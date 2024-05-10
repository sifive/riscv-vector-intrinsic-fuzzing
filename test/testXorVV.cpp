#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {9, 5, 5, 10, 10, 3, 15, 96};
std::vector<int> dataA = {1, 2, 3, 10, 0, 10, 16, 31};
std::vector<int> dataB = {8, 7, 6, 0, 10, 9, 31, 127};

TEST(Golden, XorVV8VInt8) {
  NONMASK_VV_VX_GEN_TEST(OneDInt8, OneDInt8, OneDInt8, NONMASK_VV_VALUE_INIT,
                         XorVV8VInt8VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, XorVV16VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, OneDInt16, OneDInt16, NONMASK_VV_VALUE_INIT,
                         XorVV16VInt16VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, XorVV32VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, OneDInt32, OneDInt32, NONMASK_VV_VALUE_INIT,
                         XorVV32VInt32VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, XorVV64VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt64, OneDInt64, OneDInt64, NONMASK_VV_VALUE_INIT,
                         XorVV64VInt64VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
