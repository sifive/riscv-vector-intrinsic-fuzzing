#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> dataM;
std::vector<int> dataA;
TEST(Golden, FirstMSInt32VB_0) {
  dataA = {0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0,
           1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0,
           1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0,
           1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1};
  int32_t golden = 3;
  NONMASK_V_GEN_TEST(OneDBool, ScalarInt32, NONMASK_V_VALUE_INIT,
                     FirstMSInt32VB);
  auto computed = getRawPointer(b);
  EXPECT_EQ(*computed, golden);
}
TEST(Golden, FirstMSInt32VB_1) {
  dataA = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int32_t golden = -1;
  NONMASK_V_GEN_TEST(OneDBool, ScalarInt32, NONMASK_V_VALUE_INIT,
                     FirstMSInt32VB);
  auto computed = getRawPointer(b);
  EXPECT_EQ(*computed, golden);
}
TEST(Golden, FirstMSInt32VB_2) {
  dataA = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  int32_t golden = 119;
  NONMASK_V_GEN_TEST(OneDBool, ScalarInt32, NONMASK_V_VALUE_INIT,
                     FirstMSInt32VB);
  auto computed = getRawPointer(b);
  EXPECT_EQ(*computed, golden);
}

TEST(Golden, FirstMSInt32VBVB_m) {
  dataM = {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0};
  dataA = {0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0};
  int32_t golden = 9;
  MASK_V_NO_MASKEDOFF_GEN_TEST(OneDBool, OneDBool, ScalarInt32,
                               MASK_V_NO_MASKEDOFF_VALUE_INIT,
                               FirstMSInt32VBVB_m);
  auto computed = getRawPointer(c);
  EXPECT_EQ(*computed, golden);
}
