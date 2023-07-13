include_directories(${INC})

file(GLOB SRC
     "*.c"
)

add_library(softfloat ${SRC})