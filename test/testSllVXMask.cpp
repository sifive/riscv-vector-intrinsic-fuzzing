#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {8, 99, 24, 32, 40, -40, 94, -24, -16, -8};
std::vector<int> dataM = {1, 0, 1, 1, 1, 1, 0, 1, 1, 1};
std::vector<int> dataMO = {100, 99, 98, 97, 96, 95, 94, 93, 92, 91};
std::vector<int> dataA = {1, 2, 3, 4, 5, -5, -4, -3, -2, -1};
int dataB = 3;

TEST(Golden, SllVX8VInt8_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt8, OneDInt8, ScalarUInt32, OneDInt8,
                      MASK_VX_VALUE_INIT, SllVX8VInt8VBVISL_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, SllVX16VInt16_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt16, OneDInt16, ScalarUInt32, OneDInt16,
                      MASK_VX_VALUE_INIT, SllVX16VInt16VBVISL_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, SllVX32VInt32_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt32, OneDInt32, ScalarUInt32, OneDInt32,
                      MASK_VX_VALUE_INIT, SllVX32VInt32VBVISL_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, SllVX64VInt64_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt64, OneDInt64, ScalarUInt32, OneDInt64,
                      MASK_VX_VALUE_INIT, SllVX64VInt64VBVISL_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
