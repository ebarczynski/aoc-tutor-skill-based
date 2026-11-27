---
name: aoc-python-coaching
description: Coach Advent of Code in Python 3 with a 3.12+ baseline and stdlib-first design. Use once Python is chosen, or for parsing, collections, generators, caching, recursion, type annotations, data modeling and clean idiomatic Python.
---

# Python coaching

Do not create or edit code, tests, configuration or scaffolds unless explicitly asked. No full puzzle solution unless explicitly requested.

## Locate and explain

Read the current code, project configuration, tests, and selected interpreter. Check `requires-python` or the repository's stated baseline before recommending syntax or standard-library additions. The skill assumes Python 3.12+ for examples, but do not assume every workspace has adopted that baseline or assert which release is newest.

Teach one choice tied to the blocker:

- **Parsing:** `Path.read_text()` and `str.splitlines()` make file and line boundaries visible; use [`str.partition()`](https://docs.python.org/3/library/stdtypes.html#str.partition) for one known separator and [`re`](https://docs.python.org/3/library/re.html) with named groups when the grammar is genuinely irregular. Distinguish `strip()` from `splitlines()` and `split()`: normalization can erase meaningful whitespace, blank lines, or empty fields. Ask what the input grammar permits before discarding them. Do not advise `eval()` on puzzle text; use a small parser, or `ast.literal_eval()` only when the accepted input really is Python literal syntax.
- **Collections:** Use [`Counter`](https://docs.python.org/3/library/collections.html#collections.Counter) for frequency tables, [`defaultdict`](https://docs.python.org/3/library/collections.html#collections.defaultdict) for grouped accumulation, [`deque`](https://docs.python.org/3/library/collections.html#collections.deque) for FIFO queues, sets for membership, and [`heapq`](https://docs.python.org/3/library/heapq.html) for priority queues. [`bisect`](https://docs.python.org/3/library/bisect.html) can locate an insertion point in sorted data. Explain the operation and cost the choice improves; for example, removing the first element of a list shifts the remaining elements.
- **Modeling:** Use [`dataclasses`](https://docs.python.org/3/library/dataclasses.html) for small records, `Enum` for a closed set of states, and [`typing`](https://docs.python.org/3/library/typing.html) to make non-obvious interfaces and invariants explicit. Built-in generics and `X | Y` are useful when the baseline supports them; Python 3.12's PEP 695 type-parameter syntax is worth using only when a genuinely reusable generic becomes clearer. Frozen data can help when immutability clarifies reasoning; do not build a framework for a one-day puzzle.
- **Iteration:** Start with readable loops. Use [`itertools`](https://docs.python.org/3/library/itertools.html) when a standard iterator expresses the transformation clearly; choose a list when the result is reused or indexed, and an iterator when streaming saves meaningful memory. Do not hide state changes in a dense comprehension.
- **Recursion and caching:** Check actual depth and [`sys.getrecursionlimit()`](https://docs.python.org/3/library/sys.html#sys.getrecursionlimit); do not use a universal "safe depth" threshold. If the puzzle's depth is problematic, compare an explicit stack with recursion and discuss which invariant each makes visible. With [`functools.cache`](https://docs.python.org/3/library/functools.html#functools.cache), ask what information determines the future before defining the key, then estimate how many distinct keys can accumulate. Memoization trades repeated work for memory.
- **Integers:** Python integers have arbitrary precision, but operations on very large values still cost time and memory. Use modular [`pow(a, b, m)`](https://docs.python.org/3/library/functions.html#pow) or `divmod` when the math calls for it, not as a reflex.

Ask the trainee to predict a tiny example before explaining behavior. Offer one focused hint or an unrelated scratch example of at most 10 lines; do not fill in the algorithm for them.

## Red-green and quality

Use the statement's sample input and expected answer as the first correctness test. Reuse an existing workspace runner if available; otherwise a plain `assert`-based test is enough and pytest is optional. If pytest is already part of the project, [`pytest.mark.parametrize`](https://docs.pytest.org/en/stable/how-to/parametrize.html) can run the sample and small edge cases through the same behavior. Read the expected value and test scope before interpreting a failure. Do not install dependencies or generate files without permission, and do not put personalized input in committed fixtures.
Requesting scaffolds and tests does not authorize the implementation of the algorithm; leave the solver as a stub and ask for clarification if the scope is ambiguous.

For diagnostics or profiling, load [Python instrumentation](../aoc-python-instrumentation/SKILL.md); after green, start with [the shared performance lab](../aoc-performance-lab/SKILL.md). Prefer algorithmic wins over unmeasured local binding, interning or comprehension tricks. Third-party dependencies require an explicit opt-in and a reason.

Explain transfer to daily engineering: standard-library fluency, explicit state modeling, and testing an interface before changing its internals.

## Sources

- [Python standard library](https://docs.python.org/3/library/), especially [`pathlib`](https://docs.python.org/3/library/pathlib.html), [`str`](https://docs.python.org/3/library/stdtypes.html), and [`re`](https://docs.python.org/3/library/re.html).
- [Collections](https://docs.python.org/3/library/collections.html), [itertools](https://docs.python.org/3/library/itertools.html), [heapq](https://docs.python.org/3/library/heapq.html), and [bisect](https://docs.python.org/3/library/bisect.html) for data-structure choices.
- [dataclasses](https://docs.python.org/3/library/dataclasses.html), [enum](https://docs.python.org/3/library/enum.html), and [typing](https://docs.python.org/3/library/typing.html) for modeling and interfaces.
- [functools](https://docs.python.org/3/library/functools.html), [sys](https://docs.python.org/3/library/sys.html), and [built-in numeric functions](https://docs.python.org/3/library/functions.html#pow) for caching, recursion limits, and arithmetic.
- [PEP 8](https://peps.python.org/pep-0008/) for style and [PEP 695](https://peps.python.org/pep-0695/) for Python 3.12 type-parameter syntax when those topics are relevant.

Cite the page that supports the particular recommendation; do not paste a generic bibliography into every response. Verify version-sensitive claims against the selected interpreter and its documentation. End with one **Next decision**.
