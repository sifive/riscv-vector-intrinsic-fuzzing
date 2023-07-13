// Operator.hpp
/*
CustomOperator template and declarations extended by MACRO in the .def file.
*/
#ifndef RIF_OPERATOR_HPP
#define RIF_OPERATOR_HPP

#include "Basic.hpp"

#include <iostream>

namespace RIF {

struct InitializeOp : OperatorBase {
  InitializeOp(const std::string &id)
      : OperatorBase(CustomValType::Initialize, "vinit_rif", id, NoVLParameter,
                     0, {}, NumberOfValTypes, 0, NumberOfLmuls,
                     NumberOfTypeClasses) {}
  virtual ~InitializeOp() = default;
  virtual void generateData() override;
  virtual void generateCCode(std::ostream &os) override;
};

#define CUSTOM_OP_TYPE(OP_TYPE, OP_ID, SEW, TYPE_CLASS, OP_ATTR, OUTPUT_TYPE,  \
                       NUM_OF_INPUTS, ...)                                     \
  struct OP_TYPE##Op : OperatorBase {                                          \
    OP_TYPE##Op(const std::string &id, LmulType lmul)                          \
        : OperatorBase(CustomValType::OP_TYPE, "v" #OP_ID, id, OP_ATTR,        \
                       NUM_OF_INPUTS, {__VA_ARGS__}, OUTPUT_TYPE, SEW, lmul,   \
                       TYPE_CLASS) {}                                          \
    virtual ~OP_TYPE##Op() = default;                                          \
    virtual void generateData() override;                                      \
    virtual void generateCCode(std::ostream &os) override;                     \
  };

#include "CustomOperator.def"
#undef CUSTOM_OP_TYPE

extern int placeholderIndex;

// Utilites with C code generate as side effect. Return strings are placeholders
std::string loadOneDToVector(std::ostream &os, ValueBase *value,
                             const std::string &holder, OperatorBase *op);
std::string genOpString(std::ostream &os, OperatorBase *op,
                        const std::vector<std::string> &args,
                        ValueBase *output);
void storeVectorToOneD(std::ostream &os, const std::string rawBase,
                       const std::string vec, ValueBase *value);
void incrementRawPointerByVLEN(std::ostream &os, std::string ptrID);

// Utility to get input / output of operator
ValueBase *getVd(OperatorBase *op);
ValueBase *getMask(OperatorBase *op);
ValueBase *getMaskedoff(OperatorBase *op);
ValueBase *getVs2(OperatorBase *op);
bool isExistVs1Rs1(OperatorBase *op);
ValueBase *getVs1(OperatorBase *op);
bool isMaskOfOperator(OperatorBase *op, ValueBase *value);
bool isMaskedoffOfOperator(OperatorBase *op, ValueBase *value);
bool isVs2OfOperator(OperatorBase *op, ValueBase *value);
bool isVs1OfOperator(OperatorBase *op, ValueBase *value);
bool isWideningOperator(OperatorBase *op);
bool isWideningValue(ValueBase *x, ValueBase *y);
bool isNarrowingOperator(OperatorBase *op);
bool isNarrowingValue(ValueBase *x, ValueBase *y);

// Verify for the operator
void generateVerificationCode(std::ostream &os, OperatorBase *op);

// CodeGen structures
struct CodeGenForOperator {

  using ValuePair = std::pair<std::string, ValueBase *>;

  CodeGenForOperator() = delete;
  CodeGenForOperator(std::ostream &os, OperatorBase *op, TypeInfo &typeInfo,
                     size_t length);

  std::ostream &os;
  OperatorBase *op;
  TypeInfo vlTypeInfo;
  size_t loopLength;

  // Loads raw data into pointer placeholders. The names of generated
  // placeholders are stored in `opInputs` and opOutput.
  std::vector<ValuePair> opInputs;
  ValuePair opOutput;
  void getRawPointers(std::vector<ValueBase *> inputs, ValueBase *output);

  // With the pointers of the raw pointers, we will need to use vle or vmv to
  // load raw data into rvv data type. This is done inside this function.
  std::vector<std::string> getIntrinsicArguments();

  // At the end of for loops, the raw pointer place holders need to be increased
  // by the number of data elements processed in this iteration, which is `vl`.
  void incrementRawPointerByVLEN();

  // Save the results of the operator into raw data slots.
  void storeResult(std::string opResult);
  static std::string getCounter(std::ostream &os, size_t length);
  static void getLoopStart(std::ostream &os, std::string counter);
  static void getLoopEnd(std::ostream &os);
  void getVL(std::string counter);

  void generateSingleOperatorCode();
};

} // namespace RIF
#endif // #define RIF_OPERATOR_HPP
