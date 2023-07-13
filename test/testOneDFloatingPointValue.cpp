#include "Graph.hpp"
#include "Value.hpp"
#include "gtest/gtest.h"

#include <iostream>
#include <sstream>

using namespace RIF;

TEST(OneDValue, Declare_CodeGen_Float16) {
  Graph graph;
  auto value = static_cast<OneDFloat16Val *>(
      graph.getNewValue(CustomValType::OneDFloat16, "value", 70));
  auto op = graph.getNewOperator(CustomValType::Initialize, "op");
  op->addOutput(value);

  uint16_t tmp[] = {
      13,  300, 831, 629, 821, 101, 183, 30,  99,  909, 332, 533, 430, 64,
      96,  680, 647, 980, 599, 988, 311, 779, 43,  151, 474, 80,  725, 616,
      787, 406, 10,  549, 692, 354, 290, 499, 124, 8,   884, 570, 724, 211,
      165, 0,   698, 200, 855, 612, 249, 159, 613, 891, 900, 675, 621, 785,
      359, 777, 617, 617, 414, 844, 138, 39,  488, 461, 836, 975, 637, 592,
  };

  auto raw = value->raw;
  for (int i = 0; i < 70; ++i)
    raw[i] = tmp[i];

  const char *expectedCode =
      "#include <stdbool.h>\n#include <stdint.h>\n#include "
      "<stdlib.h>\n#include <stdio.h>\n#include <string.h>\n#include "
      "<stddef.h>\n#include <riscv_vector.h>\ntypedef _Float16 "
      "float16_t;\ntypedef float float32_t;\ntypedef double "
      "float64_t;\n#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & "
      "0x03FF))\n#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & "
      "0x007FFFFF))\n#define isNaNF64UI( a ) (((~(a) & UINT64_C( "
      "0x7FF0000000000000 )) == 0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF "
      ")))\nfloat16_t value[70];\nvoid vinit_rif_op() {\nuint16_t tmp[] = "
      "{13,300,831,629,821,101,183,30,99,909,332,533,430,64,96,680,647,980,599,"
      "988,311,779,43,151,474,80,725,616,787,406,10,549,692,354,290,499,124,8,"
      "884,570,724,211,165,0,698,200,855,612,249,159,613,891,900,675,621,785,"
      "359,777,617,617,414,844,138,39,488,461,836,975,637,592,};\nfor (int "
      "i=0; i<70;++i) {union { uint16_t u16; float16_t f; } "
      "converter;\nconverter.u16 = tmp[i];\nvalue[i] = converter.f;\n}\n}\nint "
      "golden_vinit_rif_op() {\nreturn 1;\n}\nint main () "
      "{\nvinit_rif_op();\nprintf(\"op : %s\\n\", golden_vinit_rif_op() ? "
      "\"pass\" : \"fail\");\nint ret = 1; // 1 = success\nret &= "
      "golden_vinit_rif_op();\nif (!ret) return 1;\nreturn 0; }\n";

  std::stringstream generatedCode;
  graph.generateCCode(generatedCode);

  EXPECT_EQ(generatedCode.str(), expectedCode);
}
