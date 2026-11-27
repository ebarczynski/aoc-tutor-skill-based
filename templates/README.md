# Day scaffolds — clone-and-go, red on purpose

One directory per day (`dayNN/`), created from the puzzle repo root:

    ./scripts/new_day.sh <NN> <c|cpp|python|rust>      # e.g. ./scripts/new_day.sh 07 c

Each scaffold supports the sample-first red-green loop used by the AoC Skills Coach:

- `input_sample.txt` — paste the statement's sample block here (committed;
  your personalized `input.txt` stays untracked via `.gitignore`).
- Sample tests with **unset expected answers** — they fail with a "fill
  the expected answer" message until you put the statement's published
  answer in. Unset is never a valid number: C uses separate flags, C++ uses
  `std::optional`, Python uses `None` and Rust uses `Option`, so every answer,
  including `-1` and other negatives, is representable.
- `part1`/`part2` stubs that fail loudly until implemented.
- Every CLI run is timed — measure, don't guess.

## The loop

1. Read the statement → paste the sample into `input_sample.txt`
2. Fill `SAMPLE_EXPECTED_*` → run the test → **red for the right reason**
3. Implement `part1` → green
4. Check relevant edge cases; only then run on the real `input.txt` if agreed.
5. Part 2: usually the same model, new transformation — think before rewriting

## C17 (`templates/c`)

Requires CMake ≥ 3.25 and a C17 compiler. Debug builds enable ASan and UBSan
with GCC/Clang where available. From inside `dayNN/`:

    cmake --preset debug && cmake --build --preset debug
    ctest --preset sample -R '^sample_part1$' --output-on-failure
    ctest --preset sample -R '^sample_part2$' --output-on-failure
    ctest --preset sample --output-on-failure             # both parts
    cmake --preset release && cmake --build --preset release
    cmake --build --preset release -t run-p1               # local real input
    cmake --build --preset debug -t tidy                   # if clang-tidy is installed

Paste the sample into `input_sample.txt`, fill `SAMPLE_EXPECTED_P1` in
`dayNN_test.c`, and set `SAMPLE_EXPECTED_P1_SET` to `true`. After confirming
the part 1 test fails for the unimplemented solver, implement `dayNN_parse`
and `dayNN_part1` in `dayNN_solver.c`. Part 2 has its own expected-value flag
and test, so it can remain red without obscuring part 1. The `sample` preset
treats a filter that matches no test as an error rather than a pass. The release CLI
reports solver **CPU time** using C `clock()`; it excludes parsing and I/O and
is not elapsed wall time. The placeholder model owns no resources; if you add
allocations, define and call an appropriate cleanup function on all paths.

## C++23 (`templates/cpp`)

Requires CMake ≥ 3.25 (for the presets) and GCC 13+ or Clang 17+; feature-test
macros in `day01.cpp` fall back from `std::println` to `std::cout` on older
libstdc++. **GoogleTest is the standard C++ test framework.** CMake fetches
GoogleTest v1.17.0 at a pinned commit during configuration (network access is
required on the first configure of each build directory). No global installation
is needed. For offline builds with an existing source checkout, configure with
`-DFETCHCONTENT_SOURCE_DIR_GOOGLETEST=/absolute/path/to/googletest`; to build
only the CLI without fetching tests, use `-DBUILD_TESTING=OFF`.
All commands run from inside `dayNN/`:

    cmake --preset debug && cmake --build --preset debug   # ASan+UBSan build
    ctest --preset sample -R '^Sample\.Part1$' --output-on-failure
    ctest --preset sample -R '^Sample\.Part2$' --output-on-failure
    ctest --preset sample --output-on-failure              # both parts; rebuild after edits
    cmake --preset release && cmake --build --preset release
    cmake --build --preset release -t run-p1               # timed run, real input
    cmake --build --preset debug -t tidy                   # clang-tidy, if installed

Replace `std::nullopt` in the current part's `SAMPLE_EXPECTED_P1` or
`SAMPLE_EXPECTED_P2` in `dayNN_test.cpp` with the published integer answer.
Each GoogleTest case is discovered separately by CTest, so part 2 can remain
red while part 1 is green. The `sample` preset treats a filter that matches no
test as an error rather than a pass. Unset answers and missing sample files fail with
fatal assertions; they are never skipped or treated as empty input.
The CLI reports elapsed solver time using `std::chrono::steady_clock`,
excluding parsing and I/O.

GCC/Clang builds enable `-Wold-style-cast`. The scaffold uses no C-style
casts: intentionally unused stub parameters use `[[maybe_unused]]`.
The `tidy` target adds analyzer and C-style-cast checks, checks the solver
header, and treats C-style-cast findings as errors. Fix diagnostic causes
rather than inserting casts to silence warnings.

## Python 3 (`templates/python`, 3.12+ stdlib only)

    python3 dayNN/test_solution.py                        # zero-dependency runner, both parts
    python3 dayNN/test_solution.py 1                      # current part only (1 or 2)
    python3 -m pytest -q dayNN --import-mode=importlib    # if pytest is installed
                                                          # (importlib avoids
                                                          # same-name module
                                                          # clashes across days)
    python3 dayNN/solution.py 1 dayNN/input.txt

Replace `None` in the current part's `SAMPLE_EXPECTED_P1` or
`SAMPLE_EXPECTED_P2` with the published integer answer. A missing or empty
`input_sample.txt` fails with guidance instead of a traceback.

## Rust 2024 (`templates/rust`, edition 2024 = rustc ≥ 1.85)

    cargo test --manifest-path dayNN/Cargo.toml           # inline sample tests, both parts
    cargo test --manifest-path dayNN/Cargo.toml part1_sample   # current part only
    cargo run --release --manifest-path dayNN/Cargo.toml -- 1 dayNN/input.txt
    cargo clippy --manifest-path dayNN/Cargo.toml --all-targets -- -D warnings

Replace `None` with `Some(answer)` in the current part's `SAMPLE_EXPECTED_P1`
or `SAMPLE_EXPECTED_P2`. Check that the filtered run reports `1 passed`:
`cargo test` exits successfully when a misspelled filter matches no tests.

`[profile.release] overflow-checks = true` is pre-set: debug builds check
arithmetic, plain release wraps silently — the scaffold refuses that trap.
