// Value.hpp
/*
CustomValue template and declarations extended by MACRO in the .def file.
*/
#ifndef RIF_VALUE_HPP
#define RIF_VALUE_HPP
#include "Basic.hpp"

#include <iostream>
#include <memory>
#include <random>

namespace RIF {

#define CUSTOM_ONE_D_TYPE(CUSTOM_NAME, DATA_TYPE, DATA_WIDTH, DATA_CLASS,      \
                          MIN_VALUE, MAX_VALUE)                                \
  struct OneD##CUSTOM_NAME##Val : ValueBase {                                  \
    OneD##CUSTOM_NAME##Val(const std::string &id, const int length,            \
                           LmulType lmul)                                      \
        : ValueBase(CustomValType::OneD##CUSTOM_NAME, "OneD" #CUSTOM_NAME, id, \
                    #DATA_TYPE, length, DATA_CLASS, DATA_WIDTH, lmul) {        \
      ptr = new DATA_TYPE[length];                                             \
      raw = new uint64_t[length];                                              \
    }                                                                          \
    virtual ~OneD##CUSTOM_NAME##Val() {                                        \
      delete ptr;                                                              \
      delete raw;                                                              \
    }                                                                          \
    virtual void generateCCode(std::ostream &os) override;                     \
    void generateData() override;                                              \
    DATA_TYPE *ptr;                                                            \
    uint64_t *raw;                                                             \
  };                                                                           \
  DATA_TYPE *getRawPointer(OneD##CUSTOM_NAME##Val *val);
#include "CustomValue.def"
#undef CUSTOM_ONE_D_TYPE
#undef CUSTOM_SCALAR_TYPE

#define CUSTOM_SCALAR_TYPE(CUSTOM_NAME, DATA_TYPE, DATA_WIDTH, DATA_CLASS,     \
                           MIN_VALUE, MAX_VALUE)                               \
  struct Scalar##CUSTOM_NAME##Val : ValueBase {                                \
    Scalar##CUSTOM_NAME##Val(const std::string &id, const int length,          \
                             LmulType lmul)                                    \
        : ValueBase(CustomValType::Scalar##CUSTOM_NAME, "Scalar" #CUSTOM_NAME, \
                    id, #DATA_TYPE, 1, DATA_CLASS, DATA_WIDTH, lmul) {         \
      if (length != 1)                                                         \
        std::cerr                                                              \
            << "Receive length > 1 when creating scalar value, ignore\n";      \
      ptr = new DATA_TYPE;                                                     \
      raw = new uint64_t;                                                      \
    }                                                                          \
    virtual ~Scalar##CUSTOM_NAME##Val() {                                      \
      delete ptr;                                                              \
      delete raw;                                                              \
    }                                                                          \
    virtual void generateCCode(std::ostream &os) override;                     \
    void generateData() override;                                              \
    DATA_TYPE *ptr;                                                            \
    uint64_t *raw;                                                             \
  };                                                                           \
  DATA_TYPE *getRawPointer(Scalar##CUSTOM_NAME##Val *val);
#include "CustomValue.def"
#undef CUSTOM_ONE_D_TYPE
#undef CUSTOM_SCALAR_TYPE

} // namespace RIF
#endif // #define RIF_VALUE_HPP
