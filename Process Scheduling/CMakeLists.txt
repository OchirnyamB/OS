cmake_minimum_required(VERSION 2.8)
# Set the project name variable to project1.
project(project1)

# Add your CMAKE_C_FLAGS AND CMAKE_SXX_FLAGS here
# You should include -Wall -Werror -Wshadow
# Make SURE to use -std=c11 and -std=c++11 where relevant.

set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wshadow -Werror -DGRAD_TESTS=1")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Werror -DGRAD_TESTS=1")

#set(CMAKE_C_FLAGS "-std=c11 -Wextra -Wshadow -DGRAD_TESTS=0")
#set(CMAKE_CXX_FLAGS "-std=c++11 -Wextra -Wshadow -DGRAD_TESTS=0")



set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

# Add our include directory to CMake's search paths.
include_directories("include")

# Compile dyn_array_lib so we can use it
add_library(dyn_array SHARED src/dyn_array.c)


# Compile the analysis executable.
add_executable(analysis src/analysis.c src/process_scheduling.c)
target_compile_definitions(analysis PRIVATE)

# link the dyn_array library we compiled against our analysis executable.
target_link_libraries(analysis dyn_array)

# Compile the the tester executable.
add_executable(${PROJECT_NAME}_test test/tests.cpp src/process_scheduling.c)
target_compile_definitions(${PROJECT_NAME}_test PRIVATE GRAD_TEST=1)

# Link ${PROJECT_NAME}_test with dyn_array and gtest and pthread libraries
target_link_libraries(${PROJECT_NAME}_test dyn_array gtest pthread)
add_test (NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
