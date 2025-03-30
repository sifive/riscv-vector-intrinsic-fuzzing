#ifndef RIF_DECODE_H
#define RIF_DECODE_H
#include <climits>

#include "Processor.hpp"

#include "softfloat.h"
#include "specialize.h"

#if (-1 != ~0) || ((-1 >> 1) != -1)
#error spike requires a two''s-complement c++ implementation
#endif

#ifdef __SIZEOF_INT128__
typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;
#endif

// Vector macros
#define e8 8   // 8b elements
#define e16 16 // 16b elements
#define e32 32 // 32b elements
#define e64 64 // 64b elements

#define VI_VV_LOOP(BODY)                                                       \
  auto vs2 = dataA[i];                                                         \
  auto vs1 = dataB[i];                                                         \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VX_LOOP(BODY)                                                       \
  auto vs2 = dataA[i];                                                         \
  auto rs1 = *dataB;                                                           \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VV_ULOOP(BODY)                                                      \
  auto vs2 = dataA[i];                                                         \
  auto vs1 = dataB[i];                                                         \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VX_ULOOP(BODY)                                                      \
  auto vs2 = dataA[i];                                                         \
  auto rs1 = *dataB;                                                           \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_V_LOOP(BODY)                                                        \
  auto vs = dataA[i];                                                          \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_X_LOOP(BODY)                                                        \
  auto rs = *dataA;                                                            \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VV_SU_LOOP(BODY)                                                    \
  auto vs2 = dataA[i];                                                         \
  auto vs1 = dataB[i];                                                         \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VX_SU_LOOP(BODY)                                                    \
  auto vs2 = dataA[i];                                                         \
  auto rs1 = *dataB;                                                           \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VV_MUL_ADD_LOOP(BODY)                                               \
  auto vd1 = dataA[i];                                                         \
  auto vs1 = dataB[i];                                                         \
  auto vs2 = dataC[i];                                                         \
  auto &vd0 = dataOut[i];                                                      \
  BODY

#define VI_VX_MUL_ADD_LOOP(BODY)                                               \
  auto vd1 = dataA[i];                                                         \
  auto rs1 = *dataB;                                                           \
  auto vs2 = dataC[i];                                                         \
  auto &vd0 = dataOut[i];                                                      \
  BODY

#define VI_VV_LOOP_WIDEN(BODY)                                                 \
  auto vs2 = dataA[i];                                                         \
  auto vs1 = dataB[i];                                                         \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VX_LOOP_WIDEN(BODY)                                                 \
  auto vs2 = dataA[i];                                                         \
  auto rs1 = *dataB;                                                           \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VV_MUL_ADD_LOOP_WIDEN(BODY)                                         \
  auto vd_w = dataA[i];                                                        \
  auto vs1 = dataB[i];                                                         \
  auto vs2 = dataC[i];                                                         \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VX_MUL_ADD_LOOP_WIDEN(BODY)                                         \
  auto vd_w = dataA[i];                                                        \
  auto rs1 = *dataB;                                                           \
  auto vs2 = dataC[i];                                                         \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VV_LOOP_CMP(BODY)                                                   \
  auto vs2 = dataA[i];                                                         \
  auto vs1 = dataB[i];                                                         \
  auto &res = dataOut[i];                                                      \
  BODY

#define VI_VX_LOOP_CMP(BODY)                                                   \
  auto vs2 = dataA[i];                                                         \
  auto rs1 = *dataB;                                                           \
  auto &res = dataOut[i];                                                      \
  BODY

#define VI_VV_ULOOP_CMP(BODY)                                                  \
  auto vs2 = dataA[i];                                                         \
  auto vs1 = dataB[i];                                                         \
  auto &res = dataOut[i];                                                      \
  BODY

#define VI_VX_ULOOP_CMP(BODY)                                                  \
  auto vs2 = dataA[i];                                                         \
  auto rs1 = *dataB;                                                           \
  auto &res = dataOut[i];                                                      \
  BODY

#define VI_VV_LOOP_NSHIFT(BODY)                                                \
  auto vs2 = dataA[i];                                                         \
  auto vs2_u = dataA[i];                                                       \
  auto vs1 = dataB[i];                                                         \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VX_LOOP_NSHIFT(BODY)                                                \
  auto vs2 = dataA[i];                                                         \
  auto vs2_u = dataA[i];                                                       \
  auto rs1 = *dataB;                                                           \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VV_LOOP_NARROW(BODY)                                                \
  auto vs2 = dataA[i];                                                         \
  auto vs2_u = dataA[i];                                                       \
  auto vs1 = dataB[i];                                                         \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VX_LOOP_NARROW(BODY)                                                \
  auto vs2 = dataA[i];                                                         \
  auto vs2_u = dataA[i];                                                       \
  auto rs1 = *dataB;                                                           \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VV_LOOP_WITH_CARRY(BODY)                                            \
  auto vs2 = dataA[i];                                                         \
  auto vs1 = dataB[i];                                                         \
  auto carry = dataC[i];                                                       \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VX_LOOP_WITH_CARRY(BODY)                                            \
  auto vs2 = dataA[i];                                                         \
  auto rs1 = *dataB;                                                           \
  auto carry = dataC[i];                                                       \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_WIDE_OP_AND_ASSIGN(var0, var1, var2, op0, op1, sign)                \
  switch (sew) {                                                               \
  case e8:                                                                     \
    vd = op1((sign##16_t)(sign##8_t)var0 op0(sign##16_t)(sign##8_t) var1) +    \
         var2;                                                                 \
    break;                                                                     \
  case e16:                                                                    \
    vd = op1((sign##32_t)(sign##16_t)var0 op0(sign##32_t)(sign##16_t) var1) +  \
         var2;                                                                 \
    break;                                                                     \
  default:                                                                     \
    vd = op1((sign##64_t)(sign##32_t)var0 op0(sign##64_t)(sign##32_t) var1) +  \
         var2;                                                                 \
    break;                                                                     \
  }

#define VI_WIDE_OP_AND_ASSIGN_MIX(var0, var1, var2, op0, op1, sign_d, sign_1,  \
                                  sign_2)                                      \
  switch (sew) {                                                               \
  case e8:                                                                     \
    vd = op1((sign_1##16_t)(sign_1##8_t)var0 op0(sign_2##16_t)(sign_2##8_t)    \
                 var1) +                                                       \
         var2;                                                                 \
    break;                                                                     \
  case e16:                                                                    \
    vd = op1((sign_1##32_t)(sign_1##16_t)var0 op0(sign_2##32_t)(sign_2##16_t)  \
                 var1) +                                                       \
         var2;                                                                 \
    break;                                                                     \
  default:                                                                     \
    vd = op1((sign_1##64_t)(sign_1##32_t)var0 op0(sign_2##64_t)(sign_2##32_t)  \
                 var1) +                                                       \
         var2;                                                                 \
    break;                                                                     \
  }

#define VI_WIDE_WVX_OP(var0, op0, sign)                                        \
  switch (sew) {                                                               \
  case e8:                                                                     \
    vd = vs2 op0(sign##16_t)(sign##8_t) var0;                                  \
    break;                                                                     \
  case e16:                                                                    \
    vd = vs2 op0(sign##32_t)(sign##16_t) var0;                                 \
    break;                                                                     \
  default:                                                                     \
    vd = vs2 op0(sign##64_t)(sign##32_t) var0;                                 \
    break;                                                                     \
  }

#define VI_VV_MERGE_LOOP(BODY)                                                 \
  auto use_first = dataC[i];                                                   \
  auto vs2 = dataA[i];                                                         \
  auto vs1 = dataB[i];                                                         \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VX_MERGE_LOOP(BODY)                                                 \
  auto use_first = dataC[i];                                                   \
  auto vs2 = dataA[i];                                                         \
  auto rs1 = *dataB;                                                           \
  auto &vd = dataOut[i];                                                       \
  BODY

#define VI_VF_MERGE_LOOP(BODY)                                                 \
  bool use_first = dataC[i];                                                   \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  RIF::RawDatumOperand rs1(*dataB);                                            \
  RIF::RawDatumOperand vd;                                                     \
  BODY;                                                                        \
  dataOut[i] = vd;

#define VI_VV_EXT(dummy, sign)                                                 \
  auto vs = dataA[i];                                                          \
  auto &vd = dataOut[i];                                                       \
  vd = (sign##128_t)vs;

#define VV_PARAMS(...)                                                         \
  auto vs2 = dataA[i];                                                         \
  auto vs1 = dataB[i];                                                         \
  auto &vd = dataOut[i];

#define VV_U_PARAMS(...)                                                       \
  auto vs2 = dataA[i];                                                         \
  auto vs1 = dataB[i];                                                         \
  auto &vd = dataOut[i];

#define VX_PARAMS(...)                                                         \
  auto vs2 = dataA[i];                                                         \
  auto rs1 = *dataB;                                                           \
  auto &vd = dataOut[i];

#define VX_U_PARAMS(...)                                                       \
  auto vs2 = dataA[i];                                                         \
  auto rs1 = *dataB;                                                           \
  auto &vd = dataOut[i];

#define INT_ROUNDING(result, xrm, gb)                                          \
  do {                                                                         \
    const uint64_t lsb = 1UL << (gb);                                          \
    const uint64_t lsb_half = lsb >> 1;                                        \
    switch (xrm) {                                                             \
    case VRM::RNU:                                                             \
      result += lsb_half;                                                      \
      break;                                                                   \
    case VRM::RNE:                                                             \
      if ((result & lsb_half) &&                                               \
          ((result & (lsb_half - 1)) || (result & lsb)))                       \
        result += lsb;                                                         \
      break;                                                                   \
    case VRM::RDN:                                                             \
      break;                                                                   \
    case VRM::ROD:                                                             \
      if (result & (lsb - 1))                                                  \
        result |= lsb;                                                         \
      break;                                                                   \
    case VRM::INVALID_RM:                                                      \
      assert(true);                                                            \
      break;                                                                   \
    }                                                                          \
  } while (0)

#define VI_VV_LOOP_AVG(op)                                                     \
  VRM xrm = p->VU.get_vround_mode();                                           \
  VI_VV_LOOP({                                                                 \
    uint128_t res = (uint128_t)vs2 op vs1;                                     \
    INT_ROUNDING(res, xrm, 1);                                                 \
    vd = res >> 1;                                                             \
  })

#define VI_VX_LOOP_AVG(op)                                                     \
  VRM xrm = p->VU.get_vround_mode();                                           \
  VI_VX_LOOP({                                                                 \
    uint128_t res = (uint128_t)vs2 op rs1;                                     \
    INT_ROUNDING(res, xrm, 1);                                                 \
    vd = res >> 1;                                                             \
  })

#define VI_VV_ULOOP_AVG(op)                                                    \
  VRM xrm = p->VU.get_vround_mode();                                           \
  VI_VV_ULOOP({                                                                \
    uint128_t res = (uint128_t)vs2 op vs1;                                     \
    INT_ROUNDING(res, xrm, 1);                                                 \
    vd = res >> 1;                                                             \
  })

#define VI_VX_ULOOP_AVG(op)                                                    \
  VRM xrm = p->VU.get_vround_mode();                                           \
  VI_VX_ULOOP({                                                                \
    uint128_t res = (uint128_t)vs2 op rs1;                                     \
    INT_ROUNDING(res, xrm, 1);                                                 \
    vd = res >> 1;                                                             \
  })

#define VI_VV_LOOP_REDUCTION(BODY)                                             \
  auto vs2 = dataA[i];                                                         \
  auto &vd_0_res = *dataOut;                                                   \
  BODY

#define VI_VV_ULOOP_REDUCTION(BODY)                                            \
  auto vs2 = dataA[i];                                                         \
  auto &vd_0_res = *dataOut;                                                   \
  BODY

#define VI_VV_LOOP_WIDE_REDUCTION(BODY)                                        \
  auto vs2 = dataA[i];                                                         \
  auto &vd_0_res = *dataOut;                                                   \
  BODY

#define VI_VV_ULOOP_WIDE_REDUCTION(BODY)                                       \
  auto vs2 = dataA[i];                                                         \
  auto &vd_0_res = *dataOut;                                                   \
  BODY

#define VI_VFP_VV_LOOP(BODY16, BODY32, BODY64)                                 \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  RIF::RawDatumOperand vs1(dataB[i]);                                          \
  RIF::RawDatumOperand vd;                                                     \
  switch (sew) {                                                               \
  case e16:                                                                    \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    BODY32;                                                                    \
    break;                                                                     \
  case e64:                                                                    \
    BODY64;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }                                                                            \
  dataOut[i] = vd;

/*=================================*/
/*    Floating Point related       */
/*=================================*/
/* Convenience wrappers to simplify softfloat code sequences */
inline float16_t f16(uint16_t v) { return {v}; }
inline float32_t f32(uint32_t v) { return {v}; }
inline float64_t f64(uint64_t v) { return {v}; }
#define F16_SIGN ((uint16_t)1 << 15)
#define F32_SIGN ((uint32_t)1 << 31)
#define F64_SIGN ((uint64_t)1 << 63)
#define fsgnj16(a, b, n, x)                                                    \
  f16((f16(a).v & ~F16_SIGN) | ((((x)   ? f16(a).v                             \
                                  : (n) ? F16_SIGN                             \
                                        : 0) ^                                 \
                                 f16(b).v) &                                   \
                                F16_SIGN))
#define fsgnj32(a, b, n, x)                                                    \
  f32((f32(a).v & ~F32_SIGN) | ((((x)   ? f32(a).v                             \
                                  : (n) ? F32_SIGN                             \
                                        : 0) ^                                 \
                                 f32(b).v) &                                   \
                                F32_SIGN))
#define fsgnj64(a, b, n, x)                                                    \
  f64((f64(a).v & ~F64_SIGN) | ((((x)   ? f64(a).v                             \
                                  : (n) ? F64_SIGN                             \
                                        : 0) ^                                 \
                                 f64(b).v) &                                   \
                                F64_SIGN))

#define VI_VFP_V_LOOP(BODY16, BODY32, BODY64)                                  \
  RIF::RawDatumOperand vs(dataA[i]);                                           \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  RIF::RawDatumOperand vd;                                                     \
  switch (sew) {                                                               \
  case e16:                                                                    \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    BODY32;                                                                    \
    break;                                                                     \
  case e64:                                                                    \
    BODY64;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }                                                                            \
  dataOut[i] = vd;

#define VI_VFP_F_LOOP(BODY16, BODY32, BODY64)                                  \
  RIF::RawDatumOperand rs1(*dataA);                                            \
  RIF::RawDatumOperand vd;                                                     \
  switch (sew) {                                                               \
  case e16:                                                                    \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    BODY32;                                                                    \
    break;                                                                     \
  case e64:                                                                    \
    BODY64;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }                                                                            \
  dataOut[i] = vd;

#define VI_VFP_VF_LOOP(BODY16, BODY32, BODY64)                                 \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  RIF::RawDatumOperand rs1(*dataB);                                            \
  RIF::RawDatumOperand vd;                                                     \
  switch (sew) {                                                               \
  case e16:                                                                    \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    BODY32;                                                                    \
    break;                                                                     \
  case e64:                                                                    \
    BODY64;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }                                                                            \
  dataOut[i] = vd;

#define VI_VFP_VV_LOOP_WIDE(BODY16, BODY32)                                    \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  RIF::RawDatumOperand vs1(dataB[i]);                                          \
  RIF::RawDatumOperand vd;                                                     \
  switch (sew) {                                                               \
  case e16:                                                                    \
    vs2 = f16_to_f32(vs2);                                                     \
    vs1 = f16_to_f32(vs1);                                                     \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    vs2 = f32_to_f64(vs2);                                                     \
    vs1 = f32_to_f64(vs1);                                                     \
    BODY32;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }                                                                            \
  dataOut[i] = vd;

#define VI_VFP_WV_LOOP_WIDE(BODY16, BODY32)                                    \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  RIF::RawDatumOperand vs1(dataB[i]);                                          \
  RIF::RawDatumOperand vd;                                                     \
  switch (sew) {                                                               \
  case e16:                                                                    \
    vs1 = f16_to_f32(vs1);                                                     \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    vs1 = f32_to_f64(vs1);                                                     \
    BODY32;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }                                                                            \
  dataOut[i] = vd;

#define VI_VFP_VF_LOOP_WIDE(BODY16, BODY32)                                    \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  RIF::RawDatumOperand rs1(*dataB);                                            \
  RIF::RawDatumOperand vd;                                                     \
  switch (sew) {                                                               \
  case e16:                                                                    \
    vs2 = f16_to_f32(vs2);                                                     \
    rs1 = f16_to_f32(rs1);                                                     \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    vs2 = f32_to_f64(vs2);                                                     \
    rs1 = f32_to_f64(rs1);                                                     \
    BODY32;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }                                                                            \
  dataOut[i] = vd;

#define VI_VFP_WF_LOOP_WIDE(BODY16, BODY32)                                    \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  RIF::RawDatumOperand rs1(*dataB);                                            \
  RIF::RawDatumOperand vd;                                                     \
  switch (sew) {                                                               \
  case e16:                                                                    \
    rs1 = f16_to_f32(rs1);                                                     \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    rs1 = f32_to_f64(rs1);                                                     \
    BODY32;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }                                                                            \
  dataOut[i] = vd;

#define VI_VFP_VV_LOOP_CMP(BODY16, BODY32, BODY64)                             \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  RIF::RawDatumOperand vs1(dataB[i]);                                          \
  bool res;                                                                    \
  switch (sew) {                                                               \
  case e16:                                                                    \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    BODY32;                                                                    \
    break;                                                                     \
  case e64:                                                                    \
    BODY64;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }                                                                            \
  dataOut[i] = res;

#define VI_VFP_VF_LOOP_CMP(BODY16, BODY32, BODY64)                             \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  RIF::RawDatumOperand rs1(*dataB);                                            \
  bool res;                                                                    \
  switch (sew) {                                                               \
  case e16:                                                                    \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    BODY32;                                                                    \
    break;                                                                     \
  case e64:                                                                    \
    BODY64;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }                                                                            \
  dataOut[i] = res;

// floating point conversions
#define VI_VFP_CVT_INT_TO_FP(BODY16, BODY32, BODY64, ...)                      \
  auto vs2(dataA[i]);                                                          \
  RIF::RawDatumOperand vd;                                                     \
  switch (sew) {                                                               \
  case e16:                                                                    \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    BODY32;                                                                    \
    break;                                                                     \
  case e64:                                                                    \
    BODY64;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }                                                                            \
  dataOut[i] = vd;

#define VI_VFP_CVT_FP_TO_INT(BODY16, BODY32, BODY64, ...)                      \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  auto &vd = dataOut[i];                                                       \
  switch (sew) {                                                               \
  case e16:                                                                    \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    BODY32;                                                                    \
    break;                                                                     \
  case e64:                                                                    \
    BODY64;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }

#define VI_VFP_WCVT_FP_TO_FP(BODY8, BODY16, BODY32, ...)                       \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  RIF::RawDatumOperand vd;                                                     \
  switch (sew) {                                                               \
  case e8:                                                                     \
    BODY8;                                                                     \
    break;                                                                     \
  case e16:                                                                    \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    BODY32;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }                                                                            \
  dataOut[i] = vd;

#define VI_VFP_WCVT_INT_TO_FP(BODY8, BODY16, BODY32, ...)                      \
  auto vs2 = dataA[i];                                                         \
  RIF::RawDatumOperand vd;                                                     \
  switch (sew) {                                                               \
  case e8:                                                                     \
    BODY8;                                                                     \
    break;                                                                     \
  case e16:                                                                    \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    BODY32;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }                                                                            \
  dataOut[i] = vd;

#define VI_VFP_WCVT_FP_TO_INT(BODY8, BODY16, BODY32, ...)                      \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  auto &vd = dataOut[i];                                                       \
  switch (sew) {                                                               \
  case e8:                                                                     \
    BODY8;                                                                     \
    break;                                                                     \
  case e16:                                                                    \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    BODY32;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }

#define VI_VFP_NCVT_FP_TO_FP(BODY16, BODY32, BODY64, ...)                      \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  RIF::RawDatumOperand vd;                                                     \
  switch (sew) {                                                               \
  case e16:                                                                    \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    BODY32;                                                                    \
    break;                                                                     \
  case e64:                                                                    \
    BODY64;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }                                                                            \
  dataOut[i] = vd;

#define VI_VFP_NCVT_INT_TO_FP(BODY16, BODY32, BODY64, ...)                     \
  VI_VFP_CVT_INT_TO_FP(BODY16, BODY32, BODY64);

#define VI_VFP_NCVT_FP_TO_INT(BODY16, BODY32, BODY64, ...)                     \
  VI_VFP_CVT_FP_TO_INT(BODY16, BODY32, BODY64);

#define VI_VFP_VV_LOOP_REDUCTION(BODY16, BODY32, BODY64)                       \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  RIF::RawDatumOperand vd_0(*dataOut);                                         \
  switch (sew) {                                                               \
  case e16: {                                                                  \
    BODY16;                                                                    \
    if (is_propagate) {                                                        \
      auto ret = f16_classify(f16(vd_0));                                      \
      if (ret & 0x300) {                                                       \
        if (ret & 0x100)                                                       \
          softfloat_exceptionFlags |= softfloat_flag_invalid;                  \
        vd_0 = defaultNaNF16UI;                                                \
      }                                                                        \
    }                                                                          \
    *dataOut = vd_0;                                                           \
  } break;                                                                     \
  case e32: {                                                                  \
    BODY32;                                                                    \
    if (is_propagate) {                                                        \
      auto ret = f32_classify(f32(vd_0));                                      \
      if (ret & 0x300) {                                                       \
        if (ret & 0x100)                                                       \
          softfloat_exceptionFlags |= softfloat_flag_invalid;                  \
        vd_0 = defaultNaNF32UI;                                                \
      }                                                                        \
    }                                                                          \
    *dataOut = vd_0;                                                           \
  } break;                                                                     \
  case e64: {                                                                  \
    BODY64;                                                                    \
    if (is_propagate) {                                                        \
      auto ret = f64_classify(f64(vd_0));                                      \
      if (ret & 0x300) {                                                       \
        if (ret & 0x100)                                                       \
          softfloat_exceptionFlags |= softfloat_flag_invalid;                  \
        vd_0 = defaultNaNF64UI;                                                \
      }                                                                        \
    }                                                                          \
    *dataOut = vd_0;                                                           \
  } break;                                                                     \
  }

#define VI_VFP_VV_LOOP_WIDE_REDUCTION(BODY16, BODY32)                          \
  RIF::RawDatumOperand vs2(dataA[i]);                                          \
  RIF::RawDatumOperand vd_0(*dataOut);                                         \
  switch (sew) {                                                               \
  case e16: {                                                                  \
    vs2 = f16_to_f32(vs2);                                                     \
    BODY16;                                                                    \
    if (is_propagate) {                                                        \
      auto ret = f32_classify(f32(vd_0));                                      \
      if (ret & 0x300) {                                                       \
        if (ret & 0x100)                                                       \
          softfloat_exceptionFlags |= softfloat_flag_invalid;                  \
        vd_0 = defaultNaNF32UI;                                                \
      }                                                                        \
    }                                                                          \
    *dataOut = vd_0;                                                           \
  } break;                                                                     \
  case e32: {                                                                  \
    vs2 = f32_to_f64(vs2);                                                     \
    BODY32;                                                                    \
    if (is_propagate) {                                                        \
      auto ret = f64_classify(f64(vd_0));                                      \
      if (ret & 0x300) {                                                       \
        if (ret & 0x100)                                                       \
          softfloat_exceptionFlags |= softfloat_flag_invalid;                  \
        vd_0 = defaultNaNF64UI;                                                \
      }                                                                        \
    }                                                                          \
    *dataOut = vd_0;                                                           \
  } break;                                                                     \
  }

/*=================================*/
/*           Mask family           */
/*=================================*/
#define VI_LOOP_MASK(BODY)                                                     \
  uint8_t vs2 = dataA[i];                                                      \
  uint8_t vs1 = dataB[i];                                                      \
  uint8_t vd = (BODY);                                                         \
  dataOut[i] = (vd & 1);

#define VI_LOOP_PSUEDO_MASK(BODY)                                              \
  uint8_t vs = dataA[i];                                                       \
  uint8_t vd = (BODY);                                                         \
  dataOut[i] = (vd & 1);

#define VI_LOOP_PSUEDO_NOINPUT_MASK(BODY)                                      \
  uint8_t vd = (BODY);                                                         \
  dataOut[i] = (vd & 1);

#define VI_CPOP_LOOP                                                           \
  auto vs2 = dataA[i];                                                         \
  pop_count += vs2;

#define VI_VFIRST_LOOP                                                         \
  auto vs2 = dataA[i];                                                         \
  if (vs2) {                                                                   \
    first = i;                                                                 \
    break;                                                                     \
  }

#define VI_VMSBF_LOOP                                                          \
  auto vs2 = dataA[i];                                                         \
  auto &vd = dataOut[i];                                                       \
  if (vs2)                                                                     \
    break;                                                                     \
  vd = true;

#define VI_VMSIF_LOOP                                                          \
  auto vs2 = dataA[i];                                                         \
  auto &vd = dataOut[i];                                                       \
  vd = true;                                                                   \
  if (vs2) {                                                                   \
    ++i;                                                                       \
    break;                                                                     \
  }

#define VI_VMSOF_LOOP                                                          \
  auto vs2 = dataA[i];                                                         \
  auto &vd = dataOut[i];                                                       \
  vd = false;                                                                  \
  if (vs2) {                                                                   \
    vd = true;                                                                 \
    ++i;                                                                       \
    break;                                                                     \
  }

#define VI_VIOTA_LOOP                                                          \
  auto vs2 = dataA[i];                                                         \
  auto &vd = dataOut[i];                                                       \
  vd = acculateMask;                                                           \
  acculateMask += vs2;

#define VI_VID_LOOP                                                            \
  auto &vd = dataOut[i];                                                       \
  vd = i;

/*=================================*/
/*      Load / store family        */
/*=================================*/
#define UNIT_STRIDE_LOAD dataOut[i] = dataA[i];
#define UNIT_STRIDE_STORE dataOut[i] = dataA[i];
#define INDEX_LOAD_8                                                           \
  {                                                                            \
    uint128_t index = dataB[i];                                                \
    uint128_t shift = dataASew / 8;                                            \
    dataOut[i] =                                                               \
        dataA[((index % a->length) * shift) % (((uint128_t)1) << 8) / shift];  \
  }

#define INDEX_LOAD_16                                                          \
  {                                                                            \
    uint128_t index = dataB[i];                                                \
    uint128_t shift = dataASew / 8;                                            \
    dataOut[i] =                                                               \
        dataA[((index % a->length) * shift) % (((uint128_t)1) << 16) / shift]; \
  }

#define INDEX_LOAD_32                                                          \
  {                                                                            \
    uint128_t index = dataB[i];                                                \
    uint128_t shift = dataASew / 8;                                            \
    dataOut[i] =                                                               \
        dataA[((index % a->length) * shift) % (((uint128_t)1) << 32) / shift]; \
  }

#define INDEX_LOAD_64                                                          \
  {                                                                            \
    uint128_t index = dataB[i];                                                \
    uint128_t shift = dataASew / 8;                                            \
    dataOut[i] =                                                               \
        dataA[((index % a->length) * shift) % (((uint128_t)1) << 64) / shift]; \
  }

#define INDEX_STORE_8                                                          \
  {                                                                            \
    uint128_t index = dataB[i];                                                \
    uint128_t shift = dataASew / 8;                                            \
    uint64_t real_id =                                                         \
        ((index % a->length) * shift) % (((uint128_t)1) << 8) / shift;         \
    dataOut[((index % a->length) * shift) % (((uint128_t)1) << 8) / shift] =   \
        dataA[i];                                                              \
  }

#define INDEX_STORE_16                                                         \
  {                                                                            \
    uint128_t index = dataB[i];                                                \
    uint128_t shift = dataASew / 8;                                            \
    dataOut[((index % a->length) * shift) % (((uint128_t)1) << 16) / shift] =  \
        dataA[i];                                                              \
  }

#define INDEX_STORE_32                                                         \
  {                                                                            \
    uint128_t index = dataB[i];                                                \
    uint128_t shift = dataASew / 8;                                            \
    dataOut[((index % a->length) * shift) % (((uint128_t)1) << 32) / shift] =  \
        dataA[i];                                                              \
  }

#define INDEX_STORE_64                                                         \
  {                                                                            \
    uint128_t index = dataB[i];                                                \
    uint128_t shift = dataASew / 8;                                            \
    dataOut[((index % a->length) * shift) % (((uint128_t)1) << 64) / shift] =  \
        dataA[i];                                                              \
  }

#define STRIDED_LOAD dataOut[i] = *(dataA + i * stride);
#define STRIDED_STORE *(dataOut + i * stride) = dataA[i];

// dummy macro-s
#define VI_CHECK_DDS(...)
#define VI_CHECK_DSS(...)
#define VI_CHECK_SSS(...)
#define require_vector(...)
#define require_extension(...)
#define VI_LOOP_BASE
#define VI_LOOP_END
#define P_SET_OV(...)

#endif
