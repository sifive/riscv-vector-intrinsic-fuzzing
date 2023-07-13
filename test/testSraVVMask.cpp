#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {15, 99, 3, -4, 2, 3, 94, 7, 5, 2};
std::vector<int> dataA = {120, 7, 50, -50, 32, 6, 8, 14, 10, 10};
std::vector<int> dataB = {3, 2, 4, 4, 4, 1, 1, 1, 1, 2};
std::vector<int> dataM = {1, 0, 1, 1, 1, 1, 0, 1, 1, 1};
std::vector<int> dataMO = {100, 99, 98, 97, 96, 95, 94, 93, 92, 91};

TEST(Golden, SraVV8VInt8_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt8, OneDInt8, OneDUInt8, OneDInt8,
                      MASK_VV_VALUE_INIT, SraVV8VInt8_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, SraVV16VInt16_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt16, OneDInt16, OneDUInt16, OneDInt16,
                      MASK_VV_VALUE_INIT, SraVV16VInt16_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, SraVV32VInt32_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt32, OneDInt32, OneDUInt32, OneDInt32,
                      MASK_VV_VALUE_INIT, SraVV32VInt32_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, SraVV64VInt64_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt64, OneDInt64, OneDUInt64, OneDInt64,
                      MASK_VV_VALUE_INIT, SraVV64VInt64_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
