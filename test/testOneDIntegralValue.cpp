#include "Graph.hpp"
#include "Value.hpp"
#include "gtest/gtest.h"

#include <iostream>
#include <sstream>

using namespace RIF;

TEST(OneDValue, Declare_CodeGen_Bool) {
  Graph graph;
  auto value = static_cast<OneDBoolVal *>(
      graph.getNewValue(CustomValType::OneDBool, "value", 70));
  auto op = graph.getNewOperator(CustomValType::Initialize, "op");
  op->addOutput(value);

  int64_t tmp[] = {
      1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1,
      0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0,
      1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0,
  };
  auto data = getRawPointer(value);
  auto raw = value->raw;
  for (int i = 0; i < 70; ++i)
    data[i] = raw[i] = tmp[i];

  const char *expectedCode =
      "#include <stdbool.h>\n#include <stdint.h>\n#include "
      "<stdlib.h>\n#include <stdio.h>\n#include <string.h>\n#include "
      "<stddef.h>\n#include <riscv_vector.h>\ntypedef _Float16 "
      "float16_t;\ntypedef float float32_t;\ntypedef double "
      "float64_t;\n#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & "
      "0x03FF))\n#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & "
      "0x007FFFFF))\n#define isNaNF64UI( a ) (((~(a) & UINT64_C( "
      "0x7FF0000000000000 )) == 0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF "
      ")))\nint8_t value[70];\nvoid vinit_rif_op() {\nint8_t tmp[] = "
      "{1,0,1,1,1,1,1,0,1,1,0,1,0,0,0,0,1,0,1,0,1,1,1,1,0,0,1,0,1,0,0,1,0,0,0,"
      "1,0,0,0,0,0,1,1,0,0,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,1,0,1,0,1,1,0,};"
      "\nfor (int i=0; i<70;++i) {value[i] = tmp[i];\n}\n}\nint "
      "golden_vinit_rif_op() {\nreturn 1;\n}\nint main () "
      "{\nvinit_rif_op();\nprintf(\"op : %s\\n\", golden_vinit_rif_op() ? "
      "\"pass\" : \"fail\");\nint ret = 1; // 1 = success\nret &= "
      "golden_vinit_rif_op();\nif (!ret) return 1;\nreturn 0; }\n";

  std::stringstream generatedCode;
  graph.generateCCode(generatedCode);

  EXPECT_EQ(generatedCode.str(), expectedCode);
}

TEST(OneDValue, Declare_CodeGen_Int8) {
  Graph graph;
  auto value = static_cast<OneDInt8Val *>(
      graph.getNewValue(CustomValType::OneDInt8, "value", 70));
  auto op = graph.getNewOperator(CustomValType::Initialize, "op");
  op->addOutput(value);

  int8_t tmp[] = {
      3, 0, 1, 9, 1, 1, 3, 0, 9, 9, 2, 3, 0, 4, 6, 0, 7, 0, 9, 8, 1, 9, 3, 1,
      4, 0, 5, 6, 7, 6, 0, 9, 2, 4, 0, 9, 4, 8, 4, 0, 4, 1, 5, 0, 8, 0, 5, 2,
      9, 9, 3, 1, 0, 5, 1, 5, 9, 7, 7, 7, 4, 4, 8, 9, 8, 1, 6, 5, 7, 2,
  };
  auto data = getRawPointer(value);
  auto raw = value->raw;
  for (int i = 0; i < 70; ++i)
    data[i] = raw[i] = tmp[i];

  const char *expectedCode =
      "#include <stdbool.h>\n#include <stdint.h>\n#include "
      "<stdlib.h>\n#include <stdio.h>\n#include <string.h>\n#include "
      "<stddef.h>\n#include <riscv_vector.h>\ntypedef _Float16 "
      "float16_t;\ntypedef float float32_t;\ntypedef double "
      "float64_t;\n#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & "
      "0x03FF))\n#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & "
      "0x007FFFFF))\n#define isNaNF64UI( a ) (((~(a) & UINT64_C( "
      "0x7FF0000000000000 )) == 0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF "
      ")))\nint8_t value[70];\nvoid vinit_rif_op() {\nint8_t tmp[] = "
      "{3,0,1,9,1,1,3,0,9,9,2,3,0,4,6,0,7,0,9,8,1,9,3,1,4,0,5,6,7,6,0,9,2,4,0,"
      "9,4,8,4,0,4,1,5,0,8,0,5,2,9,9,3,1,0,5,1,5,9,7,7,7,4,4,8,9,8,1,6,5,7,2,};"
      "\nfor (int i=0; i<70;++i) {value[i] = tmp[i];\n}\n}\nint "
      "golden_vinit_rif_op() {\nreturn 1;\n}\nint main () "
      "{\nvinit_rif_op();\nprintf(\"op : %s\\n\", golden_vinit_rif_op() ? "
      "\"pass\" : \"fail\");\nint ret = 1; // 1 = success\nret &= "
      "golden_vinit_rif_op();\nif (!ret) return 1;\nreturn 0; }\n";

  std::stringstream generatedCode;
  graph.generateCCode(generatedCode);

  EXPECT_EQ(generatedCode.str(), expectedCode);
}

TEST(OneDValue, Declare_CodeGen_Int16) {
  Graph graph;
  auto value = static_cast<OneDInt16Val *>(
      graph.getNewValue(CustomValType::OneDInt16, "value", 70));
  auto op = graph.getNewOperator(CustomValType::Initialize, "op");
  op->addOutput(value);

  int16_t tmp[] = {
      13,  300, 831, 629, 821, 101, 183, 30,  99,  909, 332, 533, 430, 64,
      96,  680, 647, 980, 599, 988, 311, 779, 43,  151, 474, 80,  725, 616,
      787, 406, 10,  549, 692, 354, 290, 499, 124, 8,   884, 570, 724, 211,
      165, 0,   698, 200, 855, 612, 249, 159, 613, 891, 900, 675, 621, 785,
      359, 777, 617, 617, 414, 844, 138, 39,  488, 461, 836, 975, 637, 592,
  };
  auto data = getRawPointer(value);
  auto raw = value->raw;
  for (int i = 0; i < 70; ++i)
    data[i] = raw[i] = tmp[i];

  const char *expectedCode =
      "#include <stdbool.h>\n#include <stdint.h>\n#include "
      "<stdlib.h>\n#include <stdio.h>\n#include <string.h>\n#include "
      "<stddef.h>\n#include <riscv_vector.h>\ntypedef _Float16 "
      "float16_t;\ntypedef float float32_t;\ntypedef double "
      "float64_t;\n#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & "
      "0x03FF))\n#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & "
      "0x007FFFFF))\n#define isNaNF64UI( a ) (((~(a) & UINT64_C( "
      "0x7FF0000000000000 )) == 0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF "
      ")))\nint16_t value[70];\nvoid vinit_rif_op() {\nint16_t tmp[] = "
      "{13,300,831,629,821,101,183,30,99,909,332,533,430,64,96,680,647,980,599,"
      "988,311,779,43,151,474,80,725,616,787,406,10,549,692,354,290,499,124,8,"
      "884,570,724,211,165,0,698,200,855,612,249,159,613,891,900,675,621,785,"
      "359,777,617,617,414,844,138,39,488,461,836,975,637,592,};\nfor (int "
      "i=0; i<70;++i) {value[i] = tmp[i];\n}\n}\nint golden_vinit_rif_op() "
      "{\nreturn 1;\n}\nint main () {\nvinit_rif_op();\nprintf(\"op : %s\\n\", "
      "golden_vinit_rif_op() ? \"pass\" : \"fail\");\nint ret = 1; // 1 = "
      "success\nret &= golden_vinit_rif_op();\nif (!ret) return 1;\nreturn 0; "
      "}\n";

  std::stringstream generatedCode;
  graph.generateCCode(generatedCode);

  EXPECT_EQ(generatedCode.str(), expectedCode);
}

TEST(OneDValue, Declare_CodeGen_Int32) {
  Graph graph;
  auto value = static_cast<OneDInt32Val *>(
      graph.getNewValue(CustomValType::OneDInt32, "value", 70));
  auto op = graph.getNewOperator(CustomValType::Initialize, "op");
  op->addOutput(value);

  int32_t tmp[] = {
      5013, 1300, 2831, 3629, 8821, 2101, 8183, 6030, 6099, 9909, 5332, 533,
      8430, 1064, 4096, 1680, 3647, 1980, 7599, 4988, 6311, 6779, 5043, 2151,
      4474, 3080, 3725, 6616, 5787, 7406, 2010, 1549, 8692, 354,  7290, 6499,
      5124, 5008, 5884, 4570, 9724, 4211, 4165, 6000, 8698, 4200, 6855, 4612,
      8249, 8159, 4613, 9891, 6900, 1675, 621,  1785, 4359, 777,  1617, 8617,
      8414, 2844, 5138, 5039, 5488, 2461, 4836, 7975, 5637, 4592,
  };
  auto data = getRawPointer(value);
  auto raw = value->raw;
  for (int i = 0; i < 70; ++i)
    data[i] = raw[i] = tmp[i];

  const char *expectedCode =
      "#include <stdbool.h>\n#include <stdint.h>\n#include "
      "<stdlib.h>\n#include <stdio.h>\n#include <string.h>\n#include "
      "<stddef.h>\n#include <riscv_vector.h>\ntypedef _Float16 "
      "float16_t;\ntypedef float float32_t;\ntypedef double "
      "float64_t;\n#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & "
      "0x03FF))\n#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & "
      "0x007FFFFF))\n#define isNaNF64UI( a ) (((~(a) & UINT64_C( "
      "0x7FF0000000000000 )) == 0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF "
      ")))\nint32_t value[70];\nvoid vinit_rif_op() {\nint32_t tmp[] = "
      "{5013,1300,2831,3629,8821,2101,8183,6030,6099,9909,5332,533,8430,1064,"
      "4096,1680,3647,1980,7599,4988,6311,6779,5043,2151,4474,3080,3725,6616,"
      "5787,7406,2010,1549,8692,354,7290,6499,5124,5008,5884,4570,9724,4211,"
      "4165,6000,8698,4200,6855,4612,8249,8159,4613,9891,6900,1675,621,1785,"
      "4359,777,1617,8617,8414,2844,5138,5039,5488,2461,4836,7975,5637,4592,};"
      "\nfor (int i=0; i<70;++i) {value[i] = tmp[i];\n}\n}\nint "
      "golden_vinit_rif_op() {\nreturn 1;\n}\nint main () "
      "{\nvinit_rif_op();\nprintf(\"op : %s\\n\", golden_vinit_rif_op() ? "
      "\"pass\" : \"fail\");\nint ret = 1; // 1 = success\nret &= "
      "golden_vinit_rif_op();\nif (!ret) return 1;\nreturn 0; }\n";

  std::stringstream generatedCode;
  graph.generateCCode(generatedCode);

  EXPECT_EQ(generatedCode.str(), expectedCode);
}

TEST(OneDValue, Declare_CodeGen_Int64) {
  Graph graph;
  auto value = static_cast<OneDInt64Val *>(
      graph.getNewValue(CustomValType::OneDInt64, "value", 70));
  auto op = graph.getNewOperator(CustomValType::Initialize, "op");
  op->addOutput(value);

  int64_t tmp[] = {
      1118455013, 949041300,  1176082831, 984653629,  564558821,  957352101,
      1269278183, 1803356030, 1568086099, 903749909,  172885332,  138400533,
      372968430,  2123121064, 707444096,  1543451680, 1337413647, 199831980,
      2059147599, 1394724988, 1358866311, 2124986779, 1999745043, 1595862151,
      1731904474, 1125143080, 1686233725, 188526616,  1028455787, 160537406,
      912722010,  643131549,  826748692,  946070354,  635517290,  1702916499,
      1403035124, 1440885008, 1928725884, 1977764570, 1537239724, 12284211,
      302304165,  2027276000, 452188698,  2138304200, 339856855,  1815144612,
      2130288249, 907238159,  817844613,  1619069891, 942366900,  668591675,
      1385840621, 215681785,  11364359,   2022220777, 1388401617, 308668617,
      1620438414, 320812844,  1717515138, 1949225039, 762195488,  479612461,
      1340504836, 613837975,  263405637,  1094744592,
  };
  auto data = getRawPointer(value);
  auto raw = value->raw;
  for (int i = 0; i < 70; ++i)
    data[i] = raw[i] = tmp[i];

  const char *expectedCode =
      "#include <stdbool.h>\n#include <stdint.h>\n#include "
      "<stdlib.h>\n#include <stdio.h>\n#include <string.h>\n#include "
      "<stddef.h>\n#include <riscv_vector.h>\ntypedef _Float16 "
      "float16_t;\ntypedef float float32_t;\ntypedef double "
      "float64_t;\n#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & "
      "0x03FF))\n#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & "
      "0x007FFFFF))\n#define isNaNF64UI( a ) (((~(a) & UINT64_C( "
      "0x7FF0000000000000 )) == 0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF "
      ")))\nint64_t value[70];\nvoid vinit_rif_op() {\nint64_t tmp[] = "
      "{1118455013ll,949041300ll,1176082831ll,984653629ll,564558821ll,"
      "957352101ll,1269278183ll,1803356030ll,1568086099ll,903749909ll,"
      "172885332ll,138400533ll,372968430ll,2123121064ll,707444096ll,"
      "1543451680ll,1337413647ll,199831980ll,2059147599ll,1394724988ll,"
      "1358866311ll,2124986779ll,1999745043ll,1595862151ll,1731904474ll,"
      "1125143080ll,1686233725ll,188526616ll,1028455787ll,160537406ll,"
      "912722010ll,643131549ll,826748692ll,946070354ll,635517290ll,"
      "1702916499ll,1403035124ll,1440885008ll,1928725884ll,1977764570ll,"
      "1537239724ll,12284211ll,302304165ll,2027276000ll,452188698ll,"
      "2138304200ll,339856855ll,1815144612ll,2130288249ll,907238159ll,"
      "817844613ll,1619069891ll,942366900ll,668591675ll,1385840621ll,"
      "215681785ll,11364359ll,2022220777ll,1388401617ll,308668617ll,"
      "1620438414ll,320812844ll,1717515138ll,1949225039ll,762195488ll,"
      "479612461ll,1340504836ll,613837975ll,263405637ll,1094744592ll,};\nfor "
      "(int i=0; i<70;++i) {value[i] = tmp[i];\n}\n}\nint "
      "golden_vinit_rif_op() {\nreturn 1;\n}\nint main () "
      "{\nvinit_rif_op();\nprintf(\"op : %s\\n\", golden_vinit_rif_op() ? "
      "\"pass\" : \"fail\");\nint ret = 1; // 1 = success\nret &= "
      "golden_vinit_rif_op();\nif (!ret) return 1;\nreturn 0; }\n";

  std::stringstream generatedCode;
  graph.generateCCode(generatedCode);

  EXPECT_EQ(generatedCode.str(), expectedCode);
}
