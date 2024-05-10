#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {5, 99, 5, 2, -3, -4, 94, -9};
std::vector<int> dataM = {1, 0, 1, 1, 1, 1, 0, 1};
std::vector<int> dataMO = {100, 99, 98, 97, 96, 95, 94, 93};
std::vector<int> dataA = {45, 37, 41, 17, -19, -29, -53, -67};
int dataB = 3;

TEST(Golden, SraVX8VInt8_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt8, OneDInt8, ScalarUInt32, OneDInt8,
                      MASK_VX_VALUE_INIT, SraVX8VInt8VBVISL_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, SraVX16VInt16_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt16, OneDInt16, ScalarUInt32, OneDInt16,
                      MASK_VX_VALUE_INIT, SraVX16VInt16VBVISL_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, SraVX32VInt32_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt32, OneDInt32, ScalarUInt32, OneDInt32,
                      MASK_VX_VALUE_INIT, SraVX32VInt32VBVISL_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, SraVX64VInt64_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt64, OneDInt64, ScalarUInt32, OneDInt64,
                      MASK_VX_VALUE_INIT, SraVX64VInt64VBVISL_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
