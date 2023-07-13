#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> goldenVV = {9, 9, 9, 9, 8, 6, 4, 2};
std::vector<int> goldenVF = {9, 10, 11, 12, 12, 11, 10, 9};
std::vector<int> dataA = {1, 2, 3, 4, 4, 3, 2, 1};
std::vector<int> dataBOneD = {8, 7, 6, 5, 4, 3, 2, 1};
int dataBScalar = 8;

TEST(Golden, FaddVV16VFloat16VFVF) {

  NONMASK_VV_VX_GEN_TEST(OneDFloat16, OneDFloat16, OneDFloat16,
                         NONMASK_FP_VV_VALUE_INIT(16), FaddVV16VFloat16VFVF);
  EXPECT_EQ(verifyResult(c, goldenVV), true);
}

TEST(Golden, FaddVV32VFloat32VFVF) {
  NONMASK_VV_VX_GEN_TEST(OneDFloat32, OneDFloat32, OneDFloat32,
                         NONMASK_FP_VV_VALUE_INIT(32), FaddVV32VFloat32VFVF);
  EXPECT_EQ(verifyResult(c, goldenVV), true);
}

TEST(Golden, FaddVV64VFloat64VFVF) {
  NONMASK_VV_VX_GEN_TEST(OneDFloat64, OneDFloat64, OneDFloat64,
                         NONMASK_FP_VV_VALUE_INIT(64), FaddVV64VFloat64VFVF);
  EXPECT_EQ(verifyResult(c, goldenVV), true);
}

TEST(Golden, FaddVF16VFloat16VFSF) {
  NONMASK_VV_VX_GEN_TEST(OneDFloat16, ScalarFloat16, OneDFloat16,
                         NONMASK_FP_VX_VALUE_INIT(16), FaddVF16VFloat16VFSF);
  EXPECT_EQ(verifyResult(c, goldenVF), true);
}

TEST(Golden, FaddVF32VFloat32VFSF) {
  NONMASK_VV_VX_GEN_TEST(OneDFloat32, ScalarFloat32, OneDFloat32,
                         NONMASK_FP_VX_VALUE_INIT(32), FaddVF32VFloat32VFSF);
  EXPECT_EQ(verifyResult(c, goldenVF), true);
}

TEST(Golden, FaddVF64VFloat64VFSF) {
  NONMASK_VV_VX_GEN_TEST(OneDFloat64, ScalarFloat64, OneDFloat64,
                         NONMASK_FP_VX_VALUE_INIT(64), FaddVF64VFloat64VFSF);
  EXPECT_EQ(verifyResult(c, goldenVF), true);
}
