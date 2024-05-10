// poc output should be stay the same
#include "Graph.hpp"
#include "TestUtils.hpp"
#include "Value.hpp"
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace RIF;

TEST(ProofOfConcept, Graphviz) {

  Graph graph;
  const int length = 15;

  auto a = getInitializeValue(OneDInt32, graph, "A", length);
  auto b = getInitializeValue(OneDInt32, graph, "B", length);
  auto c = graph.getNewValue(OneDInt32, "value_C", length);

  auto op1 = graph.getNewOperator(AddVV32VInt32VIVI, "op1");

  op1->addInput(0, a);
  op1->addInput(1, b);
  op1->addOutput(c);

  const char *expectedGraphviz = "digraph{\n"
                                 "vinit_rif_init_A[shape=oval]\n"
                                 "vinit_rif_init_B[shape=oval]\n"
                                 "vadd_vv_op1[shape=oval]\n"
                                 "OneDInt32_value_A[shape=rectangle]\n"
                                 "OneDInt32_value_B[shape=rectangle]\n"
                                 "OneDInt32_value_C[shape=rectangle]\n"
                                 "vinit_rif_init_A -> OneDInt32_value_A\n"
                                 "OneDInt32_value_A -> vadd_vv_op1\n"
                                 "vinit_rif_init_B -> OneDInt32_value_B\n"
                                 "OneDInt32_value_B -> vadd_vv_op1\n"
                                 "vadd_vv_op1 -> OneDInt32_value_C\n"
                                 "}\n";

  std::stringstream generatedGraphviz;

  graph.generateData();
  graph.generateGraphViz(generatedGraphviz);

  EXPECT_EQ(generatedGraphviz.str(), expectedGraphviz);
}
