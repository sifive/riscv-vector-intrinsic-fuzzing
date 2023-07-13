cmake_minimum_required(VERSION 3.13.4)

project(vector-intrinsic-fuzzing LANGUAGES CXX C)

set_property(GLOBAL PROPERTY C_STANDARD 11)
set_property(GLOBAL PROPERTY CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

set(INC ${CMAKE_CURRENT_LIST_DIR}/include)
set(SPIKE ${CMAKE_CURRENT_LIST_DIR}/riscv-isa-sim)
set(LIB ${CMAKE_CURRENT_LIST_DIR}/library)
set(SOFTFLOAT ${CMAKE_CURRENT_LIST_DIR}/extern/riscv-softfloat-standalone)
set(METAL_RUN ${CMAKE_CURRENT_LIST_DIR}/prebuilt/metal-run)

execute_process(COMMAND git submodule update --init --recursive ${SOFTFLOAT} WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
execute_process(COMMAND git submodule update --init --recursive ${METAL_RUN} WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

add_custom_target(clean_headers
 COMMAND rm -rf ${CMAKE_CURRENT_SOURCE_DIR}/include/autogen
 COMMAND rm -rf ${CMAKE_CURRENT_SOURCE_DIR}/include/AutoGenComputeOp.h
 COMMENT "Clean header files with golden compute functions for operators"
)

add_custom_target(generate_headers ALL
 COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/scripts/GenerateOperatorComputeHeaders.py ${CMAKE_CURRENT_SOURCE_DIR}
 DEPENDS clean_headers
 COMMENT "Generate header files with golden compute functions for operators"
)

# GoogleTest requires at least C++11
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(extern)
add_subdirectory(include)
add_subdirectory(library)
add_subdirectory(tool)
add_subdirectory(test)
