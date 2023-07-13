#include "TestUtils.hpp"
#include <gtest/gtest.h>

#include <vector>

using namespace RIF;

std::vector<int> golden = {-1, -2, -3, -4, 4, 3, 2, 1};
std::vector<int> dataA = {1, 2, 3, 4, -4, -3, -2, -1};

TEST(Golden, NegV8) {
  Graph graph;
  auto result =
      NonMaskVOperatorTest<OneDInt8Val, OneDInt8, NegV8VInt8VI>(graph, dataA);
  EXPECT_EQ(verifyResult(result, golden), true);
}
TEST(Golden, NegV16) {
  Graph graph;
  auto result = NonMaskVOperatorTest<OneDInt16Val, OneDInt16, NegV16VInt16VI>(
      graph, dataA);
  EXPECT_EQ(verifyResult(result, golden), true);
}
TEST(Golden, NegV32) {
  Graph graph;
  auto result = NonMaskVOperatorTest<OneDInt32Val, OneDInt32, NegV32VInt32VI>(
      graph, dataA);
  EXPECT_EQ(verifyResult(result, golden), true);
}
TEST(Golden, NegV64) {
  Graph graph;
  auto result = NonMaskVOperatorTest<OneDInt64Val, OneDInt64, NegV64VInt64VI>(
      graph, dataA);
  EXPECT_EQ(verifyResult(result, golden), true);
}
