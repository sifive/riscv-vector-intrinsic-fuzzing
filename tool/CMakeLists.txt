include_directories(${INC})
include_directories(${SOFTFLOAT}/include)

add_library(RandomGenUtils RandomGenUtils.cpp)

add_executable(poc poc.cpp)
target_link_libraries(poc Graph Utils)

add_executable(random_gen random_gen.cpp)
target_link_libraries(random_gen Graph Utils RandomGenUtils)

add_executable(fused_gen fused_gen.cpp)
target_link_libraries(fused_gen Graph FuseGraph Utils RandomGenUtils)
