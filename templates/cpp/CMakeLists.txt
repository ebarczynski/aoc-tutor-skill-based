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
        target_compile_options(${tgt} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wold-style-cast)
    endif()
endfunction()

add_executable(day01 day01.cpp day01.hpp)
aoc_warnings(day01)

include(CTest)
if(BUILD_TESTING)
    include(FetchContent)
    # GoogleTest v1.17.0, pinned to an immutable release commit.
    FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        SYSTEM)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(day01_test day01_test.cpp day01.hpp)
    target_link_libraries(day01_test PRIVATE GTest::gtest_main)
    aoc_warnings(day01_test)
    if(AOC_SANITIZERS AND NOT MSVC)
        target_compile_options(day01_test PRIVATE -g -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(day01_test PRIVATE -fsanitize=address,undefined)
    endif()

    include(GoogleTest)
    gtest_discover_tests(day01_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

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
    set(AOC_TIDY_SOURCES day01.cpp)
    if(BUILD_TESTING)
        list(APPEND AOC_TIDY_SOURCES day01_test.cpp)
    endif()
    add_custom_target(tidy
        COMMAND ${CLANG_TIDY_EXE} -p build/debug
            --checks=clang-analyzer-*,cppcoreguidelines-pro-type-cstyle-cast
            --warnings-as-errors=cppcoreguidelines-pro-type-cstyle-cast,clang-diagnostic-old-style-cast
            "--header-filter=${CMAKE_CURRENT_SOURCE_DIR}/day[0-9]+\\.hpp$"
            ${AOC_TIDY_SOURCES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM)
endif()
