#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {15, 1, 3, -4, 2, 3, 4, 7};
std::vector<int> dataA = {120, 7, 50, -50, 32, 6, 8, 14};
std::vector<int> dataB = {3, 2, 4, 4, 4, 1, 1, 1};

TEST(Golden, SraVV8VInt8) {
  NONMASK_VV_VX_GEN_TEST(OneDInt8, OneDUInt8, OneDInt8, NONMASK_VV_VALUE_INIT,
                         SraVV8VInt8VIVU);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SraVV16VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, OneDUInt16, OneDInt16,
                         NONMASK_VV_VALUE_INIT, SraVV16VInt16VIVU);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SraVV32VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, OneDUInt32, OneDInt32,
                         NONMASK_VV_VALUE_INIT, SraVV32VInt32VIVU);
  EXPECT_EQ(verifyResult(c, golden), true);
}
TEST(Golden, SraVV64VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt64, OneDUInt64, OneDInt64,
                         NONMASK_VV_VALUE_INIT, SraVV64VInt64VIVU);
  EXPECT_EQ(verifyResult(c, golden), true);
}
