# Day scaffolds — clone-and-go, red on purpose

One directory per day (`dayNN/`), created from the puzzle repo root:

    ./scripts/new_day.sh <NN> <c|cpp|python|rust>      # e.g. ./scripts/new_day.sh 07 c

Each scaffold supports the sample-first red-green loop used by the AoC Skills Coach:

- `input_sample.txt` — paste the statement's sample block here (committed;
  your personalized `input.txt` stays untracked via `.gitignore`).
- Sample tests with **unset expected answers** — they fail with a "fill
  the expected answer" message until you put the statement's published
  answer in. The C scaffold uses separate flags so every `int64_t` value,
  including negative answers, is representable.
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
and test, so it can remain red without obscuring part 1. The release CLI
reports solver **CPU time** using C `clock()`; it excludes parsing and I/O and
is not elapsed wall time. The placeholder model owns no resources; if you add
allocations, define and call an appropriate cleanup function on all paths.

## C++23 (`templates/cpp`)

Requires CMake ≥ 3.25 (for the presets) and GCC 13+ or Clang 17+; feature-test
macros in `day01.cpp` fall back from `std::println` to `std::cout` on older
libstdc++. All commands run from inside `dayNN/`:

    cmake --preset debug && cmake --build --preset debug   # ASan+UBSan build
    cmake --build --preset debug && ctest --preset sample --output-on-failure  # rebuild + red-green anchor
    cmake --preset release && cmake --build --preset release
    cmake --build --preset release -t run-p1               # timed run, real input
    cmake --build --preset debug -t tidy                   # clang-tidy, if installed

## Python 3 (`templates/python`, 3.12+ stdlib only)

    python3 dayNN/test_solution.py                        # zero-dependency runner
    python3 -m pytest -q dayNN --import-mode=importlib    # if pytest is installed
                                                          # (importlib avoids
                                                          # same-name module
                                                          # clashes across days)
    python3 dayNN/solution.py 1 dayNN/input.txt

## Rust 2024 (`templates/rust`, edition 2024 = rustc ≥ 1.85)

    cargo test --manifest-path dayNN/Cargo.toml           # inline sample tests
    cargo run --release --manifest-path dayNN/Cargo.toml -- 1 dayNN/input.txt
    cargo clippy --manifest-path dayNN/Cargo.toml --all-targets -- -D warnings

`[profile.release] overflow-checks = true` is pre-set: debug builds check
arithmetic, plain release wraps silently — the scaffold refuses that trap.
