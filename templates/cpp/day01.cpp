// Day binary: ./day01 <1|2> <input-file>
// Sample tests run under ASan+UBSan first — red-green before this:
//   cmake --preset debug && cmake --build --preset debug
//   ctest --preset sample --output-on-failure
// Each run is timed: measure, don't guess (repo teaching contract, §5).
#include <chrono>
#include <fstream>
#include <iostream>
#include <version>
#if defined(__cpp_lib_print)
#include <print>
#endif
#include <string>

#include "day01.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3 || (std::string(argv[1]) != "1" && std::string(argv[1]) != "2")) {
        std::cerr << "usage: day01 <1|2> <input-file>\n";
        return 2;
    }
    std::ifstream file{argv[2]};
    if (!file) {
        std::cerr << "cannot open " << argv[2] << '\n';
        return 2;
    }
    const auto model = day01::parse(file);
    const int part = std::stoi(argv[1]);
    const auto start = std::chrono::steady_clock::now();
    const std::int64_t answer = (part == 1) ? day01::part1(model) : day01::part2(model);
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::steady_clock::now() - start)
                        .count();
#if defined(__cpp_lib_print)
    std::println("part {}: {} ({} ms)", part, answer, ms);
#else
    std::cout << "part " << part << ": " << answer << " (" << ms << " ms)\n";
#endif
    return 0;
}
