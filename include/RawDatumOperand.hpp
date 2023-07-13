// RawDatumOperand.hpp
/*
The spike golden headers have 2 problems that needs to be resolved.
1. (TODO, FIXME) Don't follow SSA. For example, code like vmacc_vv.h

  // vmacc.vv: vd[i] = +(vs1[i] * vs2[i]) + vd[i]
  VI_VV_LOOP
  ({
    vd = vs1 * vs2 + vd;
  })

2. Not strongly typed. For example, code like vfadd_vv.h

  // vfadd.vv vd, vs2, vs1
  VI_VFP_VV_LOOP
  ({
    vd = f16_add(vs1, vs2);
  },
  {
    vd = f32_add(vs1, vs2);
  },
  {
    vd = f64_add(vs1, vs2);
  })

Primitive C/C++ arithmetic can't compute/compile the spike headers correctly,
whichi is why we need to have this RawDatumOperand wrapper class for it.
*/
#ifndef RIF_RAW_DATUM_OPERAND_HPP
#define RIF_RAW_DATUM_OPERAND_HPP

#include <cstdint>

#include "softfloat.h"

namespace RIF {

struct RawDatumOperand {

  typedef union {
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    uint8_t ui8;
    uint16_t ui16;
    uint32_t ui32;
    uint64_t ui64;
    float16_t f16;
    float32_t f32;
    float64_t f64;
  } datum_t;

  RawDatumOperand() {}
  RawDatumOperand(const int8_t v) { datum.i8 = v; };
  RawDatumOperand(const int16_t v) { datum.i16 = v; };
  RawDatumOperand(const int32_t v) { datum.i32 = v; };
  RawDatumOperand(const int64_t v) { datum.i64 = v; };
  RawDatumOperand(const uint8_t v) { datum.ui8 = v; };
  RawDatumOperand(const uint16_t v) { datum.ui16 = v; };
  RawDatumOperand(const uint32_t v) { datum.ui32 = v; };
  RawDatumOperand(const uint64_t v) { datum.ui64 = v; };
  RawDatumOperand(const float16_t v) : v(v.v) { datum.f16 = v; };
  RawDatumOperand(const float32_t v) : v(v.v) { datum.f32 = v; };
  RawDatumOperand(const float64_t v) : v(v.v) { datum.f64 = v; };

  operator int8_t() const { return datum.i8; }
  operator int16_t() const { return datum.i16; }
  operator int32_t() const { return datum.i32; }
  operator int64_t() const { return datum.i64; }
  operator uint8_t() const { return datum.ui8; }
  operator uint16_t() const { return datum.ui16; }
  operator uint32_t() const { return datum.ui32; }
  operator uint64_t() const { return datum.ui64; }
  operator float16_t() const { return datum.f16; }
  operator float32_t() const { return datum.f32; }
  operator float64_t() const { return datum.f64; }

  RawDatumOperand &operator=(const int8_t i8) {
    datum.i8 = i8;
    return *this;
  }
  RawDatumOperand &operator=(const int16_t i16) {
    datum.i16 = i16;
    return *this;
  }
  RawDatumOperand &operator=(const int32_t i32) {
    datum.i32 = i32;
    return *this;
  }
  RawDatumOperand &operator=(const int64_t i64) {
    datum.i64 = i64;
    return *this;
  }
  RawDatumOperand &operator=(const uint8_t ui8) {
    datum.ui8 = ui8;
    return *this;
  }
  RawDatumOperand &operator=(const uint16_t ui16) {
    datum.ui16 = ui16;
    return *this;
  }
  RawDatumOperand &operator=(const uint32_t ui32) {
    datum.ui32 = ui32;
    return *this;
  }
  RawDatumOperand &operator=(const uint64_t ui64) {
    datum.ui64 = ui64;
    return *this;
  }
  RawDatumOperand &operator=(const float16_t f16) {
    datum.f16 = f16;
    v = f16.v;
    return *this;
  }
  RawDatumOperand &operator=(const float32_t f32) {
    datum.f32 = f32;
    v = f32.v;
    return *this;
  }
  RawDatumOperand &operator=(const float64_t f64) {
    datum.f64 = f64;
    v = f64.v;
    return *this;
  }

  datum_t datum;
  uint64_t v;
};

} // namespace RIF

#endif
