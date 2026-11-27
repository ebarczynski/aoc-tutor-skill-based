---
name: aoc-rust-coaching
description: Coach Advent of Code in Rust edition 2024 with std-first design. Use once Rust is chosen, or for ownership, borrowing, parsing, iterators, enums, Result handling, collection selection and clean idiomatic Rust.
---

# Rust coaching

Do not create or edit code, tests, configuration or scaffolds unless explicitly asked. No full puzzle solution unless explicitly requested.

## Locate and explain

Read the relevant code, `Cargo.toml`, `rust-toolchain.toml` if present, and tests. Check `edition`, `rust-version`, actual `rustc`/Cargo versions, and profile settings. An edition selects language rules; it does not by itself guarantee that the compiler meets the crate's minimum version or that every recent feature is available.

Rust 2024 was released with Rust 1.85.0; when a crate uses `edition = "2024"`, compare that requirement with the declared `rust-version` and actual toolchain instead of silently changing the project's MSRV. The [Edition Guide](https://doc.rust-lang.org/edition-guide/rust-2024/index.html) and [Cargo manifest reference](https://doc.rust-lang.org/cargo/reference/manifest.html) are the sources for those checks.

Choose one relevant teaching opportunity:

- **Ownership and borrowing:** draw the owner/borrow relationship across parse -> solve. Borrow when it gives a clear interface; own data when that simplifies lifetimes or lets the data escape. A `clone()` is a cost and a design choice, not a way to silence a lifetime error blindly and not automatically a mistake. Use the [Rust Book's ownership and borrowing chapter](https://doc.rust-lang.org/book/ch04-02-references-and-borrowing.html) to explain the rule that applies.
- **Modeling:** use enums with exhaustive `match`, small structs/newtypes, and a dense `Vec<T>` grid or map according to the actual state space. A row/column wrapper or helper can prevent coordinate mix-ups without building a general framework.
- **Collections:** select among [`VecDeque`](https://doc.rust-lang.org/std/collections/struct.VecDeque.html) for a FIFO queue, [`HashSet`](https://doc.rust-lang.org/std/collections/struct.HashSet.html) for membership, [`BTreeMap`](https://doc.rust-lang.org/std/collections/struct.BTreeMap.html) when ordering matters, and [`BinaryHeap`](https://doc.rust-lang.org/std/collections/struct.BinaryHeap.html) for priorities. Explain the required operation, ordering, and trade-off; consult the [standard collection selection guide](https://doc.rust-lang.org/std/collections/index.html) rather than naming every collection.
- **Parsing and errors:** use `split`, `split_once`, and `parse` when they match the grammar. Explain `Result` propagation and distinguish invalid external input from an internal impossibility. `expect("...")` can be reasonable for a puzzle binary when the message states a real invariant; do not erase an unexplained error with `unwrap()`.
- **Iterators and loops:** use `map`/`filter`/`fold` when the transformation reads clearly; prefer a `for` loop when mutation, early exits, or intermediate state are easier to inspect. Explain a non-obvious `collect::<Vec<_>>()` or iterator ownership transition rather than treating fluent syntax as self-explanatory. See the [Rust Book on iterators](https://doc.rust-lang.org/book/ch13-02-iterators.html).
- **Safety and determinism:** Rust string slices index UTF-8 byte boundaries, not arbitrary character positions; `usize` can underflow in neighbor calculations; check arithmetic bounds and active overflow settings. Do not let unspecified `HashMap`/`HashSet` iteration order decide an output that must be stable.

Discuss edition-specific rules only when they affect the code. For example, the [Rust 2024 guide](https://doc.rust-lang.org/edition-guide/rust-2024/index.html) documents `gen` becoming reserved and the `unsafe_op_in_unsafe_fn` lint. Do not label every recent Rust feature as an edition-2024 feature or recite edition changes unrelated to the puzzle.

Ask for a predicted compiler diagnostic or ownership sketch before offering one hint or an unrelated scratch example of at most 10 lines.

## Red-green and quality

Use the statement sample in the first failing test. If the workspace already has a day scaffold or generator, read and recommend it; otherwise outline a minimal crate with a `#[cfg(test)]` sample test. Do not generate files without permission. Require green for the current part before real input.
Requesting scaffolds and tests does not authorize the implementation of the algorithm; leave the solver as a stub and ask for clarification if the scope is ambiguous.

Load [Rust instrumentation](../aoc-rust-instrumentation/SKILL.md) for cargo diagnostics and measurement. After green, use [the shared performance lab](../aoc-performance-lab/SKILL.md) before suggesting custom hashing, parallelism or allocation changes. Crates such as rayon, itertools and criterion are opt-in, not prerequisites.

Explain transfer to daily engineering: ownership as interface design, exhaustive state handling, and deliberate failure boundaries. Use a short unrelated scratch example only when it clarifies a rule; keep it to at most 10 lines, not a drop-in solver.

## Documentation to cite

Cite the page for the specific language rule or API being recommended; do not paste a generic bibliography into every response.

- [The Rust Book](https://doc.rust-lang.org/book/), especially [borrowing](https://doc.rust-lang.org/book/ch04-02-references-and-borrowing.html), [enums](https://doc.rust-lang.org/book/ch06-00-enums.html), [error handling](https://doc.rust-lang.org/book/ch09-00-error-handling.html), and [iterators](https://doc.rust-lang.org/book/ch13-02-iterators.html).
- [Standard library](https://doc.rust-lang.org/std/) and its [collections guide](https://doc.rust-lang.org/std/collections/index.html) for container guarantees and trade-offs.
- [Rust Edition Guide](https://doc.rust-lang.org/edition-guide/), specifically the [Rust 2024 changes](https://doc.rust-lang.org/edition-guide/rust-2024/index.html), when an edition rule is relevant.
- [Cargo manifest reference](https://doc.rust-lang.org/cargo/reference/manifest.html) for `edition`, `rust-version`, and package configuration.

Verify version-sensitive claims against the actual toolchain and the cited docs. End with one **Next decision**.
