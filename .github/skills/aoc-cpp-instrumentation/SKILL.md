---
name: aoc-cpp-instrumentation
description: Teach C++ diagnostic and performance instrumentation for Advent of Code. Use for sanitizer reports, compiler warnings, clang-tidy, CMake test presets, steady_clock timing, release builds or CPU/allocation profiling; pair benchmarking with aoc-performance-lab.
---

# C++ evidence, not guesses

Do not edit files, generate scaffolds, apply fixes or install tools without an explicit request. No full puzzle solution unless explicitly requested.

Read the build configuration first. Explain what a command will do and use an existing target rather than inventing a second build system. Run checks only when requested or agreed; distinguish generated build artifacts from source edits.

## Correctness diagnostics

The commands below are examples for a day directory whose `CMakePresets.json` defines `debug`, `release` and a `sample` test preset. Confirm the preset names first (`cmake --list-presets`); for any other layout, use the targets the build files actually define.

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset sample -R '^Sample\.Part1$' --output-on-failure
```

The repository's C++ scaffold uses GoogleTest with CMake test discovery: `Sample.Part1` and `Sample.Part2` are independent CTest tests. Select `Sample.Part2` for part 2, or omit `-R` for both; the `sample` preset fails when a filter matches no test, so a typo cannot look green. CTest does not rebuild. Fill the current part's optional `SAMPLE_EXPECTED_*` value from the statement, then observe the unimplemented solver fail before implementing it. Fatal assertions stop on an unset answer or missing sample file; `-1` remains a valid expected answer. Initial configuration fetches the pinned GoogleTest dependency, so explain that network/build artifact boundary before an agreed run.

Check whether the debug build enables ASan/UBSan rather than assuming it. In other workspaces, inspect `ctest --show-only` and the runner before choosing a filter. A single aggregate CTest entry cannot isolate assertions inside its executable unless the runner provides a selector. Report per-part evidence and a failing aggregate honestly; do not invent a selector or implement part 2 to obtain green.

For a small single-translation-unit project without an existing build system, adapt the source and output names in commands like these:

```sh
g++ -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wold-style-cast -O2 dayNN.cpp -o dayNN
g++ -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wold-style-cast -g \
  -fsanitize=address,undefined -fno-omit-frame-pointer dayNN.cpp -o dayNN-debug
```

Check the compiler and library support before using a language/library feature, and check sanitizer availability on the selected platform. Do not replace an existing project's build flags or add a new build system just to copy this example.

MSVC uses different command-line options: inspect the project's build setup and current [MSVC language-mode documentation](https://learn.microsoft.com/en-us/cpp/build/reference/std-specify-language-standard-version?view=msvc-170) before suggesting `/std:c++23` or `/std:c++latest`, `/permissive-`, or `/W4`. GCC sanitizer flags are not MSVC flags.

Read the first relevant diagnostic and the owning object's lifetime with the trainee. Ask them to predict which access is invalid before proposing one local change. Do not hide warnings or turn off checks to get green.

If the build defines a tidy target (check before invoking), for example:

```sh
cmake --build --preset debug -t tidy
```

Check that clang-tidy is available; explain a finding before suggesting a change. Never apply `--fix` by default.

For a project without a tidy target, read its `.clang-tidy` configuration and compile database before suggesting an invocation. A focused standalone example is:

```sh
clang-tidy --checks='cppcoreguidelines-*,bugprone-*,performance-*,modernize-*' \
  -p build/debug dayNN.cpp
```

Check which checks are enabled and explain relevant findings; a broad check set may need project-specific filtering. Do not suppress a warning or apply `--fix` merely to make the output clean.

The scaffold enables `-Wold-style-cast` alongside its other GCC/Clang warnings. Its `tidy` target explicitly adds analyzer and C-style-cast checks and treats the latter as errors, including in the solver header; other enabled checks still follow the local configuration. Diagnose conversions rather than replacing them mechanically with named casts. Intentionally unused stub parameters use `[[maybe_unused]]`, not `(void)` casts.

## Measurement after green

Load [the shared performance lab](../aoc-performance-lab/SKILL.md). Configure/build an existing release configuration separately from timing, for example:

```sh
cmake --preset release
cmake --build --preset release
```

Inspect the executable's CLI before choosing its invocation and dataset. Do not compare sanitizer/debug timings with release timings. If the CLI has a built-in timer, read what it covers (solver only versus parsing and file I/O) and report that boundary. Existing output precision may be too coarse for microbenchmarks.

Teach `std::chrono::steady_clock` for elapsed intervals. Harness edits require explicit permission. Ensure results are observed and repeated invocations use fresh mutable state. For CPU profiling, first check whether an existing profiler is available; on Linux, `perf` may require permissions. Do not change system permissions or install tooling as a fallback. Offer coarse phase timing if profiling is unavailable.

Report exact commands, flags, test/profile evidence and limits. End with one **Next decision**.

## Sources

[GoogleTest primer](https://google.github.io/googletest/primer.html) and [CMake GoogleTest discovery](https://cmake.org/cmake/help/latest/module/GoogleTest.html) for assertions and per-case test selection.

[ASan](https://clang.llvm.org/docs/AddressSanitizer.html), [UBSan](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html), [clang-tidy](https://clang.llvm.org/extra/clang-tidy/), [C++ compiler/library support](https://en.cppreference.com/w/cpp/compiler_support), [MSVC language modes](https://learn.microsoft.com/en-us/cpp/build/reference/std-specify-language-standard-version?view=msvc-170), [steady_clock](https://en.cppreference.com/w/cpp/chrono/steady_clock), [perf](https://perfwiki.github.io/main/).
