cmake_minimum_required (VERSION 3.12)

project (my_project VERSION 2.0.7)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED true)
set (CMAKE_EXPORT_COMPILE_COMMANDS true)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set (TEST_SRC_FOLDER unit_test)
set (TEST_SRC_FILES 
        "${TEST_SRC_FOLDER}/add_test.cpp"
    )

# cppcheck
if (USE_CPPCHECK)
    find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
    if (CMAKE_CXX_CPPCHECK)
        message(STATUS "CPPCHECK enable")
        list(
            APPEND CMAKE_CXX_CPPCHECK 
                "--enable=warning"
                "--inconclusive"
                "--force" 
                "--inline-suppr"
                "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
        )
    endif()
endif()

# move the clang-tidy config to .clang-tidy file on the working folder

# find_program(CMAKE_CXX_CLANG_TIDY NAMES clang-tidy)
# if (CMAKE_CXX_CLANG_TIDY)
#     list(
#         APPEND CMAKE_CXX_CLANG_TIDY 
#             #"-header-filter=^.*(third-party/googletest).*"
#             "-checks=*"
#             #"-warnings-as-errors=*"
#     )
# endif()

add_subdirectory(my_lib)
add_executable (${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} my_queue)

enable_testing()
add_executable (unit_test ${TEST_SRC_FILES})
target_link_libraries (unit_test PRIVATE my_queue ${CONAN_LIBS})
include(GoogleTest)
gtest_discover_tests(unit_test)

# legacy stuff, keeping as records for now, these will be removed in time

# set (GCC_C_COVERAGE_COMPILE_FLAGS -Werror -Wall -Wextra -Wpointer-arith -Wcast-align -Wwrite-strings -Wswitch-default -Wunreachable-code -Winit-self -Wmissing-field-initializers -Wno-unknown-pragmas -Wstrict-prototypes -Wundef -Wold-style-definition -Wno-misleading-indentation)
# set (GCC_CXX_COVERAGE_COMPILE_FLAGS -Werror -Wall -Wextra -Wpointer-arith -Wcast-align -Wwrite-strings -Wswitch-default -Wunreachable-code -Winit-self -Wmissing-field-initializers -Wno-unknown-pragmas -Wundef -Wno-misleading-indentation)
# 
# set (CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${GCC_C_COVERAGE_COMPILE_FLAGS})
# set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${GCC_CXX_COVERAGE_COMPILE_FLAGS})
