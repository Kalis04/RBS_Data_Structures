cmake_minimum_required(VERSION 3.22)
project(bs0013_week02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

function(add_lab_target target source)
    add_executable(${target} ${source})
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
endfunction()

add_lab_target(pointer_trace src/pointer_trace.cpp)
add_lab_target(lifetime src/lifetime.cpp)
add_lab_target(dynamic_value src/dynamic_value.cpp)
add_lab_target(node_chain src/node_chain.cpp)

function(add_asan_target target source)
    add_executable(${target} EXCLUDE_FROM_ALL ${source})
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(${target} PRIVATE -fsanitize=address,undefined)
endfunction()

add_asan_target(use_after_free_asan src/use_after_free.cpp)
add_asan_target(double_delete_asan src/double_delete.cpp)

include(CTest)
if(BUILD_TESTING)
    add_test(NAME pointer_trace_runs COMMAND pointer_trace)
    add_test(NAME lifetime_runs COMMAND lifetime)
    add_test(NAME dynamic_value_runs COMMAND dynamic_value)
    add_test(NAME node_chain_runs COMMAND node_chain)
endif()
