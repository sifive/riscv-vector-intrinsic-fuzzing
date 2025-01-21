#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {9, 7, 7, 10, 10, 11, 31, 127};
std::vector<int> dataA = {1, 2, 3, 10, 0, 10, 16, 31};
std::vector<int> dataB = {8, 7, 6, 0, 10, 9, 31, 127};

TEST(Golden, OrVV8VInt8) {
  NONMASK_VV_VX_GEN_TEST(OneDInt8, OneDInt8, OneDInt8, NONMASK_VV_VALUE_INIT,
                         OrVV8VInt8VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, OrVV16VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, OneDInt16, OneDInt16, NONMASK_VV_VALUE_INIT,
                         OrVV16VInt16VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, OrVV32VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, OneDInt32, OneDInt32, NONMASK_VV_VALUE_INIT,
                         OrVV32VInt32VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, OrVV64VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt64, OneDInt64, OneDInt64, NONMASK_VV_VALUE_INIT,
                         OrVV64VInt64VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
