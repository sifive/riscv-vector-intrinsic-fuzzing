#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {3, 4, 5, 6, 6, 5, 4, 3};
std::vector<int> dataA = {1, 2, 3, 4, 4, 3, 2, 1};
int dataB = 2;

TEST(Golden, AddVX8VInt8) {
  NONMASK_VV_VX_GEN_TEST(OneDInt8, ScalarInt8, OneDInt8, NONMASK_VX_VALUE_INIT,
                         AddVX8VInt8);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, AddVX16VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, ScalarInt16, OneDInt16,
                         NONMASK_VX_VALUE_INIT, AddVX16VInt16);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, AddVX32VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, ScalarInt32, OneDInt32,
                         NONMASK_VX_VALUE_INIT, AddVX32VInt32);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, AddVX64VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt64, ScalarInt64, OneDInt64,
                         NONMASK_VX_VALUE_INIT, AddVX64VInt64);
  EXPECT_EQ(verifyResult(c, golden), true);
}
