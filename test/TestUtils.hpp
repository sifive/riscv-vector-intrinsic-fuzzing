#include "Basic.hpp"
#include "Graph.hpp"
#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace RIF {

Graph::Value *getInitializeValue(CustomValType type, Graph &graph,
                                 const std::string &id, const int &length,
                                 const LmulType lmul = LmulType::m1) {
  auto init = graph.getNewOperator(CustomValType::Initialize, "init_" + id);
  auto value = graph.getNewValue(type, "value_" + id, length, lmul);
  init->addOutput(value);
  return value;
}

template <typename OneDT, CustomValType OneDTEnum, CustomValType OperatorEnum>
OneDT *NonMaskVOperatorTest(Graph &graph, std::vector<int> &dataA) {
  const int length = dataA.size();
  auto input0 = static_cast<OneDT *>(
      getInitializeValue(OneDTEnum, graph, "input0", length));
  auto output =
      static_cast<OneDT *>(graph.getNewValue(OneDTEnum, "output", length));

  auto ptr0 = getRawPointer(input0);
  auto raw0 = input0->raw;
  for (int i = 0; i < length; ++i) {
    ptr0[i] = raw0[i] = dataA[i];
  }

  auto op = graph.getNewOperator(OperatorEnum, "op1");
  op->addInput(0, input0);
  op->addOutput(output);
  op->generateData();

  return output;
}

#define NONMASK_VV_VALUE_INIT                                                  \
  for (int i = 0; i < length; ++i) {                                           \
    ptrA[i] = a->raw[i] = dataA[i];                                            \
    ptrB[i] = b->raw[i] = dataB[i];                                            \
  }

#define NONMASK_VX_VALUE_INIT                                                  \
  *ptrB = *rawB = dataB;                                                       \
  for (int i = 0; i < length; ++i) {                                           \
    ptrA[i] = rawA[i] = dataA[i];                                              \
  }

#define NONMASK_TA_VV_VALUE_INIT                                               \
  for (int i = 0; i < length; ++i) {                                           \
    ptrA[i] = rawA[i] = dataA[i];                                              \
    ptrB[i] = rawB[i] = dataB[i];                                              \
    ptrMO[i] = rawMO[i] = dataMO[i];                                           \
  }

#define MASK_TAMA_VV_VALUE_INIT                                                \
  for (int i = 0; i < length; ++i) {                                           \
    ptrA[i] = rawA[i] = dataA[i];                                              \
    ptrB[i] = rawB[i] = dataB[i];                                              \
    ptrM[i] = rawM[i] = dataM[i];                                              \
  }

#define MASK_VV_VALUE_INIT                                                     \
  for (int i = 0; i < length; ++i) {                                           \
    ptrA[i] = rawA[i] = dataA[i];                                              \
    ptrB[i] = rawB[i] = dataB[i];                                              \
    ptrM[i] = rawM[i] = dataM[i];                                              \
    ptrMO[i] = rawMO[i] = dataMO[i];                                           \
  }

#define MASK_VX_VALUE_INIT                                                     \
  *ptrB = *rawB = dataB;                                                       \
  for (int i = 0; i < length; ++i) {                                           \
    ptrA[i] = rawA[i] = dataA[i];                                              \
    ptrM[i] = rawM[i] = dataM[i];                                              \
    ptrMO[i] = rawMO[i] = dataMO[i];                                           \
  }

#define NONMASK_FP_VV_VALUE_INIT(SEW)                                          \
  {                                                                            \
    for (int i = 0; i < length; ++i) {                                         \
      rawA[i] = dataA[i];                                                      \
      rawB[i] = dataBOneD[i];                                                  \
      ptrA[i] = ui64_to_f##SEW(rawA[i]);                                       \
      ptrB[i] = ui64_to_f##SEW(rawB[i]);                                       \
    }                                                                          \
  }

#define NONMASK_FP_VX_VALUE_INIT(SEW)                                          \
  {                                                                            \
    *rawB = dataBScalar;                                                       \
    *ptrB = ui64_to_f##SEW(*rawB);                                             \
    for (int i = 0; i < length; ++i) {                                         \
      rawA[i] = dataA[i];                                                      \
      ptrA[i] = ui64_to_f##SEW(rawA[i]);                                       \
    }                                                                          \
  }

#define MASK_FP_VV_VALUE_INIT(SEW)                                             \
  {                                                                            \
    for (int i = 0; i < length; ++i) {                                         \
      rawM[i] = dataMask[i];                                                   \
      rawMO[i] = dataMaskedOff[i];                                             \
      rawA[i] = dataA[i];                                                      \
      rawB[i] = dataBOneD[i];                                                  \
      ptrM[i] = rawM[i];                                                       \
      ptrMO[i] = ui64_to_f##SEW(rawMO[i]);                                     \
      ptrA[i] = ui64_to_f##SEW(rawA[i]);                                       \
      ptrB[i] = ui64_to_f##SEW(rawB[i]);                                       \
    }                                                                          \
  }

#define MASK_FP_VF_VALUE_INIT(SEW)                                             \
  {                                                                            \
    *rawB = dataBScalar;                                                       \
    *ptrB = ui64_to_f##SEW(*rawB);                                             \
    for (int i = 0; i < length; ++i) {                                         \
      rawM[i] = dataMask[i];                                                   \
      rawMO[i] = dataMaskedOff[i];                                             \
      rawA[i] = dataA[i];                                                      \
      ptrM[i] = rawM[i];                                                       \
      ptrMO[i] = ui64_to_f##SEW(rawMO[i]);                                     \
      ptrA[i] = ui64_to_f##SEW(rawA[i]);                                       \
    }                                                                          \
  }

#define NONMASK_V_VALUE_INIT                                                   \
  for (int i = 0; i < length; ++i) {                                           \
    ptrA[i] = rawA[i] = dataA[i];                                              \
  }

#define MASK_V_NO_MASKEDOFF_VALUE_INIT                                         \
  for (int i = 0; i < length; ++i) {                                           \
    ptrM[i] = rawM[i] = dataM[i];                                              \
    ptrA[i] = rawA[i] = dataA[i];                                              \
  }

#define MASK_V_VALUE_INIT                                                      \
  for (int i = 0; i < length; ++i) {                                           \
    ptrM[i] = rawM[i] = dataM[i];                                              \
    ptrMO[i] = rawMO[i] = dataMO[i];                                           \
    ptrA[i] = rawA[i] = dataA[i];                                              \
  }

#define NONMASK_VV_VX_GEN_TEST(INPUTA_ENUM, INPUTB_ENUM, OUTPUT_ENUM,          \
                               VALUE_INIT_BODY, OP_ENUM)                       \
  Graph graph;                                                                 \
  const int length = dataA.size();                                             \
  auto a = static_cast<INPUTA_ENUM##Val *>(                                    \
      getInitializeValue(INPUTA_ENUM, graph, "A", length));                    \
  auto b = static_cast<INPUTB_ENUM##Val *>(                                    \
      getInitializeValue(INPUTB_ENUM, graph, "B", length));                    \
  auto c = static_cast<OUTPUT_ENUM##Val *>(                                    \
      graph.getNewValue(OUTPUT_ENUM, "value_C", length));                      \
  auto ptrA = getRawPointer(a);                                                \
  auto rawA = a->raw;                                                          \
  auto ptrB = getRawPointer(b);                                                \
  auto rawB = b->raw;                                                          \
  VALUE_INIT_BODY                                                              \
  auto op = graph.getNewOperator(OP_ENUM, "op1");                              \
  op->addInput(0, a);                                                          \
  op->addInput(1, b);                                                          \
  op->addOutput(c);                                                            \
  op->generateData();                                                          \
  std::stringstream generatedCCode;                                            \
  graph.generateCCode(generatedCCode);

#define NONMASK_TA_VV_VX_GEN_TEST(INPUTMO_ENUM, INPUTA_ENUM, INPUTB_ENUM,      \
                                  OUTPUT_ENUM, VALUE_INIT_BODY, OP_ENUM)       \
  Graph graph;                                                                 \
  const int length = dataA.size();                                             \
  auto inputMO = static_cast<INPUTMO_ENUM##Val *>(                             \
      getInitializeValue(INPUTMO_ENUM, graph, "MO", length));                  \
  auto inputA = static_cast<INPUTA_ENUM##Val *>(                               \
      getInitializeValue(INPUTA_ENUM, graph, "A", length));                    \
  auto inputB = static_cast<INPUTB_ENUM##Val *>(                               \
      getInitializeValue(INPUTB_ENUM, graph, "B", length));                    \
  auto output = static_cast<OUTPUT_ENUM##Val *>(                               \
      graph.getNewValue(OUTPUT_ENUM, "output", length));                       \
  auto ptrA = getRawPointer(inputA);                                           \
  auto rawA = inputA->raw;                                                     \
  auto ptrB = getRawPointer(inputB);                                           \
  auto rawB = inputB->raw;                                                     \
  auto ptrMO = getRawPointer(inputMO);                                         \
  auto rawMO = inputMO->raw;                                                   \
  VALUE_INIT_BODY                                                              \
  auto op = graph.getNewOperator(OP_ENUM, "op");                               \
  op->addInput(0, inputMO);                                                    \
  op->addInput(1, inputA);                                                     \
  op->addInput(2, inputB);                                                     \
  op->addOutput(output);                                                       \
  op->generateData();                                                          \
  std::stringstream generatedCCode;                                            \
  graph.generateCCode(generatedCCode);

#define MASK_TAMA_VV_VX_GEN_TEST(INPUTM_ENUM, INPUTA_ENUM, INPUTB_ENUM,        \
                                 OUTPUT_ENUM, VALUE_INIT_BODY, OP_ENUM)        \
  Graph graph;                                                                 \
  const int length = dataA.size();                                             \
  auto inputM = static_cast<INPUTM_ENUM##Val *>(                               \
      getInitializeValue(INPUTM_ENUM, graph, "M", length));                    \
  auto inputA = static_cast<INPUTA_ENUM##Val *>(                               \
      getInitializeValue(INPUTA_ENUM, graph, "A", length));                    \
  auto inputB = static_cast<INPUTB_ENUM##Val *>(                               \
      getInitializeValue(INPUTB_ENUM, graph, "B", length));                    \
  auto output = static_cast<OUTPUT_ENUM##Val *>(                               \
      graph.getNewValue(OUTPUT_ENUM, "output", length));                       \
  auto ptrA = getRawPointer(inputA);                                           \
  auto rawA = inputA->raw;                                                     \
  auto ptrB = getRawPointer(inputB);                                           \
  auto rawB = inputB->raw;                                                     \
  auto ptrM = getRawPointer(inputM);                                           \
  auto rawM = inputM->raw;                                                     \
  VALUE_INIT_BODY                                                              \
  auto op = graph.getNewOperator(OP_ENUM, "op");                               \
  op->addInput(0, inputM);                                                     \
  op->addInput(1, inputA);                                                     \
  op->addInput(2, inputB);                                                     \
  op->addOutput(output);                                                       \
  op->generateData();                                                          \
  std::stringstream generatedCCode;                                            \
  graph.generateCCode(generatedCCode);

#define MASK_VV_VX_GEN_TEST(INPUTM_ENUM, INPUTMO_ENUM, INPUTA_ENUM,            \
                            INPUTB_ENUM, OUTPUT_ENUM, VALUE_INIT_BODY,         \
                            OP_ENUM)                                           \
  Graph graph;                                                                 \
  const int length = dataA.size();                                             \
  auto inputM = static_cast<INPUTM_ENUM##Val *>(                               \
      getInitializeValue(INPUTM_ENUM, graph, "M", length));                    \
  auto inputMO = static_cast<INPUTMO_ENUM##Val *>(                             \
      getInitializeValue(INPUTMO_ENUM, graph, "MO", length));                  \
  auto inputA = static_cast<INPUTA_ENUM##Val *>(                               \
      getInitializeValue(INPUTA_ENUM, graph, "A", length));                    \
  auto inputB = static_cast<INPUTB_ENUM##Val *>(                               \
      getInitializeValue(INPUTB_ENUM, graph, "B", length));                    \
  auto output = static_cast<OUTPUT_ENUM##Val *>(                               \
      graph.getNewValue(OUTPUT_ENUM, "output", length));                       \
  auto ptrA = getRawPointer(inputA);                                           \
  auto rawA = inputA->raw;                                                     \
  auto ptrB = getRawPointer(inputB);                                           \
  auto rawB = inputB->raw;                                                     \
  auto ptrM = getRawPointer(inputM);                                           \
  auto rawM = inputM->raw;                                                     \
  auto ptrMO = getRawPointer(inputMO);                                         \
  auto rawMO = inputMO->raw;                                                   \
  VALUE_INIT_BODY                                                              \
  auto op = graph.getNewOperator(OP_ENUM, "op");                               \
  op->addInput(0, inputM);                                                     \
  op->addInput(1, inputMO);                                                    \
  op->addInput(2, inputA);                                                     \
  op->addInput(3, inputB);                                                     \
  op->addOutput(output);                                                       \
  op->generateData();                                                          \
  std::stringstream generatedCCode;                                            \
  graph.generateCCode(generatedCCode);

#define NONMASK_V_GEN_TEST(INPUT_ENUM, OUTPUT_ENUM, VALUE_INIT_BODY, OP_ENUM)  \
  Graph graph;                                                                 \
  const int length = dataA.size();                                             \
  auto a = static_cast<INPUT_ENUM##Val *>(                                     \
      getInitializeValue(INPUT_ENUM, graph, "input", length));                 \
  auto b = static_cast<OUTPUT_ENUM##Val *>(                                    \
      graph.getNewValue(OUTPUT_ENUM, "output", length));                       \
  auto ptrA = getRawPointer(a);                                                \
  auto rawA = a->raw;                                                          \
  VALUE_INIT_BODY                                                              \
  auto op = graph.getNewOperator(OP_ENUM, "op1");                              \
  op->addInput(0, a);                                                          \
  op->addOutput(b);                                                            \
  op->generateData();                                                          \
  std::stringstream generatedCCode;                                            \
  graph.generateCCode(generatedCCode);

#define MASK_V_NO_MASKEDOFF_GEN_TEST(INPUTM_ENUM, INPUTA_ENUM, OUTPUT_ENUM,    \
                                     VALUE_INIT_BODY, OP_ENUM)                 \
  Graph graph;                                                                 \
  const int length = dataA.size();                                             \
  auto a = static_cast<INPUTM_ENUM##Val *>(                                    \
      getInitializeValue(INPUTM_ENUM, graph, "inputM", length));               \
  auto b = static_cast<INPUTA_ENUM##Val *>(                                    \
      getInitializeValue(INPUTA_ENUM, graph, "inputA", length));               \
  auto c = static_cast<OUTPUT_ENUM##Val *>(                                    \
      graph.getNewValue(OUTPUT_ENUM, "output", length));                       \
  auto ptrM = getRawPointer(a);                                                \
  auto rawM = a->raw;                                                          \
  auto ptrA = getRawPointer(b);                                                \
  auto rawA = b->raw;                                                          \
  VALUE_INIT_BODY                                                              \
  auto op = graph.getNewOperator(OP_ENUM, "op1");                              \
  op->addInput(0, a);                                                          \
  op->addInput(1, b);                                                          \
  op->addOutput(c);                                                            \
  op->generateData();                                                          \
  std::stringstream generatedCCode;                                            \
  graph.generateCCode(generatedCCode);

#define MASK_V_GEN_TEST(INPUTM_ENUM, INPUTMO_ENUM, INPUTA_ENUM, OUTPUT_ENUM,   \
                        VALUE_INIT_BODY, OP_ENUM)                              \
  Graph graph;                                                                 \
  const int length = dataA.size();                                             \
  auto a = static_cast<INPUTM_ENUM##Val *>(                                    \
      getInitializeValue(INPUTM_ENUM, graph, "inputM", length));               \
  auto b = static_cast<INPUTMO_ENUM##Val *>(                                   \
      getInitializeValue(INPUTMO_ENUM, graph, "inputMO", length));             \
  auto c = static_cast<INPUTA_ENUM##Val *>(                                    \
      getInitializeValue(INPUTA_ENUM, graph, "inputA", length));               \
  auto d = static_cast<OUTPUT_ENUM##Val *>(                                    \
      graph.getNewValue(OUTPUT_ENUM, "output", length));                       \
  auto ptrM = getRawPointer(a);                                                \
  auto rawM = a->raw;                                                          \
  auto ptrMO = getRawPointer(b);                                               \
  auto rawMO = b->raw;                                                         \
  auto ptrA = getRawPointer(c);                                                \
  auto rawA = c->raw;                                                          \
  VALUE_INIT_BODY                                                              \
  auto op = graph.getNewOperator(OP_ENUM, "op1");                              \
  op->addInput(0, a);                                                          \
  op->addInput(1, b);                                                          \
  op->addInput(2, c);                                                          \
  op->addOutput(d);                                                            \
  op->generateData();                                                          \
  std::stringstream generatedCCode;                                            \
  graph.generateCCode(generatedCCode);

template <typename OneDT, typename GoldenT>
static bool verifyResult(OneDT *value, std::vector<GoldenT> &golden) {
  assert(value->length == golden.size());
  auto length = value->length;
  auto rawC = getRawPointer(value);
  for (int i = 0; i < length; ++i) {
    EXPECT_EQ(rawC[i], golden[i]);
    if (rawC[i] != golden[i])
      return false;
  }
  return true;
}

template <> bool verifyResult(OneDFloat16Val *value, std::vector<int> &golden) {
  bool good = 1;
  auto length = value->length;
  auto ptr = getRawPointer(value);
  for (int i = 0; i < length; ++i) {
    float16_t x = ui64_to_f16(golden[i]);
    EXPECT_EQ(ptr[i].v, x.v);
    if (ptr[i].v != x.v) {
      good = 0;
      std::cout << "[" << i << "] (compute) " << ptr[i].v << " != (golden) "
                << x.v << "\n";
    }
  }
  return good;
}

template <> bool verifyResult(OneDFloat32Val *value, std::vector<int> &golden) {
  bool good = 1;
  auto length = value->length;
  auto ptr = getRawPointer(value);
  for (int i = 0; i < length; ++i) {
    float32_t x = ui64_to_f32(golden[i]);
    EXPECT_EQ(ptr[i].v, x.v);
    if (ptr[i].v != x.v) {
      good = 0;
      std::cout << "[" << i << "] (compute) " << ptr[i].v << " != (golden) "
                << x.v << "\n";
    }
  }
  return good;
}

template <> bool verifyResult(OneDFloat64Val *value, std::vector<int> &golden) {
  bool good = 1;
  auto length = value->length;
  auto ptr = getRawPointer(value);
  for (int i = 0; i < length; ++i) {
    float64_t x = ui64_to_f64(golden[i]);
    EXPECT_EQ(ptr[i].v, x.v);
    if (ptr[i].v != x.v) {
      good = 0;
      std::cout << "[" << i << "] (compute) " << ptr[i].v << " != (golden) "
                << x.v << "\n";
    }
  }
  return good;
}

} // namespace RIF
