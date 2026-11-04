# Day scaffold — zero dependency. `make test` first (red-green), then `make run-p1`.
# Requires GCC 13+ or Clang 17+ for -std=c++23 (downgrade: make STD=-std=c++20).
CXX ?= g++
STD ?= -std=c++23
WARN := -Wall -Wextra -Wpedantic -Wconversion

day01: day01.cpp day01.hpp
	$(CXX) $(STD) $(WARN) -O2 $< -o $@

day01_test: day01_test.cpp day01.hpp
	$(CXX) $(STD) $(WARN) -g -fsanitize=address,undefined -fno-omit-frame-pointer $< -o $@

.PHONY: test run-p1 run-p2 tidy clean

test: day01_test
	./day01_test

run-p1: day01
	./day01 1 input.txt

run-p2: day01
	./day01 2 input.txt

tidy:
	clang-tidy day01.cpp day01_test.cpp -- $(STD) $(WARN)

clean:
	rm -f day01 day01_test
