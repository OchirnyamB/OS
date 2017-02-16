cmake_minimum_required (VERSION 3.5)
enable_testing()
project(assignment1)


#include_directories ("include/")
set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wshadow -Werror -I../include")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Werror -I../include")
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

add_library(bitmap SHARED src/bitmap.c)

add_library (block_store SHARED src/block_store.c)
target_link_libraries(block_store PRIVATE bitmap)

add_executable(${PROJECT_NAME}_test test/tests.cpp)
target_compile_definitions(${PROJECT_NAME}_test PRIVATE GRAD_TESTS=0)
target_link_libraries(${PROJECT_NAME}_test block_store gtest pthread)

add_test (NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
