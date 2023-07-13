#include "Graph.hpp"
#include "Value.hpp"
#include "gtest/gtest.h"

#include <iostream>
#include <sstream>

using namespace RIF;

TEST(ScalarValue, Declare_CodeGen_Int8) {
  Graph graph;
  auto value = static_cast<ScalarInt8Val *>(
      graph.getNewValue(CustomValType::ScalarInt8, "value", 1));
  auto op = graph.getNewOperator(CustomValType::Initialize, "op");
  op->addOutput(value);

  auto data = getRawPointer(value);
  auto raw = value->raw;
  int8_t tmp = 3;
  *data = *raw = tmp;

  const char *expectedCode =
      "#include <stdbool.h>\n#include <stdint.h>\n#include "
      "<stdlib.h>\n#include <stdio.h>\n#include <string.h>\n#include "
      "<stddef.h>\n#include <riscv_vector.h>\ntypedef _Float16 "
      "float16_t;\ntypedef float float32_t;\ntypedef double "
      "float64_t;\n#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & "
      "0x03FF))\n#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & "
      "0x007FFFFF))\n#define isNaNF64UI( a ) (((~(a) & UINT64_C( "
      "0x7FF0000000000000 )) == 0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF "
      ")))\nint8_t value;\nvoid vinit_rif_op() {\nint8_t tmp = 3;\nvalue = "
      "tmp;\n}\nint golden_vinit_rif_op() {\nreturn 1;\n}\nint main () "
      "{\nvinit_rif_op();\nprintf(\"op : %s\\n\", golden_vinit_rif_op() ? "
      "\"pass\" : \"fail\");\nint ret = 1; // 1 = success\nret &= "
      "golden_vinit_rif_op();\nif (!ret) return 1;\nreturn 0; }\n";

  std::stringstream generatedCode;
  graph.generateCCode(generatedCode);

  EXPECT_EQ(generatedCode.str(), expectedCode);
}

TEST(ScalarValue, Declare_CodeGen_Int16) {
  Graph graph;
  auto value = static_cast<ScalarInt16Val *>(
      graph.getNewValue(CustomValType::ScalarInt16, "value", 1));
  auto op = graph.getNewOperator(CustomValType::Initialize, "op");
  op->addOutput(value);

  auto data = getRawPointer(value);
  auto raw = value->raw;
  int16_t tmp = 13;
  *data = *raw = tmp;

  const char *expectedCode =
      "#include <stdbool.h>\n#include <stdint.h>\n#include "
      "<stdlib.h>\n#include <stdio.h>\n#include <string.h>\n#include "
      "<stddef.h>\n#include <riscv_vector.h>\ntypedef _Float16 "
      "float16_t;\ntypedef float float32_t;\ntypedef double "
      "float64_t;\n#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & "
      "0x03FF))\n#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & "
      "0x007FFFFF))\n#define isNaNF64UI( a ) (((~(a) & UINT64_C( "
      "0x7FF0000000000000 )) == 0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF "
      ")))\nint16_t value;\nvoid vinit_rif_op() {\nint16_t tmp = 13;\nvalue = "
      "tmp;\n}\nint golden_vinit_rif_op() {\nreturn 1;\n}\nint main () "
      "{\nvinit_rif_op();\nprintf(\"op : %s\\n\", golden_vinit_rif_op() ? "
      "\"pass\" : \"fail\");\nint ret = 1; // 1 = success\nret &= "
      "golden_vinit_rif_op();\nif (!ret) return 1;\nreturn 0; }\n";

  std::stringstream generatedCode;
  graph.generateCCode(generatedCode);

  EXPECT_EQ(generatedCode.str(), expectedCode);
}

TEST(ScalarValue, Declare_CodeGen_Int32) {
  Graph graph;
  auto value = static_cast<ScalarInt32Val *>(
      graph.getNewValue(CustomValType::ScalarInt32, "value", 1));
  auto op = graph.getNewOperator(CustomValType::Initialize, "op");
  op->addOutput(value);

  auto data = getRawPointer(value);
  auto raw = value->raw;
  int32_t tmp = 5013;
  *data = *raw = tmp;

  const char *expectedCode =
      "#include <stdbool.h>\n#include <stdint.h>\n#include "
      "<stdlib.h>\n#include <stdio.h>\n#include <string.h>\n#include "
      "<stddef.h>\n#include <riscv_vector.h>\ntypedef _Float16 "
      "float16_t;\ntypedef float float32_t;\ntypedef double "
      "float64_t;\n#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & "
      "0x03FF))\n#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & "
      "0x007FFFFF))\n#define isNaNF64UI( a ) (((~(a) & UINT64_C( "
      "0x7FF0000000000000 )) == 0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF "
      ")))\nint32_t value;\nvoid vinit_rif_op() {\nint32_t tmp = 5013;\nvalue "
      "= tmp;\n}\nint golden_vinit_rif_op() {\nreturn 1;\n}\nint main () "
      "{\nvinit_rif_op();\nprintf(\"op : %s\\n\", golden_vinit_rif_op() ? "
      "\"pass\" : \"fail\");\nint ret = 1; // 1 = success\nret &= "
      "golden_vinit_rif_op();\nif (!ret) return 1;\nreturn 0; }\n";

  std::stringstream generatedCode;
  graph.generateCCode(generatedCode);

  EXPECT_EQ(generatedCode.str(), expectedCode);
}

TEST(ScalarValue, Declare_CodeGen_Int64) {
  Graph graph;
  auto value = static_cast<ScalarInt64Val *>(
      graph.getNewValue(CustomValType::ScalarInt64, "value", 1));
  auto op = graph.getNewOperator(CustomValType::Initialize, "op");
  op->addOutput(value);

  auto data = getRawPointer(value);
  auto raw = value->raw;
  int32_t tmp = 1118455013;
  *data = *raw = tmp;

  const char *expectedCode =
      "#include <stdbool.h>\n#include <stdint.h>\n#include "
      "<stdlib.h>\n#include <stdio.h>\n#include <string.h>\n#include "
      "<stddef.h>\n#include <riscv_vector.h>\ntypedef _Float16 "
      "float16_t;\ntypedef float float32_t;\ntypedef double "
      "float64_t;\n#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & "
      "0x03FF))\n#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & "
      "0x007FFFFF))\n#define isNaNF64UI( a ) (((~(a) & UINT64_C( "
      "0x7FF0000000000000 )) == 0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF "
      ")))\nint64_t value;\nvoid vinit_rif_op() {\nint64_t tmp = "
      "1118455013ll;\nvalue = tmp;\n}\nint golden_vinit_rif_op() {\nreturn "
      "1;\n}\nint main () {\nvinit_rif_op();\nprintf(\"op : %s\\n\", "
      "golden_vinit_rif_op() ? \"pass\" : \"fail\");\nint ret = 1; // 1 = "
      "success\nret &= golden_vinit_rif_op();\nif (!ret) return 1;\nreturn 0; "
      "}\n";

  std::stringstream generatedCode;
  graph.generateCCode(generatedCode);

  EXPECT_EQ(generatedCode.str(), expectedCode);
}
