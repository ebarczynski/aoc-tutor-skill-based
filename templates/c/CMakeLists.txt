cmake_minimum_required(VERSION 3.25)
project(day01 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(AOC_SANITIZERS "Build with ASan and UBSan (GCC/Clang)" ON)

function(aoc_configure target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
    endif()
    if(AOC_SANITIZERS AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang" AND NOT MSVC)
        target_compile_options(${target} PRIVATE -g -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(${target} PRIVATE -fsanitize=address,undefined)
    endif()
endfunction()

add_executable(day01 day01.c day01_solver.c)
aoc_configure(day01)

add_executable(day01_test day01_test.c day01_solver.c)
aoc_configure(day01_test)

enable_testing()
add_test(NAME sample_part1 COMMAND day01_test 1)
add_test(NAME sample_part2 COMMAND day01_test 2)
set_tests_properties(sample_part1 sample_part2 PROPERTIES
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_custom_target(run-p1
    COMMAND $<TARGET_FILE:day01> 1 input.txt
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    DEPENDS day01)
add_custom_target(run-p2
    COMMAND $<TARGET_FILE:day01> 2 input.txt
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    DEPENDS day01)

find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
    add_custom_target(tidy
        COMMAND "${CLANG_TIDY_EXE}" -p build/debug day01.c day01_solver.c day01_test.c
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        VERBATIM)
endif()
