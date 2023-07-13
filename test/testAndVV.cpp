#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {0, 2, 2, 0, 0, 8, 16, 31};
std::vector<int> dataA = {1, 2, 3, 10, 0, 10, 16, 31};
std::vector<int> dataB = {8, 7, 6, 0, 10, 9, 31, 127};

TEST(Golden, AndVV8VInt8) {
  NONMASK_VV_VX_GEN_TEST(OneDInt8, OneDInt8, OneDInt8, NONMASK_VV_VALUE_INIT,
                         AndVV8VInt8);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, AndVV16VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, OneDInt16, OneDInt16, NONMASK_VV_VALUE_INIT,
                         AndVV16VInt16);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, AndVV32VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, OneDInt32, OneDInt32, NONMASK_VV_VALUE_INIT,
                         AndVV32VInt32);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, AndVV64VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt64, OneDInt64, OneDInt64, NONMASK_VV_VALUE_INIT,
                         AndVV64VInt64);
  EXPECT_EQ(verifyResult(c, golden), true);
}
