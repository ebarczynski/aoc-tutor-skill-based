# AoC Coach — Copilot agent set for Advent of Code

A set of GitHub Copilot **custom agents** (`.agent.md`) that coach a team through Advent of Code in **C++23/26**, **Python 3**, and **Rust (edition 2024)** — teaching-first: problem decomposition, mermaid diagrams, algorithm comparison with complexity pros/cons, doc citations. No one-shot solutions; the point is that the prompter learns something.

Agents follow the red-green workflow anchored on AoC's own worked examples (sample input + expected answer = the first failing test), and reference authoritative docs (cppreference, Core Guidelines, docs.python.org, PEPs, Rust Book/std/Edition Guide) instead of reciting from memory.

## The roster

| Agent | Role | Tools |
|---|---|---|
| `aoc-coach` | Entry point: decompose the puzzle, mermaid plan, route to a lane | read, search, edit (notes only), web, todo, agent + handoffs |
| `aoc-algorithms` | Compare ≥2 approaches: time/space complexity, pros/cons, citations | read, search, web, todo + handoffs |
| `aoc-cpp` | C++23/26 lane: ranges, sanitizers, clang-tidy, benchmarks | read, edit, search, execute, web, todo |
| `aoc-python` | Python 3 lane (≥3.12 baseline): stdlib-first, pytest red-green, profiling | read, edit, search, execute, web, todo |
| `aoc-rust` | Rust 2024 lane: ownership, iterators, clippy, cargo red-green | read, edit, search, execute, web, todo |
| `aoc-review` | Post-solve review: correctness evidence, complexity audit, idiom findings | read, search, execute, web — **no edit**, manual-select only |

Supporting material: `.github/copilot-instructions.md` (the teaching contract — applies to every chat in the workspace), `references/` (algorithm playbook, mermaid templates, toolchain cheat sheet), and `templates/` + `scripts/new_day.sh` (day scaffolds).

## Day scaffolds

From your puzzle repo root: `./scripts/new_day.sh <NN> <cpp|python|rust>` creates `dayNN/` from `templates/` — the sample test is wired **red first** (`SAMPLE_EXPECTED_*` sentinels that fail with a "fill the expected answer" message), `part1`/`part2` stubs fail loudly, the CLI times every run, and each lane gets its hygiene tooling (C++: sanitizers + clang-tidy target; Python: zero-dep test runner + pytest option; Rust: edition 2024 + release overflow-checks). Details in `templates/README.md`.

`templates/cpp` builds with **CMake presets** (debug = sanitizers + `ctest --preset sample`, release = timed runs; CMake ≥ 3.25). CI (`.github/workflows/scaffold-e2e.yml`) keeps the templates honest: on every push/PR it scaffolds a scratch day per lane and proves the full contract — red with the sentinel guidance, then green after filling expected values + stubs.

## Install (per puzzle repository)

1. Copy into your AoC solution repo (e.g. `my-aoc-2026/`):
   - `.github/agents/` (all six files)
   - `.github/copilot-instructions.md`
   - `references/`
2. Open the repo in VS Code with GitHub Copilot Chat (recent version required; agents were written against the custom-agent docs as of **2026-11-04**).
3. In the Chat view, pick the agent from the **Agent** dropdown (type `@`/open the picker depending on your harness). Start with `aoc-coach`, paste the puzzle statement.

Also usable user-level (available in every workspace): copy the `.agent.md` files to `~/.copilot/agents/`. Older `.chatmode.md` files are superseded by this format — rename them.

Copilot CLI works too: the same `.agent.md` format is shared; `handoffs` are a VS Code (Local harness) feature and are simply ignored elsewhere.

## Usage patterns

- New puzzle: `aoc-coach` + "Day 4, part 1, here's the statement: …" → decomposition + mermaid → handoff button to your language lane.
- Stuck on approach: `aoc-algorithms` + "n ≈ 10⁶ lines, part 2 will multiply states" → comparison with complexities.
- Language fight: `aoc-cpp` + "my ranges pipeline segfaults with sanitizers on" → sanitizer-first diagnosis.
- Solved it: `aoc-review` (pick manually — it deliberately can't be auto-invoked) → comprehension gate, complexity audit, ≤5 idiom findings.

## The no-spoiler contract

`.github/copilot-instructions.md` defines a 9-rung escalation ladder (restate → concept → diagram → algorithm options → representation → failing test → hint → toy example → outline; full code only on explicit request). Every agent is bound by it, so colleagues can share one setup without fear of answer-dumping.

## House rules

- Personalized AoC inputs are never committed (`.gitignore` covers `input*` patterns). Samples from the public statement are fine.
- Version claims (compilers, Python/Rust point releases) are re-verified by the agents via `web` tools at usage time; anything unverified is labeled an estimate.
- Written against the docs on 2026-11-04: VS Code *Custom agents* + *Custom agent file reference*, GitHub *Custom agents configuration* (`docs.github.com/en/copilot/reference/custom-agents-configuration`). If Copilot changes the format, re-check those three pages first.
