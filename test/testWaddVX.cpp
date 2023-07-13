#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {3, 4, 5, 6, 6, 5, 4, 3};
std::vector<int> dataA = {1, 2, 3, 4, 4, 3, 2, 1};
int dataB = 2;

TEST(Golden, WaddWVX8VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt8, ScalarInt8, OneDInt16, NONMASK_VX_VALUE_INIT,
                         WaddWVX8VInt16);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, WaddWVX16VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, ScalarInt16, OneDInt32,
                         NONMASK_VX_VALUE_INIT, WaddWVX16VInt32);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, WaddWVX32VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, ScalarInt32, OneDInt64,
                         NONMASK_VX_VALUE_INIT, WaddWVX32VInt64);
  EXPECT_EQ(verifyResult(c, golden), true);
}

TEST(Golden, WaddWWX8VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, ScalarInt8, OneDInt16,
                         NONMASK_VX_VALUE_INIT, WaddWWX8VInt16);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, WaddWWX16VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, ScalarInt16, OneDInt32,
                         NONMASK_VX_VALUE_INIT, WaddWWX16VInt32);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, WaddWWX32VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt64, ScalarInt32, OneDInt64,
                         NONMASK_VX_VALUE_INIT, WaddWWX32VInt64);
  EXPECT_EQ(verifyResult(c, golden), true);
}
