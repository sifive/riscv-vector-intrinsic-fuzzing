#include "Graph.hpp"
#include "Basic.hpp"
#include "Utils.hpp"
#include "Value.hpp"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <random>
#include <utility>

using namespace RIF;

// This structure is used to encapsulate the operation definition in
// CustomOperator.def , these information can be used further, e.g. filters,
// counters, etc.
struct OpDefinition {
  CustomValType opType;
  std::string opTypeStr;
  std::string opId;
  int sew;
  TypeClass typeClass;
  uint32_t opAttr;
  CustomValType outputType;
  int numOfInputs;
  std::vector<CustomValType> inputTypes;
  OpDefinition(CustomValType opType, 
               std::string &&opTypeStr,
               std::string &&opId, 
               int sew, 
               TypeClass typeClass,
               uint32_t opAttr, 
               CustomValType outputType, 
               int numOfInputs,
               std::vector<CustomValType> inputTypes)
      : opType(opType), 
        opTypeStr(std::move(opTypeStr)), 
        opId(std::move(opId)),
        sew(sew), 
        typeClass(typeClass), 
        opAttr(opAttr), 
        outputType(outputType),
        numOfInputs(numOfInputs), 
        inputTypes(inputTypes) {}
};

bool Graph::isConstructedUseDefineCandidate = false;
Graph::DefineCandidateLookup Graph::defineCandidateLUT;
Graph::UseCandidateLookup Graph::useCandidateLUT;
Graph::EnumLoopkup Graph::operatorEnumLUT;
static std::vector<OpDefinition> opDefs;

void Graph::removeOperator(Operator *op) {
  auto id = op->id;
  operatorLUT.erase(id);
  operators.erase(op);
  delete op;
}

static void getOpDefinitions() {
#define CUSTOM_OP_TYPE(OP_TYPE, OP_ID, SEW, TYPE_CLASS, OP_ATTR, OUTPUT_TYPE,  \
                       NUM_OF_INPUTS, ...)                                     \
  {                                                                            \
    OpDefinition opDef{OP_TYPE,     #OP_TYPE,      std::string(#OP_ID),        \
                       SEW,         TYPE_CLASS,    OP_ATTR,                    \
                       OUTPUT_TYPE, NUM_OF_INPUTS, {__VA_ARGS__}};             \
    opDefs.push_back(opDef);                                                   \
  }
#include "CustomOperator.def"
#undef CUSTOM_OP_TYPE
}

// The attribute filter used to filter out the operators that contain
// attributes that are not enabled.
static bool hasPolicyAttr(const OpDefinition &opDef) {
  if (!HasPolicy) {
    return (opDef.opAttr & (TailUndisturbed | MaskUndisturbed)) == 0;
  }
  return true;
}

static bool hasTAAttr(const OpDefinition &opDef) {
  if (!HasTA)
    return (opDef.opAttr & TailAgnostic) == 0;
  return true;
}

static bool hasMAAttr(const OpDefinition &opDef) {
  if (!HasMA)
    return (opDef.opAttr & MaskAgnostic) == 0;
  return true;
}

Graph::Graph() {
  if (isConstructedUseDefineCandidate == false) {
    getOpDefinitions();
    std::vector<std::function<bool(const OpDefinition &)>> filters = {
        hasPolicyAttr, hasTAAttr, hasMAAttr};
    for (const auto &opDef : opDefs) {
      bool valid = true;
      for (auto &filter : filters) {
        valid &= filter(opDef);
      }
      if (valid) {
        validOpTypes.push_back(opDef.opType);
        operatorEnumLUT[opDef.opTypeStr] = opDef.opType;
      }
    }

    // Try create all operators and build mapping of them
    for (const auto &opType : validOpTypes) {
      auto op = getNewOperator(opType, "trashOp");

      defineCandidateLUT[op->outputType].insert(op->type);
      for (int j = 0; j < op->inputs.size(); ++j)
        useCandidateLUT[op->inputTypes[j]].insert(op->type);

      removeOperator(op);
    }
    isConstructedUseDefineCandidate = true;
  }
}

void Graph::generateGraphViz(std::ostream &os) {
  os << "digraph{\n";

  for (auto op : operators)
    os << op->getNameWithType() << "[shape=oval]\n";
  for (auto value : values)
    os << value->getNameWithType() << "[shape=rectangle]\n";

  for (auto value : values) {
    if (value->inputs[0] == nullptr) {
      std::cerr << "Value '" << value->id
                << "'-'s definer is not set, abort.\n";
      exit(1);
    }
    os << value->inputs[0]->getNameWithType() << " -> "
       << value->getNameWithType() << "\n";
    for (auto user : value->outputs)
      os << value->getNameWithType() << " -> " << user->getNameWithType()
         << "\n";
  }

  os << "}\n";
}

bool Graph::isOperator(const std::string &id) {
  return operatorLUT.find(id) != std::end(operatorLUT);
}
bool Graph::isValue(const std::string &id) {
  return valueLUT.find(id) != std::end(valueLUT);
}

template <typename T>
static void remove_at(std::vector<T> &v,
                      typename std::vector<T>::size_type position) {
  std::swap(v[position], v.back());
  v.pop_back();
}

std::vector<std::string> Graph::getOperatorsInTopologicalOrder(uint32_t seed) {
  initializeRNG(seed);

  // generate adjacency list with string
  std::map<std::string, std::vector<std::string>> edges;
  std::map<std::string, int> inDegreeCount;

  for (auto value : values) {
    if (value->inputs[0] == nullptr) {
      std::cerr << "Value '" << value->id
                << "'-'s definer is not set, abort.\n";
      exit(1);
    }

    edges[value->inputs[0]->id].push_back(value->id);
    ++inDegreeCount[value->id];
    for (auto user : value->outputs) {
      edges[value->id].push_back(user->id);
      ++inDegreeCount[user->id];
    }
  }

  std::set<std::string> visited;

  std::vector<std::string> topologicalSequence;
  std::vector<std::string> candidates;

  int totalNodes = edges.size();
  int visitedNodes = 0;

  for (auto node : edges) {
    auto id = node.first;
    if (inDegreeCount[id] == 0)
      candidates.push_back(id);
  }

  while (candidates.empty() == false) {
    auto pick = getRandomNumber<int>(0, (int)candidates.size() - 1);
    auto id = candidates[pick];
    assert(visited.find(id) == std::end(visited));

    if (isOperator(id))
      topologicalSequence.push_back(id);

    for (auto to : edges[id]) {
      inDegreeCount[to]--;
      if (inDegreeCount[to] == 0)
        candidates.push_back(to);
    }

    visited.insert(id);
    remove_at(candidates, pick);
  }

  return topologicalSequence;
}

std::vector<std::string>
Graph::getOperatorsInReverseTopologicalOrder(uint32_t seed) {
  std::vector<std::string> ordering = getOperatorsInTopologicalOrder(seed);
  std::reverse(begin(ordering), end(ordering));
  return ordering;
}

void Graph::emitHeader(std::ostream &os) {
  os << "// generated by library/Graph.cpp Graph::emitHeader\n";
  os << "#include <stdbool.h>\n";
  os << "#include <stdint.h>\n";
  os << "#include <stdlib.h>\n";
  os << "#include <stdio.h>\n";
  os << "#include <string.h>\n";
  os << "#include <stddef.h>\n";
  os << "#include <riscv_vector.h>\n";
  os << "typedef _Float16 float16_t;\n";
  os << "typedef float float32_t;\n";
  os << "typedef double float64_t;\n";
  os << "#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & 0x03FF))\n";
  os << "#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & "
        "0x007FFFFF))\n";
  os << "#define isNaNF64UI( a ) (((~(a) & UINT64_C( 0x7FF0000000000000 )) == "
        "0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF )))\n";
}

void Graph::generateData(uint32_t seed) {
  // FIXME: increase parameter of this function (or add a global under
  // Utils.hpp) so that topological order and data gen can have separate seeds
  auto ordering = getOperatorsInTopologicalOrder(seed);
  initializeRNG(seed);
  // generate data for the operators
  for (auto id : ordering) {
    auto op = operatorLUT[id];
    if (op->type == CustomValType::Initialize) {
      auto value = op->outputs[0];
      value->generateData();
    } else {
      uint8_t save_roundingMode = softfloat_roundingMode; // save
      op->generateData();
      softfloat_roundingMode = save_roundingMode; // restore
    }
  }
}

void Graph::generateCCode(std::ostream &os, uint32_t seed) {
  placeholderIndex = 0;
  auto ordering = getOperatorsInTopologicalOrder(seed);

  emitHeader(os);

  // declare values in global (avoid stack overflow)
  for (auto value : values)
    {
      os << "//generated by library/Graph.cpp Graph::generateCCode generateCCode\n";
      value->generateCCode(os);
    }
    

  // generate function calls for the operators
  for (auto id : ordering) {
    auto op = operatorLUT[id];

    if (op->type != Initialize)
      initializeLmul(op);
    os << "// the function name generated by op->getNameWithType, generate function calls for the operators\n";
    os << "void " << op->getNameWithType() << "() {\n";
    op->generateCCode(os);
    os << "}\n";
  }

  // generate function calls for verify golden
  for (auto id : ordering) {
    auto op = operatorLUT[id];

    // Note: For 'short' mode, RIF will only generate verification only for
    // values that are non-intermediate results.
    if (VerificationMode == "short" && op->outputs[0]->outputs.size() != 0)
      continue;

    os << "//generated by library/Graph.cpp, will invoke generateVerificationCode\n";
    os << "int golden_" << op->getNameWithType() << "() {\n";

    generateVerificationCode(os, op);

    os << "}\n";
  }

  // start of main function
  os << "int main () {\n";

  // call operators in topological order
  for (auto id : ordering) {
    auto op = operatorLUT[id];
    os << op->getNameWithType() << "();\n";
  }

  // verify
  for (auto id : ordering) {
    auto op = operatorLUT[id];
    // Note: For 'short' mode, RIF will only generate verification only for
    // values that are non-intermediate results.
    if (VerificationMode == "short" && op->outputs[0]->outputs.size() != 0)
      continue;
    os << "printf(\"" << id << " : %s\\n\", golden_" << op->getNameWithType()
       << "() ? \"pass\" : \"fail\");\n";
  }

  // return 1 if any there is any failure in the operator
  os << "// generated by library/Graph.cpp Graph::generateCCode";
  os << "int ret = 1; // 1 = success\n";
  for (auto id : ordering) {
    auto op = operatorLUT[id];
    os << "// operatorLUT[id] = " << operatorLUT[id] << "\n";
    os << "ret &= golden_" << op->getNameWithType() << "();\n";
  }
  os << "if (!ret) return 1;\n";

  // end of main function
  os << "return 0; }\n";
}