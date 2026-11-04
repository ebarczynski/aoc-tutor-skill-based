// dayNN.hpp — parse / model / solve for this day.
// Header-only so the test binary runs *exactly* the code the answer binary
// runs; the .cpp holds only main(). Split out if it outgrows a header.
#ifndef AOC_DAY_HPP
#define AOC_DAY_HPP

#include <cstdint>
#include <istream>
#include <stdexcept>
#include <string>

namespace day01 {

struct Model {
    // TODO: your data model. Prefer strong types (row/col wrappers, enums):
    // x-vs-y and row-vs-col mixups are AoC's favorite tax on the unwary.
};

inline Model parse(std::istream& in) {
    Model model{};
    std::string line;
    while (std::getline(in, line)) {
        // TODO: per-line parsing — std::from_chars (no exceptions, no
        // allocation), string_view, or ranges views when they clarify.
        (void)line;
    }
    return model;
}

inline std::int64_t part1(const Model& model) {
    (void)model;
    throw std::logic_error("part1 not implemented — sample test first");
}

inline std::int64_t part2(const Model& model) {
    (void)model;
    throw std::logic_error("part2 not implemented — it usually reuses part 1's model");
}

}  // namespace day01

#endif  // AOC_DAY_HPP
