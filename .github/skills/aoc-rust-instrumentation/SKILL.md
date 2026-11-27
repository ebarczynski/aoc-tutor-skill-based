---
name: aoc-rust-instrumentation
description: Teach Rust testing, linting and measurement instrumentation for Advent of Code. Use for cargo test failures, clippy, format checks, overflow profiles, Instant timing, release profiling or optional benchmark tooling; pair optimization with aoc-performance-lab.
---

# Rust evidence, not guesses

Do not edit files, generate scaffolds, apply fixes or install tools without an explicit request. No full puzzle solution unless explicitly requested.
Requesting scaffolds and tests does not authorize the implementation of the algorithm; leave the solver as a stub and ask for clarification if the scope is ambiguous.

Read the manifest, lockfile, toolchain and CLI first. Explain target/cache artifacts and possible dependency fetching before commands; run existing checks only when requested or agreed.

## Correctness diagnostics

For a `dayNN/` crate layout, from the puzzle repository root (adapt the manifest path to a workspace or single crate):

```sh
rustc --version
cargo test --manifest-path dayNN/Cargo.toml
cargo clippy --manifest-path dayNN/Cargo.toml --all-targets -- -D warnings
cargo fmt --manifest-path dayNN/Cargo.toml -- --check
```

Use a current-part test filter if a later-part stub is intentionally red, for example `cargo test --manifest-path dayNN/Cargo.toml part1_sample` in the repository's scaffold. Check that the summary reports `1 passed`: Cargo exits successfully when a misspelled filter matches no tests. The scaffold's unset answers are `None`, so `Some(-1)` is a valid expected answer. Distinguish compiler errors, assertion failures and lint advice. Ask the trainee to explain the first meaningful diagnostic before proposing a local fix. Do not use `cargo fix` or a formatting rewrite by default.

Inspect integer arithmetic and the active profile. Read `Cargo.toml` for `[profile.release] overflow-checks`; release builds disable overflow checks by default, so do not assume debug and release have identical behavior. Suggest a manifest change only with its reasoning; apply it only on explicit request.

## Measurement after green

Load [the shared performance lab](../aoc-performance-lab/SKILL.md). Build separately from runtime timing:

```sh
cargo build --release --manifest-path dayNN/Cargo.toml
```

Inspect Cargo target names and target-directory configuration before invoking the built binary. Avoid including compilation in latency comparisons. Do not compare debug against release as evidence for an algorithmic optimization.

Teach `std::time::Instant` for elapsed solver timing; if the CLI already times itself, check whether parsing/I/O is inside the boundary. A microbenchmark harness needs explicit edit consent; observe results, avoid dead-code elimination and reset mutable state. `std::hint::black_box` can help a benchmark but does not guarantee every compiler transformation is prevented.

Use an existing profiler if available. CPU symbols, profiler permissions and platform support need checking. Criterion, flamegraph tooling and rayon are opt-in, not automatic installations. Do not change machine permissions to obtain a profile. Separate profiling overhead from uninstrumented timing, and state what memory metrics actually measure.

Report exact profile/flags, checks run, output and limits. End with one **Next decision**.

## Sources

[Cargo profiles](https://doc.rust-lang.org/cargo/reference/profiles.html), [cargo test](https://doc.rust-lang.org/cargo/commands/cargo-test.html), [Clippy](https://doc.rust-lang.org/clippy/), [rustfmt](https://github.com/rust-lang/rustfmt), [Instant](https://doc.rust-lang.org/std/time/struct.Instant.html), [black_box](https://doc.rust-lang.org/std/hint/fn.black_box.html).
