#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {9, 99, 115, 33, 10, 3, 94, 96, 11, -11};
std::vector<int> dataA = {1, 2, -30, -111, 0, 10, 16, 31, 111, -111};
std::vector<int> dataB = {8, 7, -111, -80, 10, 9, 31, 127, 100, 100};
std::vector<int> dataM = {1, 0, 1, 1, 1, 1, 0, 1, 1, 1};
std::vector<int> dataMO = {100, 99, 98, 97, 96, 95, 94, 93, 92, 91};

TEST(Golden, XorVV8VInt8_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt8, OneDInt8, OneDInt8, OneDInt8,
                      MASK_VV_VALUE_INIT, XorVV8VInt8_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, XorVV16VInt16_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt16, OneDInt16, OneDInt16, OneDInt16,
                      MASK_VV_VALUE_INIT, XorVV16VInt16_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, XorVV32VInt32_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt32, OneDInt32, OneDInt32, OneDInt32,
                      MASK_VV_VALUE_INIT, XorVV32VInt32_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, XorVV64VInt64_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt64, OneDInt64, OneDInt64, OneDInt64,
                      MASK_VV_VALUE_INIT, XorVV64VInt64_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
