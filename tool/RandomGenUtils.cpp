#include "RandomGenUtils.hpp"

namespace RIF {

int valueIndex;
int opIndex;

void initializeIndex() { valueIndex = opIndex = 0; }

std::string getNewValueName() {
  return "value_" + std::to_string(valueIndex++);
}

std::string getNewOperatorName() {
  return "operator_" + std::to_string(opIndex++);
}

// Currently the value created is hard-coded to OneDInt32
void fillOperatorWithUninitializedValue(Graph &graph, Graph::Operator *op,
                                        const int length) {
  for (int i = 0; i < op->inputs.size(); ++i) {
    if (op->inputs[i] == nullptr) {
      auto value =
          graph.getNewValue(op->inputTypes[i], getNewValueName(), length);
      op->addInput(i, value);
    }
  }

  if (op->outputs[0] == nullptr) {
    auto value = graph.getNewValue(op->outputType, getNewValueName(), length);
    op->addOutput(value);
  }
}

void initializeGraph(Graph &graph, const int length) {
  if (graph.operatorEnumLUT.find(InitialRootName) ==
      graph.operatorEnumLUT.end()) {
    std::cerr << "Can not find root '" << InitialRootName
              << "' in .def file, abort.\n";
    exit(1);
  }
  CustomValType initialType = graph.operatorEnumLUT[InitialRootName];
  Graph::Operator *op = graph.getNewOperator(initialType, getNewOperatorName());
  fillOperatorWithUninitializedValue(graph, op, length);
}

void growOnExistingValue(Graph &graph, const int length) {
  Graph::Value *selectValue;
  do
    selectValue = *select_random(
        graph.values, getRandomNumber<int>(0, (int)graph.values.size() - 1));
  while (graph.useCandidateLUT.find(selectValue->type) ==
             graph.useCandidateLUT.end() ||
         graph.defineCandidateLUT.find(selectValue->type) ==
             graph.defineCandidateLUT.end());
  std::cerr << "Existing value - " << selectValue->getNameWithType() << "\n";
  CustomValType type;
  if (selectValue->inputs[0] != nullptr) { // Value is defined
    do
      type =
          *select_random(graph.useCandidateLUT[selectValue->type],
                         getRandomNumber<int>(0, (int)graph.values.size() - 1));
    while (type == CustomValType::Initialize);
  } else // Create a define for
    type =
        *select_random(graph.defineCandidateLUT[selectValue->type],
                       getRandomNumber<int>(0, (int)graph.values.size() - 1));

  Graph::Operator *newOp = graph.getNewOperator(type, getNewOperatorName());
  std::cerr << "Created op - " << newOp->getNameWithType() << "\n";

  if (selectValue->inputs[0] == nullptr) {
    assert(selectValue->type == newOp->outputType);
    newOp->addOutput(selectValue);
  } else {
    for (int i = 0; i < newOp->inputs.size(); ++i)
      if (newOp->inputTypes[i] == selectValue->type && !newOp->inputs[i]) {
        newOp->addInput(i, selectValue);
        break;
      }
  }

  fillOperatorWithUninitializedValue(graph, newOp, length);
}

void createRandomOp(Graph &graph, const int length) {
  CustomValType randomType;
  randomType = *select_random(
      graph.validOpTypes,
      getRandomNumber<int>(0, (int)graph.validOpTypes.size() - 1));

  Graph::Operator *op = graph.getNewOperator(randomType, getNewOperatorName());
  std::cerr << "Created randomOp - " << op->typeID << "\n";
  fillOperatorWithUninitializedValue(graph, op, length);
}

void growUntilMaxNode(Graph &graph, const int maxNode, const int length) {
  while (graph.operators.size() < maxNode) {
    int coinFlip = getRandomNumber<int>(0, 1);
    if (coinFlip & 1) {
      std::cerr << "growOnExistingValue...\n";
      growOnExistingValue(graph, length);
    } else {
      std::cerr << "createRandomOp...\n";
      createRandomOp(graph, length);
    }
  }
}

// Currently the value created is hard-coded to OneDInt32
void defineNonInitializedValue(Graph &graph) {
  for (Graph::Value *value : graph.values) {
    if (value->inputs[0] == nullptr) {
      Graph::Operator *init =
          graph.getNewOperator(CustomValType::Initialize, getNewOperatorName());
      init->addOutput(value);
    }
  }
}

} // namespace RIF
