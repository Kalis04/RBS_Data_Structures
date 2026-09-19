cmake_minimum_required(VERSION 3.22)
project(bs0013_week03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

function(enable_lab_warnings target)
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
endfunction()

add_library(int_vector src/int_vector.cpp)
target_include_directories(int_vector PUBLIC include)
enable_lab_warnings(int_vector)

add_executable(week03_demo src/main.cpp)
target_link_libraries(week03_demo PRIVATE int_vector)
enable_lab_warnings(week03_demo)

add_executable(vector_growth src/vector_growth.cpp)
enable_lab_warnings(vector_growth)

add_executable(reallocation_demo src/reallocation_demo.cpp)
enable_lab_warnings(reallocation_demo)

add_executable(public_tests tests/public_tests.cpp)
target_link_libraries(public_tests PRIVATE int_vector)
enable_lab_warnings(public_tests)

include(CTest)
if(BUILD_TESTING)
    add_test(NAME week03_public_tests COMMAND public_tests)
endif()
