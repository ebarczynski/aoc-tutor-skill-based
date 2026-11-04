// First failing test: the statement's sample input + its published answers.
// 1. Paste the sample block into input_sample.txt
// 2. Fill expected_p1 / expected_p2 below with the answers from the statement.
// 3. cmake --build --preset debug && ctest --preset sample --output-on-failure
//    — red for the *right* reason, then implement in dayNN.hpp. (ctest does
//    NOT rebuild — always build before testing.)
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "day01.hpp"

namespace {

constexpr std::int64_t kUnset = -1;  // sentinel: "expected value not filled in"
// TODO: replace with the answers printed in the puzzle statement:
std::int64_t expected_p1 = kUnset;
std::int64_t expected_p2 = kUnset;

std::string read_sample() {
    const std::ifstream in{"input_sample.txt"};
    if (!in) {
        std::cout << "FAIL: input_sample.txt missing — paste the statement's sample input there\n";
        return {};
    }
    std::ostringstream buf;
    buf << in.rdbuf();
    return buf.str();
}

int failures = 0;

void run(const char* name, int part, std::int64_t expected) {
    if (expected == kUnset) {
        std::cout << "FAIL: " << name << " — fill the expected sample answer in day01_test.cpp\n";
        ++failures;
        return;
    }
    std::istringstream in{read_sample()};
    try {
        const std::int64_t got =
            (part == 1) ? day01::part1(day01::parse(in)) : day01::part2(day01::parse(in));
        if (got == expected) {
            std::cout << "PASS: " << name << '\n';
        } else {
            std::cout << "FAIL: " << name << " — expected " << expected << ", got " << got << '\n';
            ++failures;
        }
    } catch (const std::exception& e) {
        std::cout << "FAIL: " << name << " — threw: " << e.what() << '\n';
        ++failures;
    }
}

}  // namespace

int main() {
    run("part1 on sample", 1, expected_p1);
    run("part2 on sample", 2, expected_p2);
    if (failures == 0) {
        std::cout << "ALL GREEN — now build release and run the real input (see templates/README.md)\n";
        return 0;
    }
    std::cout << failures << " failing — stay red until green\n";
    return 1;
}
