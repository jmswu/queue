set(SRC_DIR src)

add_library(my_lib
    ${SRC_DIR}/add.c
    ${SRC_DIR}/add.cpp
)

target_include_directories(my_lib PUBLIC include)