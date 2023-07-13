// Basic.cpp
/*
Implementations.
*/
#include "Basic.hpp"

#include <string>

using namespace std;

namespace RIF {

string ValueBase::getNameWithType() const { return typeID + "_" + id; }

bool isScalarValue(const ValueBase *value) {
  if (value->typeID.find("Op") != std::string::npos) {
    std::cerr << "[isScalarValue] Should not feed operator to isScalarValue\n";
    exit(1);
  }
  return value->typeID.find("Scalar") != std::string::npos;
}

bool isOneDValue(const ValueBase *value) {
  if (value->typeID.find("Op") != std::string::npos) {
    std::cerr << "[isScalarValue] Should not feed operator to isOneDValue\n";
    exit(1);
  }
  return value->typeID.find("OneD") != std::string::npos;
}

DataTypeEnum getDataTypeEnum(const char *dataTypeString) {
  if (strcmp(dataTypeString, "uint8_t") == 0)
    return DataTypeEnum::Uint8_t;
  else if (strcmp(dataTypeString, "uint16_t") == 0)
    return DataTypeEnum::Uint16_t;
  else if (strcmp(dataTypeString, "uint32_t") == 0)
    return DataTypeEnum::Uint32_t;
  else if (strcmp(dataTypeString, "uint64_t") == 0)
    return DataTypeEnum::Uint64_t;
  else if (strcmp(dataTypeString, "int8_t") == 0)
    return DataTypeEnum::Int8_t;
  else if (strcmp(dataTypeString, "int16_t") == 0)
    return DataTypeEnum::Int16_t;
  else if (strcmp(dataTypeString, "int32_t") == 0)
    return DataTypeEnum::Int32_t;
  else if (strcmp(dataTypeString, "int64_t") == 0)
    return DataTypeEnum::Int64_t;
  else if (strcmp(dataTypeString, "float16_t") == 0)
    return DataTypeEnum::Float16_t;
  else if (strcmp(dataTypeString, "float32_t") == 0)
    return DataTypeEnum::Float32_t;
  else if (strcmp(dataTypeString, "float64_t") == 0)
    return DataTypeEnum::Float64_t;
  else if (strcmp(dataTypeString, "ptrdiff_t") == 0)
    return DataTypeEnum::Ptrdiff_t;
  else if (strcmp(dataTypeString, "size_t") == 0)
    return DataTypeEnum::Size_t;
  else
    assert(false && "Unhandled type");
}

bool isIntegral(DataTypeEnum dt) {
  return dt == DataTypeEnum::Uint8_t || dt == DataTypeEnum::Uint16_t ||
         dt == DataTypeEnum::Uint32_t || dt == DataTypeEnum::Uint64_t ||
         dt == DataTypeEnum::Int8_t || dt == DataTypeEnum::Int16_t ||
         dt == DataTypeEnum::Int32_t || dt == DataTypeEnum::Int64_t ||
         dt == DataTypeEnum::Ptrdiff_t || dt == DataTypeEnum::Size_t;
}

bool isWideningOperator(OperatorBase *op) {
  return op->opAttr & WideningOperation;
}

// is X Widen of Y
bool isWideningValue(ValueBase *x, ValueBase *y) {
  if (x == nullptr || y == nullptr)
    return false;
  return x->typeInfo->sew.to_int() == y->typeInfo->sew.to_int() * 2;
}

bool isNarrowingOperator(OperatorBase *op) {
  return op->opAttr & NarrowingOperation;
}

// is X Narrow of Y
bool isNarrowingValue(ValueBase *x, ValueBase *y) {
  if (x == nullptr || y == nullptr)
    return false;
  return x->typeInfo->sew.to_int() * 2 == y->typeInfo->sew.to_int();
}

bool hasMask(const OperatorBase *op) { return op->opAttr & MaskedOperation; }

bool hasNonmask(const OperatorBase *op) {
  return op->opAttr & NonmaskedOperation;
}

bool hasTA(const OperatorBase *op) { return op->opAttr & TailAgnostic; }

bool hasTU(const OperatorBase *op) { return op->opAttr & TailUndisturbed; }

bool hasMA(const OperatorBase *op) { return op->opAttr & MaskAgnostic; }

bool hasMU(const OperatorBase *op) { return op->opAttr & MaskUndisturbed; }

bool hasTAMA(const OperatorBase *op) { return hasTA(op) && hasMA(op); }

bool hasTAMU(const OperatorBase *op) { return hasTA(op) && hasMU(op); }

bool hasTUMA(const OperatorBase *op) { return hasTU(op) && hasMA(op); }

bool hasTUMU(const OperatorBase *op) { return hasTU(op) && hasMU(op); }

bool isExplicitPolicy(OperatorBase *op) {
  return hasTA(op) || hasTU(op) || hasMA(op) || hasMU(op);
}

bool haveTailPolicy(OperatorBase *op) { return hasTA(op) || hasTU(op); }

bool haveMaskPolicy(OperatorBase *op) { return hasMA(op) || hasMU(op); }

ValueBase *getVd(OperatorBase *op) { return op->outputs[0]; }

ValueBase *getMask(OperatorBase *op) {
  ValueBase *mask = nullptr;
  if (hasMask(op))
    mask = op->inputs[0];
  return mask;
}

ValueBase *getMaskedoff(OperatorBase *op) {
  ValueBase *maskedoff = nullptr;
  if (hasMask(op)) {
    if (op->opAttr & ReductionOperation && !hasTU(op))
      maskedoff = nullptr;
    else if (op->opAttr & NoMaskedOff)
      maskedoff = nullptr;
    else
      maskedoff = op->inputs[1];
  } else if (op->opAttr & MulAddOperation)
    maskedoff = op->inputs[0];
  else if (hasTU(op))
    maskedoff = op->inputs[0];
  return maskedoff;
}

ValueBase *getVs2(OperatorBase *op) {
  ValueBase *vs2 = nullptr;
  if (!(op->opAttr & NoInputOperation)) {
    if (op->opAttr & MulAddOperation)
      vs2 = hasMask(op) ? op->inputs[3] : op->inputs[2];
    else if (op->opAttr & ReductionOperation)
      vs2 = hasMask(op) ? hasTU(op) ? op->inputs[2] : op->inputs[1]
            : hasTU(op) ? op->inputs[1]
                        : op->inputs[0];
    else if (op->opAttr & MergeOperation) {
      assert(hasNonmask(op));
      vs2 = hasTU(op) ? op->inputs[2] : op->inputs[1];
    } else
      vs2 = hasMask(op)
                ? (op->opAttr & NoMaskedOff ? op->inputs[1] : op->inputs[2])
            : hasTU(op) ? op->inputs[1]
                        : op->inputs[0];
  }
  return vs2;
}

bool isExistVs1Rs1(OperatorBase *op) {
  std::string typeID = op->typeID;
  std::string operandType = typeID.substr(typeID.find("_") + 1);

  if (operandType == "m")
    return false;

  if (ends_with(typeID, "_v") || ends_with(typeID, "_x") ||
      ends_with(typeID, "_w") || ends_with(typeID, "_f"))
    return false;

  if (operandType == "vf2" || operandType == "vf4" || operandType == "vf8")
    return false;

  if (op->opAttr & ReductionOperation)
    return false;

  return true;
}

ValueBase *getVs1(OperatorBase *op) {
  ValueBase *vs1 = nullptr;
  if (!(op->opAttr & NoInputOperation) && isExistVs1Rs1(op)) {
    if (op->opAttr & MulAddOperation)
      vs1 = hasMask(op) ? op->inputs[2] : op->inputs[1];
    else if (op->opAttr & ReductionOperation)
      return vs1;
    else if (op->opAttr & MergeOperation) {
      assert(hasNonmask(op));
      vs1 = hasTU(op) ? op->inputs[3] : op->inputs[2];
    } else
      vs1 = hasMask(op)
                ? (op->opAttr & NoMaskedOff ? op->inputs[2] : op->inputs[3])
            : hasTU(op) ? op->inputs[2]
                        : op->inputs[1];
  }
  return vs1;
}

bool isMaskOfOperator(OperatorBase *op, ValueBase *value) {
  return getMask(op) == value;
}

bool isMaskedoffOfOperator(OperatorBase *op, ValueBase *value) {
  return getMaskedoff(op) == value;
}

bool isVs2OfOperator(OperatorBase *op, ValueBase *value) {
  return getVs2(op) == value;
}

bool isVs1OfOperator(OperatorBase *op, ValueBase *value) {
  return getVs1(op) == value;
}

void initializeLmul(OperatorBase *op) {
  std::string typeID = op->typeID;
  std::string operandType = typeID.substr(typeID.find("_") + 1);

  int gap = op->typeInfo->lmul - getSmallestLmulForSew(op->typeInfo->sew);
  assert(gap >= 0);

  for (auto input : op->inputs) {
    assert(input != nullptr);
    input->typeInfo = TypeInfo::setLmul(
        *input->typeInfo,
        static_cast<LmulType>(gap +
                              getSmallestLmulForSew(input->typeInfo->sew)));
  }

  auto vd = getVd(op);
  assert(vd != nullptr);
  vd->typeInfo = TypeInfo::setLmul(
      *vd->typeInfo,
      static_cast<LmulType>(gap + getSmallestLmulForSew(vd->typeInfo->sew)));

  if (op->opAttr & ReductionOperation) {
    // Note: Output of reduction result is fixed to m1
    vd->typeInfo = TypeInfo::create(LmulType::m1, vd->typeInfo->sew,
                                    vd->typeInfo->typeClass);
  }

  auto maskedoff = getMaskedoff(op);
  if (maskedoff)
    maskedoff->typeInfo = vd->typeInfo;
}

bool ends_with(std::string const &value, std::string const &ending) {
  if (ending.size() > value.size())
    return false;
  return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

LmulType getSmallestLmulForSew(SewType sew) {
  static std::map<int, int> log2LUT = {{1, 0},  {2, 1},  {4, 2}, {8, 3},
                                       {16, 4}, {32, 5}, {64, 6}};
  return static_cast<LmulType>(log2LUT[sew.to_int()] - 3);
}

} // namespace RIF
