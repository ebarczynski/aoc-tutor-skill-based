---
name: aoc-c-instrumentation
description: Teach ISO C diagnostic and performance instrumentation for Advent of Code. Use for C compiler warnings, sanitizer reports, CMake tests, clang-tidy, timing, profiling or vectorization remarks; pair benchmarking with aoc-performance-lab.
---

# C evidence, not guesses

Do not edit files, generate scaffolds, apply fixes or install tools without an explicit request. No full puzzle solution unless explicitly requested. Read the actual build configuration and explain generated artifacts before running agreed checks. Use C tooling and language mode, not C++-specific flags or idioms.
Requesting scaffolds and tests does not authorize the implementation of the algorithm; leave the solver as a stub and ask for clarification if the scope is ambiguous.

## Correctness diagnostics

If the workspace uses the C scaffold's CMake presets, run from its day directory:

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset sample -R '^sample_part1$' --output-on-failure
```

Select `sample_part2` for part 2, or omit `-R` to run both; the scaffold's `sample` preset fails when a filter matches no test, so a typo cannot look green. Rebuild before testing: CTest does not compile. Each part's expected-value flag is independent, so an unfinished part 2 does not prevent an isolated part 1 test from passing. For any other project, inspect its actual test names, build presets and sanitizer flags first.

The scaffold enables ASan and UBSan for GCC/Clang debug builds where supported. Sanitizers catch some errors, not all undefined behavior or correctness defects; interpret their first actionable report with the trainee. Check allocation size arithmetic, ownership, bounds and lifetimes rather than suppressing warnings. If `clang-tidy` is installed and the project defines a `tidy` target, `cmake --build --preset debug -t tidy` provides static analysis without applying fixes.

For a single C translation unit with no existing build system, adapt the paths and verify toolchain support:

```sh
cc -std=c17 -Wall -Wextra -Wpedantic -Wconversion -O2 dayNN.c -o dayNN
cc -std=c17 -Wall -Wextra -Wpedantic -Wconversion -g \
  -fsanitize=address,undefined -fno-omit-frame-pointer dayNN.c -o dayNN-debug
```

These are GCC/Clang-style options, not portable MSVC flags. Explain any target/platform limitations and never disable checks merely to obtain a green result.

## Measurement after green

Load [the shared performance lab](../aoc-performance-lab/SKILL.md). For an existing C scaffold, build separately from timing with `cmake --preset release` and `cmake --build --preset release`. The scaffold's CLI reports **process CPU time** for the selected solver only, excluding parsing and I/O; C `clock()` is not elapsed wall time and may be too coarse for short runs. For elapsed latency on POSIX, `clock_gettime(CLOCK_MONOTONIC)` is an option; check platform support and errors. Persisting a timing harness requires explicit edit consent.

Do not compare debug or sanitizer timings with release timings as evidence of an optimization. Profile an agreed representative input using an existing tool if available; distinguish profiler overhead, process CPU time and wall time. Check permissions and tool availability without installing tools or changing machine permissions.

When a profile identifies a hot loop, inspect compiler vectorization remarks, such as GCC `-fopt-info-vec-optimized -fopt-info-vec-missed` or Clang `-Rpass=loop-vectorize -Rpass-missed=loop-vectorize`, subject to compiler support. Explain dependencies, aliasing and missed-vectorization remarks; neither `restrict` nor vectorization guarantees a speedup. Evaluate flag or layout changes one at a time with the same input, flags, timing boundary and correctness checks.

Report exact commands, toolchain, flags, measurement boundary, observed results and what was not checked. End with one **Next decision**.

## Sources

[GCC instrumentation](https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html), [GCC optimization reports](https://gcc.gnu.org/onlinedocs/gcc/Developer-Options.html), [LLVM vectorizers](https://llvm.org/docs/Vectorizers.html), [ASan](https://clang.llvm.org/docs/AddressSanitizer.html), [UBSan](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html), [clang-tidy](https://clang.llvm.org/extra/clang-tidy/), [C `clock`](https://en.cppreference.com/w/c/chrono/clock), and [POSIX `clock_gettime`](https://pubs.opengroup.org/onlinepubs/9799919799/functions/clock_gettime.html).
