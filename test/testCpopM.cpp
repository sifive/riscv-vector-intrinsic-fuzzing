#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> dataM;
std::vector<int> dataA;
TEST(Golden, CpopMSUInt32VB) {
  dataA = {0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0,
           1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0,
           1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0,
           1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1};
  uint32_t golden = 37;
  NONMASK_V_GEN_TEST(OneDBool, ScalarUInt32, NONMASK_V_VALUE_INIT,
                     CpopMSUInt32VB);
  auto computed = getRawPointer(b);
  EXPECT_EQ(*computed, golden);
}

TEST(Golden, CpopMSUInt32VBVB_m) {
  dataM = {0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0,
           0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0,
           1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0,
           0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1};
  dataA = {0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0,
           1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0,
           1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0,
           1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1};
  uint32_t golden = 28;
  MASK_V_NO_MASKEDOFF_GEN_TEST(OneDBool, OneDBool, ScalarUInt32,
                               MASK_V_NO_MASKEDOFF_VALUE_INIT,
                               CpopMSUInt32VBVB_m);
  auto computed = getRawPointer(c);
  EXPECT_EQ(*computed, golden);
}
