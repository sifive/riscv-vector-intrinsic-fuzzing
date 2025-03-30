#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {-7, -5, -3, -1, 0, 0, 0, 0};
std::vector<int> dataA = {1, 2, 3, 4, 4, 3, 2, 1};
std::vector<int> dataB = {8, 7, 6, 5, 4, 3, 2, 1};

TEST(Golden, SubVV8VInt8) {
  NONMASK_VV_VX_GEN_TEST(OneDInt8, OneDInt8, OneDInt8, NONMASK_VV_VALUE_INIT,
                         SubVV8VInt8VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SubVV16VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, OneDInt16, OneDInt16, NONMASK_VV_VALUE_INIT,
                         SubVV16VInt16VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SubVV32VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, OneDInt32, OneDInt32, NONMASK_VV_VALUE_INIT,
                         SubVV32VInt32VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SubVV64VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt64, OneDInt64, OneDInt64, NONMASK_VV_VALUE_INIT,
                         SubVV64VInt64VIVI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
