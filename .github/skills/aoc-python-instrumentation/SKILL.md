---
name: aoc-python-instrumentation
description: Teach Python testing and profiling instrumentation for Advent of Code. Use for sample-test execution, interpreter mismatches, cProfile, pstats, timeit, perf_counter or tracemalloc; pair optimization measurements with aoc-performance-lab.
---

# Python evidence, not guesses

Do not edit files, generate scaffolds, apply fixes or install tools without an explicit request. No full puzzle solution unless explicitly requested.

Inspect the selected interpreter, CLI and tests. Use that interpreter consistently; `python3` below is an example command, not a guarantee it matches the editor. Explain artifacts and run checks only when requested or agreed.

## Correctness diagnostics

Find the existing test entry point first. For a `dayNN/` layout with a `test_solution.py` runner, from the puzzle repository root:

```sh
python3 --version
python3 dayNN/test_solution.py      # both parts
python3 dayNN/test_solution.py 1    # current part only
```

A plain runner like that needs no third-party dependency. If pytest is already available:

```sh
python3 -m pytest -q dayNN --import-mode=importlib
```

Check whether the runner executes both parts and whether it has a part selector. The repository's scaffold runner accepts an optional `1` or `2`; with pytest, `-k part1` selects part 1 and pytest reports an error when nothing is collected. In other layouts, call the existing part-1 sample test function directly with the selected interpreter. The scaffold's unset answers are `None`, so `-1` remains a valid expected answer. Do not claim the aggregate suite is green when part 2 is intentionally red. An unfinished part 2 is not evidence that part 1 is wrong. Read the assertion and expected sample answer before changing anything. Syntax-only `py_compile` is not a correctness test; it can create bytecode caches.

## Measurement after green

Load [the shared performance lab](../aoc-performance-lab/SKILL.md). Read the CLI's arguments first. For an agreed dataset and, for example, a `solution.py <part> <input>` CLI, profiling can start with:

```sh
python3 -m cProfile -s cumulative dayNN/solution.py 1 dayNN/input_sample.txt
```

Use a sufficiently representative synthetic or agreed local dataset; a tiny public sample may not reveal the hot path. Explain total versus cumulative time and call counts. cProfile instruments execution, so its timings are diagnostic, not directly comparable to unprofiled latency.

- Use `timeit` for an isolated operation after identifying it as relevant. Keep setup outside the timed body when appropriate, consume iterator work, reset mutable state, and distinguish warm from cold caches. Explain that timeit disables garbage collection by default and decide whether that matches the workload.
- Use `time.perf_counter` for a clearly bounded elapsed-time experiment. If the CLI has a built-in timer, check what it covers; cProfile of the whole CLI includes startup, input and parsing.
- Use `tracemalloc` only when the question is Python allocation growth. It adds overhead and is not the same as process RSS or complete native-allocation accounting. Starting/stopping tracing or adding a harness is a file edit if persisted and needs permission.

Prefer stdlib tools; optional profilers require opt-in. Report measurements or "not measured", never a guessed speedup. Explain one hot-path observation and one **Next decision**.

## Sources

[Profilers](https://docs.python.org/3/library/profile.html), [timeit](https://docs.python.org/3/library/timeit.html), [perf_counter](https://docs.python.org/3/library/time.html#time.perf_counter), [tracemalloc](https://docs.python.org/3/library/tracemalloc.html).
