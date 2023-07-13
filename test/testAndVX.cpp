#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {1, 2, 3, 4, 4, 5, 6, 7};
std::vector<int> dataA = {1, 2, 3, 4, -4, -3, -2, -1};
int dataB = 7;

TEST(Golden, AndVX8VInt8) {
  NONMASK_VV_VX_GEN_TEST(OneDInt8, ScalarInt8, OneDInt8, NONMASK_VX_VALUE_INIT,
                         AndVX8VInt8);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, AndVX16VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, ScalarInt16, OneDInt16,
                         NONMASK_VX_VALUE_INIT, AndVX16VInt16);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, AndVX32VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, ScalarInt32, OneDInt32,
                         NONMASK_VX_VALUE_INIT, AndVX32VInt32);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, AndVX64VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt64, ScalarInt64, OneDInt64,
                         NONMASK_VX_VALUE_INIT, AndVX64VInt64);
  EXPECT_EQ(verifyResult(c, golden), true);
}
