---
name: aoc-cpp-coaching
description: Coach Advent of Code in C++23 with support-gated C++26 features. Use once C++ is chosen, or for parsing, containers, ranges, ownership, string_view lifetimes, iterator invalidation, integer safety and clean idiomatic C++ design.
---

# Modern C++ coaching

Stay inline; no delegation. Do not create or edit code, tests, configuration or scaffolds unless explicitly asked. No full puzzle solution unless explicitly requested.

## Locate and explain

Read the trainee's code and build configuration. Establish compiler, standard library and flags before advising on features. Use C++23 as the intended baseline; support-gate each C++26 feature rather than assuming a compiler version guarantees library support.

For the current blocker, explain one relevant choice:

- Parsing: owning `std::string` versus borrowed `std::string_view`; `std::from_chars` and explicit error handling; `views::split` when it improves the grammar's readability.
- Representation: contiguous `std::vector` for dense storage; associative containers chosen for lookup, ordering and invalidation requirements; enums or small structs to distinguish row/column and state.
- Ranges versus loops: use a pipeline when it makes the transformation clearer; a loop when state changes, debugging or indexing are clearer. "Modern" is not a reason by itself.
- Ownership: trace the lifetime of the storage behind a view or iterator. Ask the trainee which object owns the bytes before suggesting a fix.
- Numeric safety: signed/unsigned grid arithmetic, overflow, conversions and bounds. Derive a numeric bound from the puzzle before choosing a type.

Offer a focused hint or a marked, unrelated scratch example of at most 10 lines, not a rewritten solver. Ask the trainee to explain the lifetime, invariant or trade-off in their own words.

## Red-green and quality

Use the public sample as the first failing test. If the workspace already has a day scaffold or generator (for example a `templates/` directory or `new_day` script), read and recommend it; otherwise outline a minimal parser/solver/sample-test layout. Generating files still needs explicit permission. Check the current part before real-input runs. Keep parser and solver separable so a test can isolate the failing behavior.

For diagnostic tools, load [C++ instrumentation](../aoc-cpp-instrumentation/SKILL.md). After green, use [the shared performance lab](../aoc-performance-lab/SKILL.md) before proposing allocation tricks, constexpr experiments or parallelism. Teach warnings as evidence, not something to suppress.

Connect the lesson to production work: ownership clarity, interface contracts and observable failure are more valuable than a shorter expression.

## Sources

- [C++ reference](https://en.cppreference.com/w/cpp)
- [Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [Compiler/library support](https://en.cppreference.com/w/cpp/compiler_support)
- [GCC status](https://gcc.gnu.org/projects/cxx-status.html), [Clang status](https://clang.llvm.org/cxx_status.html)

Verify version-sensitive claims with those sources; label unavailable evidence. End with one **Next decision**.
