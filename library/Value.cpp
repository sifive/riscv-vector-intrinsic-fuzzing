// Value.cpp
#include "Value.hpp"
#include "Utils.hpp"

#include <iostream>

namespace RIF {

#define CUSTOM_ONE_D_TYPE(CUSTOM_NAME, DATA_TYPE, DATA_WIDTH, DATA_CLASS,      \
                          MIN_VALUE, MAX_VALUE)                                \
  DATA_TYPE *getRawPointer(OneD##CUSTOM_NAME##Val *val) { return val->ptr; }   \
  void OneD##CUSTOM_NAME##Val::generateData() {                                \
    auto length = this->length;                                                \
    auto data = getRawPointer(this);                                           \
    for (int i = 0; i < length; ++i)                                           \
      data[i] = getRandomNumber<DATA_TYPE>(MIN_VALUE, MAX_VALUE, &raw[i]);     \
  }                                                                            \
  void OneD##CUSTOM_NAME##Val::generateCCode(std::ostream &os) {               \
    os << this->dataTypeID << " " << this->id << "[" << this->length           \
       << "];\n";                                                              \
  }
#include "CustomValue.def"
#undef CUSTOM_ONE_D_TYPE
#undef CUSTOM_SCALAR_TYPE

#define CUSTOM_SCALAR_TYPE(CUSTOM_NAME, DATA_TYPE, DATA_WIDTH, DATA_CLASS,     \
                           MIN_VALUE, MAX_VALUE)                               \
  DATA_TYPE *getRawPointer(Scalar##CUSTOM_NAME##Val *val) { return val->ptr; } \
  void Scalar##CUSTOM_NAME##Val::generateData() {                              \
    auto data = getRawPointer(this);                                           \
    *data = getRandomNumber<DATA_TYPE>(MIN_VALUE, MAX_VALUE, raw);             \
  }                                                                            \
  void Scalar##CUSTOM_NAME##Val::generateCCode(std::ostream &os) {             \
    os << this->dataTypeID << " " << this->id << ";\n";                        \
  }
#include "CustomValue.def"
#undef CUSTOM_ONE_D_TYPE
#undef CUSTOM_SCALAR_TYPE

} // namespace RIF
