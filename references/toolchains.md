# Toolchain cheat sheet (verified 2026-11-04)

Current-version notes were checked against public release pages on 2026-11-04; re-verify when December starts — these move.

## C++ (baseline C++23; C++26 per-feature, support-gated)

- Check feature support before use: <https://en.cppreference.com/w/cpp/compiler_support>, <https://gcc.gnu.org/projects/cxx-status.html>, Clang C++ status page.
- Scaffolded days use CMake presets (CMake ≥ 3.25): `cmake --preset debug && cmake --build --preset debug`, tests via `ctest --preset sample --output-on-failure` (ASan+UBSan on), timed real runs via `cmake --preset release && cmake --build --preset release` then `cmake --build --preset release -t run-p1`.
- Build (fast, warnings on, no scaffold): `g++ -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -O2 dayXX_pY.cpp -o dayXX_pY`
- Debug + sanitizers: `g++ -std=c++23 -g -fsanitize=address,undefined -fno-omit-frame-pointer dayXX_pY.cpp -o dayXX_pY_dbg`
- Static analysis: `clang-tidy -p build/debug day01.cpp day01_test.cpp` (the debug preset exports `compile_commands.json`; run from inside `dayNN/`)
- C++23 sweet spots for AoC: `std::print`, ranges (`views::split`, `views::enumerate`, `views::chunk`, `views::slide`, `to<vector>`), `std::from_chars`, `std::expected`, `std::mdspan`, `string::contains`.
- C++26 (verify support first): reflection, pack indexing, placeholder `_`, `std::execution`, `std::simd`.
- Core Guidelines: <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines>

## Python 3 (baseline ≥ 3.12; 3.14 series current)

- Version check: `python3 --version`. Current stable releases: <https://www.python.org/downloads/>
- Tests: `python3 -m pytest -q dayXX/` (stdlib-only fallback: `assert` harness or `python3 -m doctest file -v`)
- Profile: `python3 -m cProfile -s cumtime dayXX_pY.py` · micro: `timeit`
- Stdlib to know cold: `itertools` (batched 3.12+, pairwise, accumulate), `collections` (Counter, deque, defaultdict), `heapq`, `bisect`, `functools.cache`, `re` named groups, `dataclasses`, `pathlib`.
- Docs: <https://docs.python.org/3/library/> · typing: <https://docs.python.org/3/library/typing.html> · PEPs: <https://peps.python.org/>

## Rust (edition 2024)

- Edition guide: <https://doc.rust-lang.org/edition-guide/> (edition 2024 stable since 1.85; check <https://releases.rs/> for current stable)
- Scaffold: `cargo new dayXX` · Test: `cargo test` · Lints: `cargo clippy --all-targets -- -D warnings` · Format: `cargo fmt --check`
- Recommended `Cargo.toml` addition for puzzle binaries:
  ```toml
  [profile.release]
  overflow-checks = true
  ```
- Std docs: <https://doc.rust-lang.org/std/> · Collections choosing guide: <https://doc.rust-lang.org/std/collections/index.html> · Book: <https://doc.rust-lang.org/book/>
- Opt-in crates (team policy): `itertools`, `rayon` (parallel), `criterion` (benchmarks) — only after std-only is measured and found wanting.

## Team conventions

- One directory per day: `dayXX/` with `input_sample.txt` (from the public statement) and code; **never commit your personalized `input.txt`** (see `.gitignore`).
- Sample input/expected answer from the statement = the first failing test, in every language.
- Keep `notes/` per day: the approach comparison and the final complexity justification. Future-you in part 2 says thank you.
- Scaffold a new day: `./scripts/new_day.sh <NN> <cpp|python|rust>` from the repo root — creates `dayNN/` with the sample test wired red-first (see `templates/README.md`).
