#include "softfloat.h"
#include "specialize.h"
#include "gtest/gtest.h"

#include <cstdio>
#include <iostream>

#include "RawDatumOperand.hpp"

using namespace std;

#define e16 16
#define e32 32
#define e64 64
/* Convenience wrappers to simplify softfloat code sequences */
#define isBoxedF16(r)                                                          \
  (isBoxedF32(r) && ((uint64_t)((r.v[0] >> 16) + 1) == ((uint64_t)1 << 48)))
#define unboxF16(r) (isBoxedF16(r) ? (uint16_t)r.v[0] : defaultNaNF16UI)
#define isBoxedF32(r) (isBoxedF64(r) && ((uint32_t)((r.v[0] >> 32) + 1) == 0))
#define unboxF32(r) (isBoxedF32(r) ? (uint32_t)r.v[0] : defaultNaNF32UI)
#define isBoxedF64(r) ((r.v[1] + 1) == 0)
#define unboxF64(r) (isBoxedF64(r) ? r.v[0] : defaultNaNF64UI)
typedef float128_t freg_t;
inline float16_t f16(uint16_t v) { return {v}; }
inline float32_t f32(uint32_t v) { return {v}; }
inline float64_t f64(uint64_t v) { return {v}; }
inline float16_t f16(freg_t r) { return f16(unboxF16(r)); }
inline float32_t f32(freg_t r) { return f32(unboxF32(r)); }
inline float64_t f64(freg_t r) { return f64(unboxF64(r)); }
inline freg_t freg(float16_t f) {
  return {((uint64_t)-1 << 16) | f.v, (uint64_t)-1};
}
inline freg_t freg(float32_t f) {
  return {((uint64_t)-1 << 32) | f.v, (uint64_t)-1};
}
inline freg_t freg(float64_t f) { return {f.v, (uint64_t)-1}; }
inline freg_t freg(float128_t f) { return f; }
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

#define VI_VFP_VV_LOOP(BODY16, BODY32, BODY64)                                 \
  switch (sew) {                                                               \
  case e16:                                                                    \
    BODY16;                                                                    \
    break;                                                                     \
  case e32:                                                                    \
    BODY32;                                                                    \
    break;                                                                     \
  case e64:                                                                    \
    BODY32;                                                                    \
    break;                                                                     \
  default:                                                                     \
    assert(0);                                                                 \
    break;                                                                     \
  }

// Simulating behavior when Spike header is trying to import vfadd_vv.h
TEST(Datum, ResolveStronglyTyped) {
  RIF::RawDatumOperand vs1(ui64_to_f16(0xdeadbeef));
  RIF::RawDatumOperand vs2(ui64_to_f16(0xcafebabe));
  RIF::RawDatumOperand vd;

  size_t sew = 32;

  VI_VFP_VV_LOOP({ vd = f16_add(vs1, vs2); }, { vd = f32_add(vs1, vs2); },
                 { vd = f64_add(vs1, vs2); });
}

// Simulate behavior for vneg_v.h
TEST(Datum, AccessSoftfloatRawData) {
  RIF::RawDatumOperand vs(ui64_to_f32(0xdeadbeef));
  RIF::RawDatumOperand vd;

  size_t sew = 32;
  VI_VFP_V_LOOP({ vd = fsgnj16(vs.v, vs.v, true, false); },
                { vd = fsgnj32(vs.v, vs.v, true, false); },
                { vd = fsgnj64(vs.v, vs.v, true, false); });
}
