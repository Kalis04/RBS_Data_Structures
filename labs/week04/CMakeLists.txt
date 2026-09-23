cmake_minimum_required(VERSION 3.16)
project(bs0013_week04_linked_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

add_library(int_linked_list src/int_linked_list.cpp)
target_include_directories(int_linked_list PUBLIC include)
target_compile_options(int_linked_list PRIVATE -Wall -Wextra -Wpedantic)

if(ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(int_linked_list PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(int_linked_list PUBLIC -fsanitize=address,undefined)
endif()

add_executable(week04_demo src/main.cpp)
target_link_libraries(week04_demo PRIVATE int_linked_list)
target_compile_options(week04_demo PRIVATE -Wall -Wextra -Wpedantic)

enable_testing()
add_executable(week04_public_tests tests/public_tests.cpp)
target_link_libraries(week04_public_tests PRIVATE int_linked_list)
target_compile_options(week04_public_tests PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME week04_public_tests COMMAND week04_public_tests)
