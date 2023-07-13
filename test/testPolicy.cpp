#include "TestUtils.hpp"
using namespace RIF;

std::vector<int> goldenTA = {9, -1, 9, -1, 8, -1, 4, -1};
std::vector<int> goldenTU = {9, 102, 9, 104, 8, 106, 4, 108};
std::vector<int> goldenTAMA = {9, -1, -1, -1, 8, -1, -1, -1};
std::vector<int> goldenTAMU = {9, -1, 103, -1, 8, -1, 107, -1};
std::vector<int> goldenTUMA = {9, 102, -1, 104, 8, 106, -1, 108};
std::vector<int> goldenTUMU = {9, 102, 103, 104, 8, 106, 107, 108};

std::vector<int> dataM = {1, 1, 0, 0, 1, 1, 0, 1};
std::vector<int> dataMO = {101, 102, 103, 104, 105, 106, 107, 108};
std::vector<int> dataA = {1, 2, 3, 4, 4, 3, 2, 1};
std::vector<int> dataB = {8, 7, 6, 5, 4, 3, 2, 1};

TEST(Golden, AddVV8VInt8TA) {
  NONMASK_VV_VX_GEN_TEST(OneDInt8, OneDInt8, OneDInt8, NONMASK_VV_VALUE_INIT,
                         AddVV8VInt8TA);
  EXPECT_EQ(verifyResult(c, goldenTA), true);
}

TEST(Golden, AddVV8VInt8TU) {
  NONMASK_TA_VV_VX_GEN_TEST(OneDInt8, OneDInt8, OneDInt8, OneDInt8,
                            NONMASK_TA_VV_VALUE_INIT, AddVV8VInt8TU);
  EXPECT_EQ(verifyResult(output, goldenTU), true);
}

TEST(Golden, AddVV8VInt8TAMA) {
  MASK_TAMA_VV_VX_GEN_TEST(OneDBool, OneDInt8, OneDInt8, OneDInt8,
                           MASK_TAMA_VV_VALUE_INIT, AddVV8VInt8TAMA);
  EXPECT_EQ(verifyResult(output, goldenTAMA), true);
}

TEST(Golden, AddVV8VInt8TAMU) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt8, OneDInt8, OneDInt8, OneDInt8,
                      MASK_VV_VALUE_INIT, AddVV8VInt8TAMU);
  EXPECT_EQ(verifyResult(output, goldenTAMU), true);
}

TEST(Golden, AddVV8VInt8TUMA) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt8, OneDInt8, OneDInt8, OneDInt8,
                      MASK_VV_VALUE_INIT, AddVV8VInt8TUMA);
  EXPECT_EQ(verifyResult(output, goldenTUMA), true);
}

TEST(Golden, AddVV8VInt8TUMU) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDInt8, OneDInt8, OneDInt8, OneDInt8,
                      MASK_VV_VALUE_INIT, AddVV8VInt8TUMU);
  EXPECT_EQ(verifyResult(output, goldenTUMU), true);
}
