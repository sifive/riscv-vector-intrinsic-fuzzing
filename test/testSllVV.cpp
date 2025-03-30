#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {32, 16, 12, 8, 8, 12, 16, 32};
std::vector<int> dataA = {1, 2, 3, 4, 4, 3, 2, 1};
std::vector<int> dataB = {5, 3, 2, 1, 1, 2, 3, 5};

TEST(Golden, SllVV8VInt8) {
  NONMASK_VV_VX_GEN_TEST(OneDInt8, OneDUInt8, OneDInt8, NONMASK_VV_VALUE_INIT,
                         SllVV8VInt8VIVU);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SllVV16VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, OneDUInt16, OneDInt16,
                         NONMASK_VV_VALUE_INIT, SllVV16VInt16VIVU);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SllVV32VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, OneDUInt32, OneDInt32,
                         NONMASK_VV_VALUE_INIT, SllVV32VInt32VIVU);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SllVV64VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt64, OneDUInt64, OneDInt64,
                         NONMASK_VV_VALUE_INIT, SllVV64VInt64VIVU);
  EXPECT_EQ(verifyResult(c, golden), true);
}
