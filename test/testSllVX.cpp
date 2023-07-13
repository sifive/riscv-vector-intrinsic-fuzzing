#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {8, 16, 24, 32, -32, -24, -16, -8};
std::vector<int> dataA = {1, 2, 3, 4, -4, -3, -2, -1};
int dataB = 3;

TEST(Golden, SllVX8VInt8) {
  NONMASK_VV_VX_GEN_TEST(OneDInt8, ScalarUInt32, OneDInt8,
                         NONMASK_VX_VALUE_INIT, SllVX8VInt8);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SllVX16VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, ScalarUInt32, OneDInt16,
                         NONMASK_VX_VALUE_INIT, SllVX16VInt16);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SllVX32VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, ScalarUInt32, OneDInt32,
                         NONMASK_VX_VALUE_INIT, SllVX32VInt32);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SllVX64VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt64, ScalarUInt32, OneDInt64,
                         NONMASK_VX_VALUE_INIT, SllVX64VInt64);
  EXPECT_EQ(verifyResult(c, golden), true);
}
