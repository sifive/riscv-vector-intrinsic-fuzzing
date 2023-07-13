#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {2, 99, 5, 7, 10, 14, 94, 29, 43, 65};
std::vector<int> dataM = {1, 0, 1, 1, 1, 1, 0, 1, 1, 1};
std::vector<int> dataMO = {100, 99, 98, 97, 96, 95, 94, 93, 92, 91};
std::vector<int> dataA = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
std::vector<int> dataB = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};

TEST(Golden, AddVV8VInt8_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt8, OneDInt8, OneDInt8, OneDInt8,
                      MASK_VV_VALUE_INIT, AddVV8VInt8_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, AddVV16VInt16_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt16, OneDInt16, OneDInt16, OneDInt16,
                      MASK_VV_VALUE_INIT, AddVV16VInt16_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, AddVV32VInt32_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt32, OneDInt32, OneDInt32, OneDInt32,
                      MASK_VV_VALUE_INIT, AddVV32VInt32_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, AddVV64VInt64_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt64, OneDInt64, OneDInt64, OneDInt64,
                      MASK_VV_VALUE_INIT, AddVV64VInt64_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
