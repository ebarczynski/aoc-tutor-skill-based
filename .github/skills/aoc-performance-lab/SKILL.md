---
name: aoc-performance-lab
description: Teach evidence-based optimization and shared benchmark design for Advent of Code in any language. Use for slow solutions, complexity budgets, profiling hypotheses, before/after experiments, memory trade-offs or interpreting benchmark results.
---

# One measured improvement

Do not edit files without an explicit request. "Make it faster" requests a coached experiment, not an automatic rewrite. No full puzzle solution unless explicitly requested.

## Shared experimental method

1. **Correctness gate:** check the current part's sample and relevant edge cases. If red, return to correctness; diagnostic profiling may explain nontermination, but do not optimize incorrect output.
2. **Hypothesis:** invite the trainee to predict the bottleneck and its cause. Re-derive time/space from the code with actual input dimensions. Distinguish algorithm growth, allocations/copies, I/O, parsing and output.
3. **Baseline:** agree on the metric (latency, throughput or peak memory), dataset size/shape and measurement boundary. Preserve the existing implementation for comparison without changing files unless requested.
4. **Instrument:** load only the matching [C++](../aoc-cpp-instrumentation/SKILL.md), [Python](../aoc-python-instrumentation/SKILL.md) or [Rust](../aoc-rust-instrumentation/SKILL.md) skill. Inspect a profile before guessing at a hot line.
5. **Experiment:** explain one change and its expected effect, then let the trainee implement it. Prefer reducing work/state growth before tuning constants. New tools, dependencies, parallelism and benchmark harness edits require explicit agreement.
6. **Compare:** same input, flags, interpreter/toolchain, hardware and timing boundary; separate build time from runtime. Warm up as appropriate, repeat runs, reset mutable input/cache state deliberately, consume results and verify output so dead-code elimination or cache reuse does not fake a win.
7. **Interpret:** report repetitions, median and spread (range or IQR), not a single lucky run. Alternate baseline/candidate order when drift matters. Identify timer resolution, background load and profiling overhead. Compute speedup as baseline/candidate only for comparable measurements.
8. **Revalidate:** sample and edge cases must still pass; use a tiny oracle or invariant to test the transformation. Discuss memory/readability trade-offs and whether to keep the change.

Do not claim universal runtime cutoffs, "fast enough", or a speedup without measurements or a complexity argument at the actual size. If evidence is missing, say **unknown** and propose the smallest useful measurement. Do not publish personalized inputs or profiles that expose their contents.

## Teaching output

Explain the hypothesis, one observation, what it implies and the next experiment. For completed measurements, use:

| Variant | Input dimensions | Build/runtime + timing boundary | Repetitions | Median + spread | Peak memory | Correctness |
|---|---|---|---|---|---|---|
| Baseline / candidate | actual or synthetic | exact setup | measured count | measured units | measured or not measured | exact checks |

Never populate the table with invented results. Explain how the lesson transfers to service latency, batch processing, cache design or allocation budgets. End with one **Next decision**, not a list of ten speculative optimizations.

## Sources

Use the relevant language instrumentation docs and [Google Benchmark's measurement guidance](https://google.github.io/benchmark/user_guide.html) for warm-up, repetitions and measurement pitfalls; adopting that library is optional.
