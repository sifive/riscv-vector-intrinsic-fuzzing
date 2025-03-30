#include "Basic.hpp"
#include "TestUtils.hpp"
#include "TypeInfo.hpp"
#include "Utils.hpp"
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

using namespace RIF;

static int idx = 0;

static std::string getNewValueName() {
  return "value_" + std::to_string(idx++);
}

void fillOperatorWithInitializedValue(Graph &graph, Graph::Operator *op,
                                      const int length) {
  for (int i = 0; i < op->inputs.size(); ++i) {
    if (op->inputs[i] == nullptr) {
      auto value =
          getInitializeValue(op->inputTypes[i], graph, getNewValueName(),
                             length, op->typeInfo->lmul);
      op->addInput(i, value);
    }
  }

  if (op->outputs[0] == nullptr) {
    auto value = getInitializeValue(op->outputType, graph, getNewValueName(),
                                    length, op->typeInfo->lmul);
    op->addOutput(value);
  }
}

const char *expectedCCode = "";

TEST(EnumerateLmul, AddVV8) {
  uint32_t seed = 0xdeadbeef;
  initializeRNG(seed);

  int length = 70;
  Graph graph;

  const SewType operatorSew = SewType{e32};
  for (LmulType lmul : TypeInfo::validSewLmul[operatorSew]) {
    auto op = graph.getNewOperator(AddVV32VInt32VBVIVI_m,
                                   "op_" + std::string(LMUL_STR(lmul)), lmul);

    fillOperatorWithInitializedValue(graph, op, length);
    op->generateData();
  }
  graph.generateData();

  graph.generateCCode(std::cout);
  // std::stringstream generatedCCode;
  // graph.generateCCode(generatedCCode);

  // EXPECT_EQ(generatedCCode.str(), expectedCCode);
}
