#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {40, 99, 28, 32, 18, 18, 94, 56, 48, 80};
std::vector<int> dataA = {5, 6, 7, 8, 9, 9, 8, 7, 6, 5};
std::vector<int> dataB = {3, 3, 2, 2, 1, 1, 2, 3, 3, 4};
std::vector<int> dataM = {1, 0, 1, 1, 1, 1, 0, 1, 1, 1};
std::vector<int> dataMO = {100, 99, 98, 97, 96, 95, 94, 93, 92, 91};

TEST(Golden, SllVV8VInt8_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt8, OneDInt8, OneDUInt8, OneDInt8,
                      MASK_VV_VALUE_INIT, SllVV8VInt8_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, SllVV16VInt16_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt16, OneDInt16, OneDUInt16, OneDInt16,
                      MASK_VV_VALUE_INIT, SllVV16VInt16_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, SllVV32VInt32_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt32, OneDInt32, OneDUInt32, OneDInt32,
                      MASK_VV_VALUE_INIT, SllVV32VInt32_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, SllVV64VInt64_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt64, OneDInt64, OneDUInt64, OneDInt64,
                      MASK_VV_VALUE_INIT, SllVV64VInt64_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
