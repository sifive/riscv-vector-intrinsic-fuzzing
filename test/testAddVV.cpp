#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {9, 9, 9, 9, 8, 6, 4, 2};
std::vector<int> dataA = {1, 2, 3, 4, 4, 3, 2, 1};
std::vector<int> dataB = {8, 7, 6, 5, 4, 3, 2, 1};

TEST(Golden, AddVV8VInt8) {
  NONMASK_VV_VX_GEN_TEST(OneDInt8, OneDInt8, OneDInt8, NONMASK_VV_VALUE_INIT,
                         AddVV8VInt8VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, AddVV16VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, OneDInt16, OneDInt16, NONMASK_VV_VALUE_INIT,
                         AddVV16VInt16VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, AddVV32VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, OneDInt32, OneDInt32, NONMASK_VV_VALUE_INIT,
                         AddVV32VInt32VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, AddVV64VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt64, OneDInt64, OneDInt64, NONMASK_VV_VALUE_INIT,
                         AddVV64VInt64VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
