#include "TypeInfo.hpp"

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>

using namespace RIF;

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

std::map<SewType::Value, std::set<LmulType>> TypeInfo::validSewLmul = {
    {SewType::Value::e8,
     {LmulType::mf8, LmulType::mf4, LmulType::mf2, LmulType::m1, LmulType::m2,
      LmulType::m4, LmulType::m8}},
    {SewType::Value::e16,
     {LmulType::mf4, LmulType::mf2, LmulType::m1, LmulType::m2, LmulType::m4,
      LmulType::m8}},
    {SewType::Value::e32,
     {LmulType::mf2, LmulType::m1, LmulType::m2, LmulType::m4, LmulType::m8}},
    {SewType::Value::e64,
     {LmulType::m1, LmulType::m2, LmulType::m4, LmulType::m8}},
};

static std::map<LmulType, size_t> lmulToIdx = {
    {LmulType::mf8, 0}, {LmulType::mf4, 1}, {LmulType::mf2, 2},
    {LmulType::m1, 3},  {LmulType::m2, 4},  {LmulType::m4, 5},
    {LmulType::m8, 6},
};

static constexpr size_t TotalSew =
    static_cast<size_t>(SewType::Value::NumberOfSews);
static constexpr size_t TotalLmul =
    static_cast<size_t>(LmulType::NumberOfLmuls);
static TypeInfo *typeInfos[TotalSew][TotalLmul][NumberOfTypeClasses];

SewType::SewType(int sew) {
  switch (sew) {
  // this case is for InitializeOp in Operator.hpp
  case 0:
    break;
  case 8:
    value = Value::e8;
    break;
  case 16:
    value = Value::e16;
    break;
  case 32:
    value = Value::e32;
    break;
  case 64:
    value = Value::e64;
    break;
  default:
    assert(false && "unsupported sew!");
  }
}

SewType::SewType(SewType::Value sew) : value(sew) {}

std::string SewType::to_string() const { return std::to_string(to_int()); }

int SewType::to_int() const { return 8 << static_cast<int>(value); }

size_t SewType::to_index() const { return static_cast<size_t>(value); }

TypeInfo *TypeInfo::create(LmulType lmul, SewType sew, TypeClass typeClass) {
  static bool inited = false;
  // Isn't fully thread-safe, but I assume we don't need multi-therad.
  if (!inited) {
    memset(typeInfos, 0, sizeof(typeInfos));
    for (auto it : validSewLmul) {
      const auto sew = it.first;
      for (LmulType lmul : it.second) {
        size_t sewIdx = static_cast<size_t>(sew);
        size_t lmulIdx = lmulToIdx[lmul];
        for (size_t typeClassIdx = 0; typeClassIdx < NumberOfTypeClasses;
             ++typeClassIdx) {
          typeInfos[sewIdx][lmulIdx][typeClassIdx] = new TypeInfo(
              lmul, SewType{sew}, static_cast<TypeClass>(typeClassIdx));
        }
      }
    }
    inited = true;
  }

  static TypeInfo *dummy = new TypeInfo(lmul, sew, typeClass);
  // Used for Initialize node.
  if (typeClass == NumberOfTypeClasses)
    return dummy;

  assert(lmulToIdx.find(lmul) != lmulToIdx.end());

  size_t sewIdx = sew.to_index();
  size_t lmulIdx = lmulToIdx[lmul];
  size_t typeClassIdx = static_cast<size_t>(typeClass);

  if (!typeInfos[sewIdx][lmulIdx][typeClassIdx]) {
    std::cerr
        << "WARNING: calling ctor for TypeInfo with invalid sew/lmul pair\n";
    exit(1);
  }
  return typeInfos[sewIdx][lmulIdx][typeClassIdx];
}

TypeInfo *TypeInfo::getNarrowed(const TypeInfo &typeInfo, TypeClass typeClass) {
  if (typeInfo.sew.to_int() == 8) {
    std::cerr << "sew = 8, can't be narrowed\n";
    exit(1);
  }
  size_t sewIdx = typeInfo.sew.to_index();
  size_t lmulIdx = lmulToIdx[typeInfo.lmul];
  return typeInfos[sewIdx - 1][lmulIdx - 1][typeClass];
}

TypeInfo *TypeInfo::getWidened(const TypeInfo &typeInfo, TypeClass typeClass) {
  if (typeInfo.sew.to_int() == 64) {
    std::cerr << "sew = 64, can't be widened\n";
    exit(1);
  }
  size_t sewIdx = typeInfo.sew.to_index();
  size_t lmulIdx = lmulToIdx[typeInfo.lmul];
  return typeInfos[sewIdx + 1][lmulIdx + 1][typeClass];
}

TypeInfo *TypeInfo::setLmul(const TypeInfo &typeInfo, LmulType lmul) {
  if (!validSewLmul[typeInfo.sew].count(lmul)) {
    std::cerr << "Sew " << typeInfo.sew.to_int() << " can't be set to "
              << std::string(LMUL_STR(lmul)) << "\n";
    exit(1);
  }
  size_t sewIdx = typeInfo.sew.to_index();
  size_t lmulIdx = lmulToIdx[lmul];
  size_t typeClassIdx = static_cast<size_t>(typeInfo.typeClass);
  return typeInfos[sewIdx][lmulIdx][typeClassIdx];
}
