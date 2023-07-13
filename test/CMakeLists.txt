include_directories(${INC})
include_directories(${SOFTFLOAT}/include)

add_executable(testNegV testNegV.cpp)
target_link_libraries(testNegV gtest_main Graph)

add_executable(testWaddVV testWaddVV.cpp)
target_link_libraries(testWaddVV gtest_main Graph)

add_executable(testWaddVX testWaddVX.cpp)
target_link_libraries(testWaddVX gtest_main Graph)

add_executable(testAddVV testAddVV.cpp)
target_link_libraries(testAddVV gtest_main Graph)

add_executable(testAddVX testAddVX.cpp)
target_link_libraries(testAddVX gtest_main Graph)

add_executable(testSubVV testSubVV.cpp)
target_link_libraries(testSubVV gtest_main Graph)

add_executable(testSubVX testSubVX.cpp)
target_link_libraries(testSubVX gtest_main Graph)

add_executable(testOneDIntegralValue testOneDIntegralValue.cpp)
target_link_libraries(testOneDIntegralValue gtest_main Graph)

add_executable(testOneDFloatingPointValue testOneDFloatingPointValue.cpp)
target_link_libraries(testOneDFloatingPointValue gtest_main Graph)

add_executable(testScalarValue testScalarValue.cpp)
target_link_libraries(testScalarValue gtest_main Graph)

add_executable(testAddVVMask testAddVVMask.cpp)
target_link_libraries(testAddVVMask gtest_main Graph)

add_executable(testSubVVMask testSubVVMask.cpp)
target_link_libraries(testSubVVMask gtest_main Graph)

add_executable(testAddVXMask testAddVXMask.cpp)
target_link_libraries(testAddVXMask gtest_main Graph)

add_executable(testSubVXMask testSubVXMask.cpp)
target_link_libraries(testSubVXMask gtest_main Graph)

add_executable(testSllVV testSllVV.cpp)
target_link_libraries(testSllVV gtest_main Graph)

add_executable(testSllVVMask testSllVVMask.cpp)
target_link_libraries(testSllVVMask gtest_main Graph)

add_executable(testSraVV testSraVV.cpp)
target_link_libraries(testSraVV gtest_main Graph)

add_executable(testSraVVMask testSraVVMask.cpp)
target_link_libraries(testSraVVMask gtest_main Graph)

add_executable(testAndVV testAndVV.cpp)
target_link_libraries(testAndVV gtest_main Graph)

add_executable(testAndVVMask testAndVVMask.cpp)
target_link_libraries(testAndVVMask gtest_main Graph)

add_executable(testOrVV testOrVV.cpp)
target_link_libraries(testOrVV gtest_main Graph)

add_executable(testOrVVMask testOrVVMask.cpp)
target_link_libraries(testOrVVMask gtest_main Graph)

add_executable(testXorVV testXorVV.cpp)
target_link_libraries(testXorVV gtest_main Graph)

add_executable(testXorVVMask testXorVVMask.cpp)
target_link_libraries(testXorVVMask gtest_main Graph)

add_executable(testRsubVX testRsubVX.cpp)
target_link_libraries(testRsubVX gtest_main Graph)

add_executable(testRsubVXMask testRsubVXMask.cpp)
target_link_libraries(testRsubVXMask gtest_main Graph)

add_executable(testAndVX testAndVX.cpp)
target_link_libraries(testAndVX gtest_main Graph)

add_executable(testAndVXMask testAndVXMask.cpp)
target_link_libraries(testAndVXMask gtest_main Graph)

add_executable(testOrVX testOrVX.cpp)
target_link_libraries(testOrVX gtest_main Graph)

add_executable(testOrVXMask testOrVXMask.cpp)
target_link_libraries(testOrVXMask gtest_main Graph)

add_executable(testXorVX testXorVX.cpp)
target_link_libraries(testXorVX gtest_main Graph)

add_executable(testXorVXMask testXorVXMask.cpp)
target_link_libraries(testXorVXMask gtest_main Graph)

add_executable(testSllVX testSllVX.cpp)
target_link_libraries(testSllVX gtest_main Graph)

add_executable(testSllVXMask testSllVXMask.cpp)
target_link_libraries(testSllVXMask gtest_main Graph)

add_executable(testSraVX testSraVX.cpp)
target_link_libraries(testSraVX gtest_main Graph)

add_executable(testSraVXMask testSraVXMask.cpp)
target_link_libraries(testSraVXMask gtest_main Graph)

add_executable(testFadd testFadd.cpp)
target_link_libraries(testFadd gtest_main Graph)

add_executable(testFaddMask testFaddMask.cpp)
target_link_libraries(testFaddMask gtest_main Graph)

add_executable(testCpopM testCpopM.cpp)
target_link_libraries(testCpopM gtest_main Graph)

add_executable(testVfirstM testVfirstM.cpp)
target_link_libraries(testVfirstM gtest_main Graph)

add_executable(testMsbfM testMsbfM.cpp)
target_link_libraries(testMsbfM gtest_main Graph)

add_executable(testMsifM testMsifM.cpp)
target_link_libraries(testMsifM gtest_main Graph)

add_executable(testMsofM testMsofM.cpp)
target_link_libraries(testMsofM gtest_main Graph)

add_executable(testPoc testPoc.cpp)
target_link_libraries(testPoc gtest_main Graph)

add_executable(testEnumerateLmul testEnumerateLmul.cpp)
target_link_libraries(testEnumerateLmul gtest_main Graph)

add_executable(testEnumerateLmulMask testEnumerateLmulMask.cpp)
target_link_libraries(testEnumerateLmulMask gtest_main Graph)

add_executable(testDatum testDatum.cpp)
target_link_libraries(testDatum gtest_main softfloat)

add_executable(testPolicy testPolicy.cpp)
target_link_libraries(testPolicy gtest_main softfloat Graph)

include(GoogleTest)
gtest_discover_tests(testOneDIntegralValue)
gtest_discover_tests(testOneDFloatingPointValue)
gtest_discover_tests(testScalarValue)
gtest_discover_tests(testNegV)
gtest_discover_tests(testWaddVV)
gtest_discover_tests(testWaddVX)
gtest_discover_tests(testAddVV)
gtest_discover_tests(testAddVX)
gtest_discover_tests(testSubVV)
gtest_discover_tests(testSubVX)
gtest_discover_tests(testAddVVMask)
gtest_discover_tests(testSubVVMask)
gtest_discover_tests(testAddVXMask)
gtest_discover_tests(testSubVXMask)
gtest_discover_tests(testSllVV)
gtest_discover_tests(testSllVVMask)
gtest_discover_tests(testSraVV)
gtest_discover_tests(testSraVVMask)
gtest_discover_tests(testAndVV)
gtest_discover_tests(testAndVVMask)
gtest_discover_tests(testOrVV)
gtest_discover_tests(testOrVVMask)
gtest_discover_tests(testXorVV)
gtest_discover_tests(testXorVVMask)
gtest_discover_tests(testRsubVX)
gtest_discover_tests(testRsubVXMask)
gtest_discover_tests(testAndVX)
gtest_discover_tests(testAndVXMask)
gtest_discover_tests(testOrVX)
gtest_discover_tests(testOrVXMask)
gtest_discover_tests(testXorVX)
gtest_discover_tests(testXorVXMask)
gtest_discover_tests(testSllVX)
gtest_discover_tests(testSllVXMask)
gtest_discover_tests(testSraVX)
gtest_discover_tests(testSraVXMask)
gtest_discover_tests(testFadd)
gtest_discover_tests(testFaddMask)
gtest_discover_tests(testCpopM)
gtest_discover_tests(testVfirstM)
gtest_discover_tests(testMsbfM)
gtest_discover_tests(testMsifM)
gtest_discover_tests(testMsofM)
gtest_discover_tests(testPoc)
gtest_discover_tests(testEnumerateLmul)
gtest_discover_tests(testEnumerateLmulMask)
gtest_discover_tests(testPolicy)

add_test(
  NAME Golden.Codegen
  COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/TestCodeGen.py
                  --random-gen=${CMAKE_BINARY_DIR}/tool/random_gen
                  --filepath=${CMAKE_SOURCE_DIR}/include/CustomOperator.def
                  --codegen-golden=${CMAKE_SOURCE_DIR}/test/codegen-golden
                  --output-dir=${CMAKE_BINARY_DIR}/codegen-output
                  --has-policy
)

set(GCC_TOOLCHAIN_PREFIX "/sifive/tools/riscv-tools/riscv64-unknown-linux-gnu-toolsuite-13.0.0-2021.11.5-x86_64-linux-redhat8")
set(COMPILER_TOOLCHAIN_PREFIX "/sifive/tools/riscv-tools/riscv64-unknown-linux-gnu-toolsuite-13.0.0-2021.11.5-x86_64-linux-redhat8")
set(FUZZ 1)
set(NODE 20)
set(LENGTH 500)
set(ENABLE_FUSED_GEN 1)
set(RANDOM_OR_SEED "--random on")
if(DEFINED ENV{GCC_TOOLCHAIN_PREFIX})
  set(GCC_TOOLCHAIN_PREFIX $ENV{GCC_TOOLCHAIN_PREFIX})
elseif(DEFINED ENV{TOOLCHAIN_PATH})
  set(GCC_TOOLCHAIN_PREFIX $ENV{TOOLCHAIN_PATH})
endif()
if(DEFINED ENV{COMPILER_TOOLCHAIN_PREFIX})
  set(COMPILER_TOOLCHAIN_PREFIX $ENV{COMPILER_TOOLCHAIN_PREFIX})
elseif(DEFINED ENV{TOOLCHAIN_PATH})
  set(COMPILER_TOOLCHAIN_PREFIX $ENV{TOOLCHAIN_PATH})
endif()
if(DEFINED ENV{FUZZ})
  set(FUZZ $ENV{FUZZ})
endif()
if(DEFINED ENV{NODE})
  set(NODE $ENV{NODE})
endif()
if(DEFINED ENV{LENGTH})
  set(LENGTH $ENV{LENGTH})
endif()
if(DEFINED ENV{SEED})
  set(RANDOM_OR_SEED "--seed $ENV{SEED}")
endif()
if(DEFINED ENV{ENABLE_FUSED_GEN})
  set(ENABLE_FUSED_GEN "$ENV{ENABLE_FUSED_GEN}")
endif()

message(STATUS "GCC toolchain path: " ${GCC_TOOLCHAIN_PREFIX})
message(STATUS "LLVM toolchain path: " ${COMPILER_TOOLCHAIN_PREFIX})

set(GCC_TOOLCHAIN ${GCC_TOOLCHAIN_PREFIX}/bin/riscv64-unknown-linux-gnu-gcc)
execute_process(COMMAND ${GCC_TOOLCHAIN} --print-sysroot OUTPUT_VARIABLE SYSROOT OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CLANG "${COMPILER_TOOLCHAIN_PREFIX}/bin/riscv64-unknown-linux-gnu-clang")
set(CFLAGS "-target riscv64-unknown-linux-gnu --sysroot ${SYSROOT} --gcc-toolchain=${GCC_TOOLCHAIN_PREFIX}")
set(POLICY_ENABLE "")

execute_process(
  COMMAND
  bash -c "${CLANG} ${CFLAGS} -march=rv64gcv_zfh_zvfh0p1 -menable-experimental-extensions -c ${CMAKE_SOURCE_DIR}/test/codegen-golden/AddVV8VInt8TA.c"
  RESULT_VARIABLE OK
)

if("${OK}" STREQUAL "0")
  set(POLICY_ENABLE "--has-policy")
endif()

foreach(count RANGE 1 ${FUZZ})
  add_test(
    NAME Test.FuzzTestRandomGen${count}
    COMMAND
    sh -c "rm -rf fuzz_test_random_gen${count} && mkdir fuzz_test_random_gen${count} && cd fuzz_test_random_gen${count} && \
    ${CMAKE_SOURCE_DIR}/rif-test --gen-path ${CMAKE_BINARY_DIR}/tool --sim ${CMAKE_SOURCE_DIR}/prebuilt/metal-run/qemu-run --cc ${CLANG} --arch rv64gcv_zfh_zvfh0p1 --cflags \"${CFLAGS}\" ${POLICY_ENABLE} --node ${NODE} --length ${LENGTH} ${RANDOM_OR_SEED} && \
    make -j$(nproc)"
  )
endforeach()

if("${ENABLE_FUSED_GEN}" STREQUAL "1")
  foreach(count RANGE 1 ${FUZZ})
    add_test(
      NAME Test.FuzzTestFusedGen${count}
      COMMAND
      sh -c "rm -rf fuzz_test_fused_gen${count} && mkdir fuzz_test_fused_gen${count} && cd fuzz_test_fused_gen${count} && \
      ${CMAKE_SOURCE_DIR}/rif-test --gen fused_gen --gen-path ${CMAKE_BINARY_DIR}/tool --sim ${CMAKE_SOURCE_DIR}/prebuilt/metal-run/qemu-run --cc ${CLANG} --arch rv64gcv_zfh_zvfh0p1 --cflags \"${CFLAGS}\" ${POLICY_ENABLE} --node ${NODE} --length ${LENGTH} ${RANDOM_OR_SEED} && \
      make -j$(nproc)"
    )
  endforeach()
endif()
