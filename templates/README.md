# Day scaffolds — clone-and-go, red on purpose

One directory per day (`dayNN/`), created from the puzzle repo root:

    ./scripts/new_day.sh <NN> <cpp|python|rust>      # e.g. ./scripts/new_day.sh 07 cpp

Each scaffold supports the sample-first red-green loop used by the AoC Skills Coach:

- `input_sample.txt` — paste the statement's sample block here (committed;
  your personalized `input.txt` stays untracked via `.gitignore`).
- Sample tests with **sentinel expected values** — they fail with a "fill
  the expected answer" message until you put the statement's published
  answer in. That failure is the red-green anchor, not an accident.
- `part1`/`part2` stubs that fail loudly until implemented.
- Every CLI run is timed — measure, don't guess.

## The loop

1. Read the statement → paste the sample into `input_sample.txt`
2. Fill `SAMPLE_EXPECTED_*` → run the test → **red for the right reason**
3. Implement `part1` → green
4. Only now: run on the real `input.txt`, record answer + time in `notes/`
5. Part 2: usually the same model, new transformation — think before rewriting

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
