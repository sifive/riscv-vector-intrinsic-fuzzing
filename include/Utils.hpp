// Utils.hpp
/*
Utility functions.
*/
#ifndef RIF_UTILS_HPP
#define RIF_UTILS_HPP

#include "Decode.hpp"
#include <cassert>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include <type_traits>

namespace RIF {

// default filename
extern std::string GraphVizFilename;
extern std::string CCodeFilename;
extern std::string InitialRootName;
extern uint32_t InitialLength;
extern uint32_t InitialSeed;
extern uint32_t NodesToGenerate;
extern std::mt19937 rng;
extern std::string VerificationMode;
extern bool VerifyTailPolicy;
extern bool VerifyMaskPolicy;
extern bool HasPolicy;
extern bool HasTA;
extern bool HasMA;

void parseArguments(int argc, char **argv);
void initializeRNG(uint32_t seed = 0xdeadbeef);
template <typename T, typename T2>
T getRandomNumber(T2 minValue, T2 maxValue, uint64_t *raw = nullptr) {
  static_assert(std::is_integral<T>::value,
                "non integral type should be handeled explicitly");
  T ret = std::uniform_int_distribution<T>(minValue, maxValue)(rng);
  if (raw != nullptr)
    *raw = ret;
  return ret;
}
template <>
float16_t getRandomNumber(int minValue, int maxValue, uint64_t *raw);
template <>
float32_t getRandomNumber(int minValue, int maxValue, uint64_t *raw);
template <>
float64_t getRandomNumber(int minValue, int maxValue, uint64_t *raw);

} // namespace RIF

#endif // #define RIF_UTILS_HPP
