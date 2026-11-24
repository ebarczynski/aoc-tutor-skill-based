# Algorithm playbook for Advent of Code

Puzzle taxonomy → candidate algorithms, complexity in terms of the *actual* input size, pros/cons, and reuse potential for part 2. Use it as a taxonomy for discussion; the trainee still chooses. Rules of thumb are not measured guarantees.

## Complexity sanity budget

| Input scale | Comfortable | Uncomfortable | Rules of thumb |
|---|---|---|---|
| n ≤ 10³ | anything linear-ish or O(n²) | — | model clarity > cleverness |
| n ≤ 10⁵ | O(n log n) | O(n²) | Python constants start to hurt |
| n ≤ 10⁶ | O(n)–O(n log n) | O(n²) anywhere | data layout matters; measure |
| n ≥ 10⁹ / "simulate forever" | closed form, cycle detection, memo over *states* | anything per-step | find the cycle or the formula |

## Puzzle families → candidate approaches

### Grid / maze navigation
- **BFS** — O(V+E) time, O(V) space. Pros: shortest path on unweighted graphs, simple queue. Cons: memory grows with explored set; wrong for weighted edges. Reuse for part 2: often becomes multi-source BFS or a state-augmented search.
- **Dijkstra** — O(E log V) with a heap. Pros: weighted edges, still optimal. Cons: heap churn; overkill when all weights are 1.
- **A\*** — Dijkstra + admissible heuristic. Pros: dramatic pruning when a good heuristic exists (Manhattan distance on grids). Cons: heuristic must be admissible or answers are wrong; more code.
- **Flood fill** — O(cells). Pros: trivial. Cons: connected-components semantics only.
- Track visited as a set of `(row, col)` — or `(row, col, extra_state)` when the puzzle adds keys/parity/facing; that state augmentation is usually *the* part-2 twist.

### Simulation ("run the machine until X")
- **Direct simulation** — O(steps × cost-per-step). Pros: transparent, debuggable, matches the narrative. Cons: step counts in AoC can explode (10¹²+); always ask "how many steps?" before committing.
- **Cycle detection** — store state fingerprints (hash) in a dict, or Floyd's tortoise-and-hare for O(1) memory. Pros: turns "simulate 10¹² steps" into arithmetic on the cycle. Cons: state must be fully captured; a missed field silently corrupts results.
- **State machine via enum + transition function** — pros: exhaustive match/table makes illegal states unrepresentable; cons: boilerplate.

### Counting / combinatorics
- **DP / memoization** — O(states × transition). Define the state *precisely* (what suffices to predict the future?); pros: kills exponential blowups; cons: state design is the hard part, wrong state = wrong answers that still run fast.
- **Closed form / arithmetic series** — O(1). Pros: nothing beats it on 10¹² inputs (triangular numbers, CRT, geometric growth). Cons: derivation risk; verify against small cases first.
- **Chinese Remainder Theorem** — for "the first time all cycles align". Pros: exact. Cons: the basic form needs pairwise coprime moduli; with shared factors, residues must agree modulo each gcd (generalized CRT). Implement once, test twice.
- **Inclusion–exclusion / counting with overcounting correction** — pros: handles "how many X satisfy" on huge spaces; cons: easy to miscount overlaps; test on the sample.

### Intervals / events
- **Sweep line** (sort events, walk) — O(n log n). Pros: natural fit for overlaps, coverage, "at what time". Cons: event tie-breaking is where bugs live.
- **Interval merge** — O(n log n) for the sort. Simple; good for calendar-style puzzles.

### Parsing-heavy / expression puzzles
- **Recursive descent parser** — pros: full control, handles precedence cleanly; cons: Python recursion limits, more code than a regex hack.
- **Shunting-yard / two-stack evaluator** — pros: linear, precedence via stack; cons: subtle operator handling.
- Note: AoC part 2 sometimes *changes operator precedence* — a reason to have a real parser, not `eval`.

### String / sequence
- **Sliding window (two pointers)** — O(n). Pros: linear on "longest/shortest substring satisfying". Cons: window invariant must be monotonic.
- **Memo over positions** (word-break style) — O(n × candidates) with a set.

### Sets / ranges of numbers ("how many numbers in [a,b]…")
- **Digit DP** — O(digits × states). Pros: exact counting over astronomically large ranges. Cons: fiddly bounds; verify with brute force on small ranges.
- **Bitsets** — represent reachable sets as packed bits. Python integers can encode a set directly; C can use an array of `uint64_t` words, C++ a `std::bitset` or word array, and Rust a word array. Operations over a word array take time proportional to the number of words; account for allocation, width and any unused final bits. Pros: compact storage and word-at-a-time operations. Cons: less transparent invariants and tricky shifts.

## Choosing: tie-breakers, in order

1. Survives the likely part-2 mutation (state-augmented search and DP generalizing brute force is the common winner).
2. The trainee can hold its state in their head by mid-December-fatigue.
3. Fewer moving parts (queue vs heap vs priority update).
4. Measured runtime — never assumed runtime.

## Anti-patterns

- Optimizing before the sample test is green.
- Simulating 10¹² steps because the loop "should finish eventually".
- Assuming input is rectangular/positive/single-line without checking the sample *and* the real input's shape.
- Writing a part-2-only rewrite when part 1's model could be parameterized — but equally, contorting part 1 into premature generality. Ask: which transformation is smaller?
