/*
TypeInfo
*/
#ifndef RIF_TYPEINFO_HPP
#define RIF_TYPEINFO_HPP

#include <cassert>
#include <string>

#include <map>
#include <set>

namespace RIF {

enum TypeClass {
  SIGNED_INT,
  UNSIGNED_INT,
  FLOAT,
  BOOL,
  NumberOfTypeClasses,
};

#define TYPE_CLASS_STR(TC)                                                     \
  (TC) == SIGNED_INT     ? "int"                                               \
  : (TC) == UNSIGNED_INT ? "uint"                                              \
  : (TC) == FLOAT        ? "float"                                             \
  : (TC) == BOOL         ? "bool"                                              \
                 : (assert("Unknown type class!?"), "<SOME_THING_WRONG>")

#define TYPE_CLASS_SHORT_STR(TC)                                               \
  (TC) == SIGNED_INT     ? "i"                                                 \
  : (TC) == UNSIGNED_INT ? "u"                                                 \
  : (TC) == FLOAT        ? "f"                                                 \
  : (TC) == BOOL         ? "b"                                                 \
                 : (assert("Unknown type class!?"), "<SOME_THING_WRONG>")

enum LmulType {
  mf8,
  mf4,
  mf2,
  m1,
  m2,
  m4,
  m8,
  NumberOfLmuls,
};
#define LMUL_STR(LMUL)                                                         \
  (LMUL) == LmulType::mf8   ? "mf8"                                            \
  : (LMUL) == LmulType::mf4 ? "mf4"                                            \
  : (LMUL) == LmulType::mf2 ? "mf2"                                            \
  : (LMUL) == LmulType::m1  ? "m1"                                             \
  : (LMUL) == LmulType::m2  ? "m2"                                             \
  : (LMUL) == LmulType::m4  ? "m4"                                             \
  : (LMUL) == LmulType::m8                                                     \
      ? "m8"                                                                   \
      : (assert("Unknown type class!?"), "<SOME_THING_WRONG>")

class SewType {
public:
  enum class Value { e8, e16, e32, e64, NumberOfSews };

  explicit SewType(int);
  explicit SewType(Value);

  operator Value() const { return value; }

  std::string to_string() const;
  int to_int() const;
  size_t to_index() const;

private:
  // The underlying value of SEW
  Value value;
};

struct TypeInfo {
  static TypeInfo *create(LmulType lmul, SewType sew, TypeClass typeClass);

  static TypeInfo *getNarrowed(const TypeInfo &typeInfo, TypeClass typeClass);
  static TypeInfo *getWidened(const TypeInfo &typeInfo, TypeClass typeClass);
  static TypeInfo *setLmul(const TypeInfo &typeInfo, LmulType lmul);

  TypeInfo(const TypeInfo &) = default;
  TypeInfo &operator=(const TypeInfo &) = delete;

  bool operator==(const TypeInfo &rhs) const {
    return lmul == rhs.lmul && sew == rhs.sew && typeClass == rhs.typeClass;
  }
  bool operator!=(const TypeInfo &rhs) const {
    return lmul != rhs.lmul || sew != rhs.sew || typeClass != rhs.typeClass;
  }

  static std::map<SewType::Value, std::set<LmulType>> validSewLmul;
  const LmulType lmul;
  const SewType sew;

  const TypeClass typeClass;

  const std::string scalarTypeName;
  const std::string vectorTypeName;
  const std::string shortScalarTypeName;
  const std::string shortVectorTypeName;
  const std::string setvlTypeName;
  const std::string setvlmaxTypeName;

  bool isIntegerType() const {
    return isSignedIntegerType() || isUnsigedIntegerType();
  };
  bool isSignedIntegerType() const { return typeClass == SIGNED_INT; };
  bool isUnsigedIntegerType() const { return typeClass == UNSIGNED_INT; };
  bool isFloatType() const { return typeClass == FLOAT; };
  bool isBoolType() const { return typeClass == BOOL; };

private:
  TypeInfo(LmulType lmul, SewType sew, TypeClass typeClass)
      : lmul(lmul), sew(sew), typeClass(typeClass),
        scalarTypeName(std::string(TYPE_CLASS_STR(typeClass)) +
                       sew.to_string() + "_t"),
        vectorTypeName(("v" + std::string(TYPE_CLASS_STR(typeClass)) +
                        sew.to_string() + std::string(LMUL_STR(lmul)) + "_t")),
        shortScalarTypeName(std::string(TYPE_CLASS_SHORT_STR(typeClass)) +
                            sew.to_string()),
        shortVectorTypeName((std::string(TYPE_CLASS_SHORT_STR(typeClass)) +
                             sew.to_string() + std::string(LMUL_STR(lmul)))),
        setvlTypeName("vsetvl_e" + sew.to_string() +
                      std::string(LMUL_STR(lmul))),
        setvlmaxTypeName("vsetvlmax_e" + sew.to_string() +
                         std::string(LMUL_STR(lmul))) {}
};

} // namespace RIF

#endif // #define RIF_TYPEINFO_HPP
