#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> golden = {9, 9, 9, 9, 8, 6, 4, 2};
std::vector<int> dataA = {1, 2, 3, 4, 4, 3, 2, 1};
std::vector<int> dataB = {8, 7, 6, 5, 4, 3, 2, 1};

TEST(Golden, WaddWVV8VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt8, OneDInt8, OneDInt16, NONMASK_VV_VALUE_INIT,
                         WaddWVV8VInt16);
  EXPECT_EQ(verifyResult(c, golden), true);
}

TEST(Golden, WaddWVV16VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, OneDInt16, OneDInt32, NONMASK_VV_VALUE_INIT,
                         WaddWVV16VInt32);
  EXPECT_EQ(verifyResult(c, golden), true);
}

TEST(Golden, WaddWVV32VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, OneDInt32, OneDInt64, NONMASK_VV_VALUE_INIT,
                         WaddWVV32VInt64);
  EXPECT_EQ(verifyResult(c, golden), true);
}

TEST(Golden, WaddWWV8VInt16) {
  NONMASK_VV_VX_GEN_TEST(OneDInt16, OneDInt8, OneDInt16, NONMASK_VV_VALUE_INIT,
                         WaddWWV8VInt16);
  EXPECT_EQ(verifyResult(c, golden), true);
}

TEST(Golden, WaddWWV16VInt32) {
  NONMASK_VV_VX_GEN_TEST(OneDInt32, OneDInt16, OneDInt32, NONMASK_VV_VALUE_INIT,
                         WaddWWV16VInt32);
  EXPECT_EQ(verifyResult(c, golden), true);
}

TEST(Golden, WaddWWV32VInt64) {
  NONMASK_VV_VX_GEN_TEST(OneDInt64, OneDInt32, OneDInt64, NONMASK_VV_VALUE_INIT,
                         WaddWWV32VInt64);
  EXPECT_EQ(verifyResult(c, golden), true);
}
