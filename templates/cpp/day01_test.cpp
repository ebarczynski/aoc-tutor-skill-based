// Paste the statement's sample into input_sample.txt and fill the expected
// answer for the current part. Rebuild before CTest: CTest does not compile.
#include <cstdint>
#include <fstream>
#include <optional>

#include <gtest/gtest.h>

#include "day01.hpp"

namespace {

constexpr std::optional<std::int64_t> SAMPLE_EXPECTED_P1 = std::nullopt;
constexpr std::optional<std::int64_t> SAMPLE_EXPECTED_P2 = std::nullopt;

TEST(Sample, Part1) {
    ASSERT_TRUE(SAMPLE_EXPECTED_P1.has_value())
        << "fill SAMPLE_EXPECTED_P1 with the expected sample answer in day01_test.cpp";
    std::ifstream in{"input_sample.txt"};
    ASSERT_TRUE(in.is_open())
        << "input_sample.txt missing — paste the statement's sample input there";
    const auto model = day01::parse(in);
    ASSERT_FALSE(in.bad()) << "cannot read input_sample.txt";
    EXPECT_EQ(day01::part1(model), *SAMPLE_EXPECTED_P1);
}

TEST(Sample, Part2) {
    ASSERT_TRUE(SAMPLE_EXPECTED_P2.has_value())
        << "fill SAMPLE_EXPECTED_P2 with the expected sample answer in day01_test.cpp";
    std::ifstream in{"input_sample.txt"};
    ASSERT_TRUE(in.is_open())
        << "input_sample.txt missing — paste the statement's sample input there";
    const auto model = day01::parse(in);
    ASSERT_FALSE(in.bad()) << "cannot read input_sample.txt";
    EXPECT_EQ(day01::part2(model), *SAMPLE_EXPECTED_P2);
}

}  // namespace
