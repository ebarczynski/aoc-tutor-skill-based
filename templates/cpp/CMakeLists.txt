# Day scaffold build — CMake presets (see CMakePresets.json):
#   cmake --preset debug && cmake --build --preset debug      # ASan+UBSan ON
#   ctest --preset sample --output-on-failure                 # red-green anchor
#   cmake --preset release && cmake --build --preset release  # timed real runs
# Requires CMake >= 3.25, GCC >= 13 or Clang >= 17 (C++23).
# MSVC is an untested lane here; CMAKE_CXX_STANDARD 23 maps to its nearest flag.
cmake_minimum_required(VERSION 3.25)
project(day01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(AOC_SANITIZERS "Build day01_test with ASan+UBSan (GCC/Clang)" ON)

function(aoc_warnings tgt)
    if(MSVC)
        target_compile_options(${tgt} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${tgt} PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
    endif()
endfunction()

add_executable(day01 day01.cpp day01.hpp)
aoc_warnings(day01)

add_executable(day01_test day01_test.cpp day01.hpp)
aoc_warnings(day01_test)
if(AOC_SANITIZERS AND NOT MSVC)
    target_compile_options(day01_test PRIVATE -g -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(day01_test PRIVATE -fsanitize=address,undefined)
endif()

enable_testing()
# The statement's sample input/answers are the first failing test:
add_test(NAME sample
         COMMAND day01_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Timed runs on the real (personalized, untracked) input:
add_custom_target(run-p1
    COMMAND $<TARGET_FILE:day01> 1 input.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS day01)
add_custom_target(run-p2
    COMMAND $<TARGET_FILE:day01> 2 input.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS day01)

find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
    add_custom_target(tidy
        COMMAND ${CLANG_TIDY_EXE} -p build/debug day01.cpp day01_test.cpp
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM)
endif()
