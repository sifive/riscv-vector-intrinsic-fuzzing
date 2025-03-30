#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {5, 4, 5, 2, -3, -4, -7, -9};
std::vector<int> dataA = {45, 37, 41, 17, -19, -29, -53, -67};
int dataB = 3;

TEST(Golden, SraVX8VInt8) {
  NONMASK_VV_VX_GEN_TEST(OneDInt8, ScalarUInt32, OneDInt8,
                         NONMASK_VX_VALUE_INIT, SraVX8VInt8VISL);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SraVX16VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, ScalarUInt32, OneDInt16,
                         NONMASK_VX_VALUE_INIT, SraVX16VInt16VISL);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SraVX32VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, ScalarUInt32, OneDInt32,
                         NONMASK_VX_VALUE_INIT, SraVX32VInt32VISL);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SraVX64VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt64, ScalarUInt32, OneDInt64,
                         NONMASK_VX_VALUE_INIT, SraVX64VInt64VISL);
  EXPECT_EQ(verifyResult(c, golden), true);
}
