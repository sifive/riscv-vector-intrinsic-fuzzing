#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {-1, 0, 1, 2, 2, 1, 0, -1};
std::vector<int> dataA = {1, 2, 3, 4, 4, 3, 2, 1};
int dataB = 2;

TEST(Golden, SubVX8VInt8) {
  NONMASK_VV_VX_GEN_TEST(OneDInt8, ScalarInt8, OneDInt8, NONMASK_VX_VALUE_INIT,
                         SubVX8VInt8VISI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SubVX16VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, ScalarInt16, OneDInt16,
                         NONMASK_VX_VALUE_INIT, SubVX16VInt16VISI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SubVX32VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, ScalarInt32, OneDInt32,
                         NONMASK_VX_VALUE_INIT, SubVX32VInt32VISI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SubVX64VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt64, ScalarInt64, OneDInt64,
                         NONMASK_VX_VALUE_INIT, SubVX64VInt64VISI);
  EXPECT_EQ(verifyResult(c, golden), true);
}
