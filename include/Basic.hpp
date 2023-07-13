// Basic.hpp
/*
This file declares the base class of basic components of the graph - Value and
Operator.

Value is the basic node type of the graph, with informations of
- type attributes: data width, sew, lmul
- strings used for code generation: typeID, id, dataTypeID
- linkages to other Values: currently using std::vector as the container

Operator is derived from value becuase it also needs all of the informations
above. Aside from that, an operator will have restrictions of the types of its
input and output, and the attributes of that operator (e.g. whether the
intrinsic function of this operator has an 'vl' as the last parameter, whether
the operator is masked).
*/
#ifndef RIF_BASIC_HPP
#define RIF_BASIC_HPP

#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "TypeInfo.hpp"

#include "softfloat.h"

namespace RIF {

struct ValueBase;
struct OperatorBase;

enum CustomValType {
// Derived Value
#define CUSTOM_ONE_D_TYPE(CUSTOM_NAME, ...) OneD##CUSTOM_NAME,
#include "CustomValue.def"
#undef CUSTOM_ONE_D_TYPE
#undef CUSTOM_SCALAR_TYPE

#define CUSTOM_SCALAR_TYPE(CUSTOM_NAME, ...) Scalar##CUSTOM_NAME,
#include "CustomValue.def"
#undef CUSTOM_ONE_D_TYPE
#undef CUSTOM_SCALAR_TYPE
  NumberOfValTypes,
  // Derived Operator
  Initialize,
#define CUSTOM_OP_TYPE(OP_TYPE, ...) OP_TYPE,
#include "CustomOperator.def"
#undef CUSTOM_OP_TYPE
  NumberOfOpTypes,
};

enum DataTypeEnum {
  Uint8_t,
  Uint16_t,
  Uint32_t,
  Uint64_t,
  Int8_t,
  Int16_t,
  Int32_t,
  Int64_t,
  Float16_t,
  Float32_t,
  Float64_t,
  Ptrdiff_t,
  Size_t,
  Not_set // Don't set for `Operator`
};

DataTypeEnum getDataTypeEnum(const char *dataTypeString);
bool isIntegral(DataTypeEnum dt);

struct ValueBase {
  // ctor for derived Value
  ValueBase(const CustomValType &type, const std::string &typeID,
            const std::string &id, const std::string &dataTypeID,
            const int length, TypeClass typeClass, int dataWidth, LmulType lmul)
      : type(type), typeID(typeID), id(id), dataTypeID(dataTypeID),
        length(length), inputs(1, nullptr),
        typeInfo(TypeInfo::create(lmul, SewType{dataWidth}, typeClass)),
        dt(getDataTypeEnum(dataTypeID.c_str())) {}

  // ctor for derived Operator
  ValueBase(const CustomValType &type, const std::string &typeID,
            const std::string &id, const unsigned numOfInputs,
            TypeClass typeClass, int dataWidth, LmulType lmul)
      : type(type), typeID(typeID), id(id), dataTypeID(""), length(0),
        inputs(numOfInputs, nullptr), outputs(1, nullptr),
        typeInfo(TypeInfo::create(lmul, SewType{dataWidth}, typeClass)),
        dt(DataTypeEnum::Not_set) {}

  virtual ~ValueBase() = default;

  std::string getNameWithType() const;

  virtual void generateCCode(std::ostream &os) = 0;
  virtual void generateData() = 0;

  const CustomValType type;
  const std::string typeID;
  const std::string id;
  const std::string dataTypeID;

  std::vector<ValueBase *> inputs;
  std::vector<ValueBase *> outputs;

  int length;
  TypeInfo *typeInfo;
  DataTypeEnum dt;
};

bool isScalarValue(const ValueBase *value);
bool isOneDValue(const ValueBase *value);

using OperatorAttrT = uint32_t;
enum OperatorAttr : OperatorAttrT {
  HaveVLParameter = 1,
  NoVLParameter = 1 << 1,
  MaskedOperation = 1 << 2,
  NonmaskedOperation = 1 << 3,
  MulAddOperation = 1 << 4,
  MergeOperation = 1 << 5,
  ReductionOperation = 1 << 6,
  LogicalMaskOperation = 1 << 7,
  NoInputOperation = 1 << 8,
  LoadOperation = 1 << 9,
  StoreOperation = 1 << 10,
  VoidOperation = 1 << 11,
  WideningOperation = 1 << 12,
  NarrowingOperation = 1 << 13,
  NoMaskedOff = 1 << 14,
  ExtensionOperation = 1 << 15,
  TailAgnostic = 1 << 16,
  TailUndisturbed = 1 << 17,
  MaskAgnostic = 1 << 18,
  MaskUndisturbed = 1 << 19,
};

struct OperatorBase : ValueBase {

  OperatorBase(const CustomValType &type, const std::string &typeID,
               const std::string &id, const OperatorAttrT opAttr,
               const unsigned numOfInputs,
               const std::initializer_list<CustomValType> inputTypes,
               const CustomValType outputType, int dataWidth, LmulType lmul,
               TypeClass typeClass)
      : ValueBase(type, typeID, id, numOfInputs, typeClass, dataWidth, lmul),
        opAttr(opAttr), inputTypes(inputTypes), outputType(outputType) {}

  virtual ~OperatorBase() = default;

  // returns 1 if fail
  int addInput(int inputIdx, ValueBase *input) {
    if (inputIdx >= inputs.size()) {
      std::cerr << "addInput: inputIdx is out of range, abort.\n";
      return 1;
    }
    if (inputTypes[inputIdx] != input->type) {
      std::cerr << "addInput: Encounter mismatch type when adding input "
                << inputIdx << " of operator " << id << "\n";
      return 1;
    }
    if (input->type >= NumberOfValTypes) {
      std::cerr << "addInput: Adding a non-value node of type '"
                << input->typeID << "' as an input\n";
      return 1;
    }
    if (inputs[inputIdx] != nullptr)
      std::cerr << "Warning: setting input of index " << inputIdx
                << "that is already occupied.\n";

    inputs[inputIdx] = input;
    input->outputs.push_back(this);
    return 0;
  }
  // return 1 if fail
  int addOutput(ValueBase *output) {
    if (outputType != output->type && type != Initialize) {
      std::cerr << "addOutput: Encounter mismatch type for operator " << id
                << "\n";
      return 1;
    }
    if (output->type >= NumberOfValTypes) {
      std::cerr << "addOutput: Adding a non-value node of type '"
                << output->typeID << "' as an output\n";
      return 1;
    }
    assert(outputs.size() == 1 && output->inputs.size() == 1);
    if (outputs[0] != nullptr)
      std::cerr << "Warning: setting output that is already occupied\n";

    outputs[0] = output;
    output->inputs[0] = this;
    return 0;
  }

  const OperatorAttrT opAttr;

  const std::vector<CustomValType> inputTypes;
  const CustomValType outputType;
};

// Utility (sugar) functions for readability
bool hasMask(const OperatorBase *op);
bool hasNonmask(const OperatorBase *op);
bool hasTA(const OperatorBase *op);
bool hasTU(const OperatorBase *op);
bool hasMA(const OperatorBase *op);
bool hasMU(const OperatorBase *op);
bool hasTAMA(const OperatorBase *op);
bool hasTAMU(const OperatorBase *op);
bool hasTUMA(const OperatorBase *op);
bool hasTUMU(const OperatorBase *op);
bool isExplicitPolicy(OperatorBase *op);
bool haveTailPolicy(OperatorBase *op);
bool haveMaskPolicy(OperatorBase *op);

bool isMaskOfOperator(OperatorBase *op, ValueBase *value);
bool isMaskedoffOfOperator(OperatorBase *op, ValueBase *value);
bool isVs2OfOperator(OperatorBase *op, ValueBase *value);
bool isVs1OfOperator(OperatorBase *op, ValueBase *value);
bool isExistVs1Rs1(OperatorBase *op);
bool isWideningOperator(OperatorBase *op);
bool isNarrowingOperator(OperatorBase *op);
bool isWideningValue(ValueBase *x, ValueBase *y);  // is X Widen of Y
bool isNarrowingValue(ValueBase *x, ValueBase *y); // is X Narrow of Y

// Getters for input/output of an Operator
ValueBase *getVd(OperatorBase *op);
ValueBase *getMask(OperatorBase *op);
ValueBase *getMaskedoff(OperatorBase *op);
ValueBase *getVs2(OperatorBase *op);
ValueBase *getVs1(OperatorBase *op);

/*
Set all inputs/outputs to LMUL of `op`.

This function is called "exactly" before the actual code generation.
The adjustment of an Operator and its used/defined Value-s will be
suitable for exactly when it is code generated. Therefore this function
is called in FusedGraphs::generateCCode (before calling
FuseGraph::generateCCode) and called in Graph::generateCCode (before calling
Operator::generateCCode).
*/
void initializeLmul(OperatorBase *op);

// String utility
bool ends_with(std::string const &value, std::string const &ending);

// LMUL utility
// Returns an LmulType (LmulType::mf8 = 0, LmulType::mf4 = 1, ...,
// LmulType::m8 = 6) Example: When value's sew = 8, its lowest LMUL possible
// will be: log2(8) - 3 = 0 = mf8
LmulType getSmallestLmulForSew(SewType sew);

} // namespace RIF
#endif // #define RIF_BASIC_HPP
