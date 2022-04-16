set(SRC_DIR src)

add_library(my_queue
    ${SRC_DIR}/queue.c
)

target_include_directories(my_queue PUBLIC include)