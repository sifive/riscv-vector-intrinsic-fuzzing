#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {14, 99, 12, 11, 10, -12, 94, -14, -15, -16};
std::vector<int> dataM = {1, 0, 1, 1, 1, 1, 0, 1, 1, 1};
std::vector<int> dataMO = {100, 99, 98, 97, 96, 95, 94, 93, 92, 91};
std::vector<int> dataA = {1, 2, 3, 4, 5, -5, -4, -3, -2, -1};
int dataB = 15;

TEST(Golden, XorVX8VInt8_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt8, OneDInt8, ScalarInt8, OneDInt8,
                      MASK_VX_VALUE_INIT, XorVX8VInt8VBVISI_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, XorVX16VInt16_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt16, OneDInt16, ScalarInt16, OneDInt16,
                      MASK_VX_VALUE_INIT, XorVX16VInt16VBVISI_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, XorVX32VInt32_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt32, OneDInt32, ScalarInt32, OneDInt32,
                      MASK_VX_VALUE_INIT, XorVX32VInt32VBVISI_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
TEST(Golden, XorVX64VInt64_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt64, OneDInt64, ScalarInt64, OneDInt64,
                      MASK_VX_VALUE_INIT, XorVX64VInt64VBVISI_m);
  EXPECT_EQ(verifyResult(output, golden), true);
}
