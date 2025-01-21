#include "TestUtils.hpp"

using namespace RIF;

std::vector<int> goldenVV = {9, 99, 9, 9, 8, 6, 94, 2};
std::vector<int> goldenVF = {9, 99, 11, 12, 12, 11, 94, 9};
std::vector<int> dataA = {1, 2, 3, 4, 4, 3, 2, 1};
std::vector<int> dataBOneD = {8, 7, 6, 5, 4, 3, 2, 1};
int dataBScalar = 8;
std::vector<int> dataMask = {1, 0, 1, 1, 1, 1, 0, 1};
std::vector<int> dataMaskedOff = {100, 99, 98, 97, 96, 95, 94, 93};

TEST(Golden, FaddVV16VFloat16VBVFVFVF_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDFloat16, OneDFloat16, OneDFloat16,
                      OneDFloat16, MASK_FP_VV_VALUE_INIT(16),
                      FaddVV16VFloat16VBVFVF_m);
  verifyResult(output, goldenVV);
}

TEST(Golden, FaddVV32VFloat32VBVFVFVF_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDFloat32, OneDFloat32, OneDFloat32,
                      OneDFloat32, MASK_FP_VV_VALUE_INIT(32),
                      FaddVV32VFloat32VBVFVF_m);
  verifyResult(output, goldenVV);
}

TEST(Golden, FaddVV64VFloat64VBVFVFVF_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDFloat64, OneDFloat64, OneDFloat64,
                      OneDFloat64, MASK_FP_VV_VALUE_INIT(64),
                      FaddVV64VFloat64VBVFVF_m);
  verifyResult(output, goldenVV);
}

TEST(Golden, FaddVF16VFloat16VBVFVFSF_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDFloat16, OneDFloat16, ScalarFloat16,
                      OneDFloat16, MASK_FP_VF_VALUE_INIT(16),
                      FaddVF16VFloat16VBVFSF16_m);
  verifyResult(output, goldenVF);
}

TEST(Golden, FaddVF32VFloat32VBVFVFSF_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDFloat32, OneDFloat32, ScalarFloat32,
                      OneDFloat32, MASK_FP_VF_VALUE_INIT(32),
                      FaddVF32VFloat32VBVFSF32_m);
  verifyResult(output, goldenVF);
}

TEST(Golden, FaddVF64VFloat64VBVFVFSF_m) {
  MASK_VV_VX_GEN_TEST(OneDBool, OneDFloat64, OneDFloat64, ScalarFloat64,
                      OneDFloat64, MASK_FP_VF_VALUE_INIT(64),
                      FaddVF64VFloat64VBVFSF64_m);
  verifyResult(output, goldenVF);
}
