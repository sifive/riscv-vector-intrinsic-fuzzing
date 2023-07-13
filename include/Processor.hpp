#ifndef RIF_PROCESSOR_H
#define RIF_PROCESSOR_H
#include <cstdint>

enum VRM {
  RNU = 0, // round-to-nearest-up
  RNE,     // round-to-nearest-even
  RDN,     // round-to-nearest-down
  ROD,     // round-to-nearest-odd
  INVALID_RM
};

struct Processor {
  struct VectorUnit {
    unsigned vsew;      // sew
    VRM xrm = VRM::RNU; // rounding mode
    VRM get_vround_mode() { return xrm; }
  };
  VectorUnit VU;
};

extern Processor P;
extern Processor *p;

#endif