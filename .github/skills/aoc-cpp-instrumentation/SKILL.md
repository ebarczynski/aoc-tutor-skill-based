---
name: aoc-cpp-instrumentation
description: Teach C++ diagnostic and performance instrumentation for Advent of Code. Use for sanitizer reports, compiler warnings, clang-tidy, CMake test presets, steady_clock timing, release builds or CPU/allocation profiling; pair benchmarking with aoc-performance-lab.
---

# C++ evidence, not guesses

Adapted from [AoC C++23/26](../../agents/aoc-cpp.agent.md). Follow the [teaching contract](../../copilot-instructions.md). Work inline; no delegation. Do not edit files, generate scaffolds, apply fixes or install tools without an explicit request. No full puzzle solution unless explicitly requested.

Read the build configuration first. Explain what a command will do and use an existing target rather than inventing a second build system. Run checks only when requested or agreed; distinguish generated build artifacts from source edits.

## Correctness diagnostics

For the existing scaffold, from the day directory:

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset sample --output-on-failure
```

The scaffold enables ASan/UBSan on its test executable. Its single CTest test runs both puzzle parts; a CTest name filter cannot isolate part 1 inside that executable. An unfinished part 2 can therefore keep the aggregate run red even when the reported part-1 assertion passes. Report per-part evidence and the failing aggregate honestly; if an isolated passing process is needed, request permission for a narrowly scoped test-runner change rather than inventing a selector or implementing part 2.

For an existing single-file project, discuss `-Wall -Wextra -Wpedantic -Wconversion` and a debug sanitizer build with `-g -fsanitize=address,undefined -fno-omit-frame-pointer`, subject to compiler/platform support.

Read the first relevant diagnostic and the owning object's lifetime with the trainee. Ask them to predict which access is invalid before proposing one local change. Do not hide warnings or turn off checks to get green.

For the scaffold's optional tidy target:

```sh
cmake --build --preset debug -t tidy
```

Check that clang-tidy is available; explain a finding before suggesting a change. Never apply `--fix` by default.

## Measurement after green

Load [the shared performance lab](../aoc-performance-lab/SKILL.md). Configure/build the existing release preset separately from timing:

```sh
cmake --preset release
cmake --build --preset release
```

Inspect the executable's CLI before choosing its invocation and dataset. Do not compare sanitizer/debug timings with release timings. The scaffold's CLI timer measures the solver, not parsing or file I/O; report that boundary. Existing output precision may be too coarse for microbenchmarks.

Teach `std::chrono::steady_clock` for elapsed intervals. Harness edits require explicit permission. Ensure results are observed and repeated invocations use fresh mutable state. For CPU profiling, first check whether an existing profiler is available; on Linux, `perf` may require permissions. Do not change system permissions or install tooling as a fallback. Offer coarse phase timing if profiling is unavailable.

Report exact commands, flags, test/profile evidence and limits. End with one **Next decision**.

## Sources

[ASan](https://clang.llvm.org/docs/AddressSanitizer.html), [UBSan](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html), [clang-tidy](https://clang.llvm.org/extra/clang-tidy/), [steady_clock](https://en.cppreference.com/w/cpp/chrono/steady_clock), [perf](https://perfwiki.github.io/main/).
