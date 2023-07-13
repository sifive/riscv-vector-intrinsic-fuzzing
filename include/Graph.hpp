// Graph.hpp
/*
This file defines the 2 main node type - Operator & Value. Value is the place
holder in-between the use-define chain of the graph. Operator labels the
actual operation done to the value.

The graph is a bipartite graph consisting Operator and Value. Essentially the
graph is a data flow graph. Any control flow semantics shall be transformed into
data flow.
*/
#ifndef RIF_GRAPH_HPP
#define RIF_GRAPH_HPP

#include "Operator.hpp"
#include "Utils.hpp"
#include "Value.hpp"

#include <cassert>
#include <cstdint>

#include <cstddef>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace RIF {

struct Graph {
  using Operator = OperatorBase;
  using Value = ValueBase;

  using OperatorLookup = std::map<std::string, Operator *>;
  using ValueLookup = std::map<std::string, Value *>;

  using OperatorCollection = std::set<Operator *>;
  using ValueCollection = std::set<Value *>;

  // key = enum of Values
  // value = enum of Operators
  // The 2 lookup tables are used in graph generation, when a value
  // is selected it has 2 directions to expand. The first is to create an
  // operator that defines it. The second is to create an operator that uses it
  // (alongside of this, other values are created to be used by the new
  // operator)
  using UseCandidateLookup = std::map<CustomValType, std::set<CustomValType>>;
  using DefineCandidateLookup =
      std::map<CustomValType, std::set<CustomValType>>;
  using EnumLoopkup = std::map<std::string, CustomValType>;

  static bool isConstructedUseDefineCandidate;
  static UseCandidateLookup useCandidateLUT;
  static DefineCandidateLookup defineCandidateLUT;
  static EnumLoopkup operatorEnumLUT;

  void removeOperator(Operator *op);

  Graph();

  Operator *getNewOperator(const CustomValType type, const std::string &id,
                           const LmulType lmul = LmulType::m1) {
    if (operatorLUT.find(id) != end(operatorLUT)) {
      std::cerr << "Found duplicate name in operatorLUT\n";
      exit(1);
    }
    if (valueLUT.find(id) != end(valueLUT)) {
      std::cerr << "Found duplicate name in valueLUT\n";
      exit(1);
    }
    Operator *op = nullptr;

    if (type == CustomValType::Initialize)
      op = new InitializeOp(id);
#define CUSTOM_OP_TYPE(OP_TYPE, ...)                                           \
  if (type == CustomValType::OP_TYPE)                                          \
    op = new OP_TYPE##Op(id, lmul);
#include "CustomOperator.def"
#undef CUSTOM_OP_TYPE

    assert(op != nullptr && "Operator type not defined in CustomOperator.def");

    operatorLUT[id] = op;
    operators.insert(op);
    return op;
  }

  Value *getNewValue(const CustomValType type, const std::string &id,
                     const int &length, const LmulType lmul = LmulType::m1) {
    if (operatorLUT.find(id) != end(operatorLUT)) {
      std::cerr << "Found duplicate name in operatorLUT\n";
      exit(1);
    }
    if (valueLUT.find(id) != end(valueLUT)) {
      std::cerr << "Found duplicate name in valueLUT\n";
      exit(1);
    }
    Value *value = nullptr;

#define CUSTOM_ONE_D_TYPE(CUSTOM_NAME, ...)                                    \
  if (type == OneD##CUSTOM_NAME)                                               \
    value = new OneD##CUSTOM_NAME##Val(id, length, lmul);
#include "CustomValue.def"
#undef CUSTOM_ONE_D_TYPE
#undef CUSTOM_SCALAR_TYPE
#define CUSTOM_SCALAR_TYPE(CUSTOM_NAME, ...)                                   \
  if (type == Scalar##CUSTOM_NAME)                                             \
    value = new Scalar##CUSTOM_NAME##Val(id, length, lmul);
#include "CustomValue.def"
#undef CUSTOM_ONE_D_TYPE
#undef CUSTOM_SCALAR_TYPE

    assert(value != nullptr && "Value type not defined in CustomValue.def");

    valueLUT[id] = value;
    values.insert(value);
    return value;
  }

  bool isOperator(const std::string &id);
  bool isValue(const std::string &id);

  void generateData(uint32_t seed = InitialSeed);
  void generateGraphViz(std::ostream &os);
  void generateCCode(std::ostream &os, uint32_t seed = InitialSeed);

  std::vector<std::string>
  getOperatorsInTopologicalOrder(uint32_t seed = InitialSeed);
  std::vector<std::string>
  getOperatorsInReverseTopologicalOrder(uint32_t seed = InitialSeed);

  // Misc sub-functions (utilities)
  void emitHeader(std::ostream &os);

  OperatorLookup operatorLUT;
  ValueLookup valueLUT;
  std::vector<CustomValType> validOpTypes;

  OperatorCollection operators;
  ValueCollection values;
};

} // namespace RIF
#endif // #define RIF_GRAPH_HPP
