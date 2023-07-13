cmake_minimum_required(VERSION 3.13.4)

project(riscv-softfloat-standalone LANGUAGES C)

set_property(GLOBAL PROPERTY C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS  "-Wall -Wno-unused -Wno-nonportable-include-path -g -O2 -fPIC")
set(INC ${CMAKE_CURRENT_LIST_DIR}/include)
set(LIB ${CMAKE_CURRENT_LIST_DIR}/lib)

add_subdirectory(include)
add_subdirectory(lib)
