# AoC Skills Coach

An AI-augmented Advent of Code learning workflow built around **one Copilot
agent and a set of reusable skills**. The coach stays with the trainee in one
conversation and loads only the knowledge needed for the current question.
All coaching stays in that conversation.

The workflow supports **C17 with support-gated C23**, **C++23/26**,
**Python 3**, and **Rust 2024**. Its goal is to help engineers become better
problem solvers—not to produce one-shot answers.

## Learning principles

- **Teach, don't solve.** Start from the trainee's understanding and give one
  manageable next step. Do not provide a complete puzzle solution unless
  explicitly asked.
- **The trainee owns the implementation.** Do not edit code, tests, scaffolds,
  configuration, or scratch files without an explicit request for that
  specific change. Consent is scoped.
- **Sample first.** Use the puzzle's public sample as the red-green anchor for
  each part. Run personalized input only after the current part's sample is
  green, edge cases are checked, and the trainee agrees.
- **Explain the engineering.** Discuss assumptions, invariants, trade-offs,
  complexity, correctness, and how a technique transfers to day-to-day work.
- **Measure, don't guess.** Ground performance advice in actual input sizes,
  profiles, or repeatable measurements. Keep personalized puzzle input private.

## What's included

| Component | Purpose |
|---|---|
| [AoC Skills Coach](.github/agents/aoc-skills-coach.agent.md) | Guides the trainee through the puzzle, routes relevant skills, and keeps the conversation in one voice. |
| [Algorithm design](.github/skills/aoc-algorithm-design/SKILL.md) | Models the problem and teaches algorithm choices such as graph search, dynamic programming, cycle detection, and interval methods. Includes a bundled algorithm playbook. |
| [C coaching](.github/skills/aoc-c-coaching/SKILL.md) | Portable C17/C23 and measured performance: parsing, memory ownership, data layout, compiler behavior, and C-specific safety. |
| [C++ coaching](.github/skills/aoc-cpp-coaching/SKILL.md) | C++23/26 representation, parsing, lifetimes, ownership, containers, and idioms. |
| [Python coaching](.github/skills/aoc-python-coaching/SKILL.md) | Python 3 data modeling, standard-library tools, types, iteration, and caching. |
| [Rust coaching](.github/skills/aoc-rust-coaching/SKILL.md) | Rust 2024 ownership, borrowing, parsing, iterators, and error handling. |
| [Performance lab](.github/skills/aoc-performance-lab/SKILL.md) | Shared hypothesis-driven optimization and benchmark design. |
| [C instrumentation](.github/skills/aoc-c-instrumentation/SKILL.md) | C tests, warnings, sanitizers, compiler reports, CPU timing, and profiling. |
| [C++ instrumentation](.github/skills/aoc-cpp-instrumentation/SKILL.md) | Tests, compiler diagnostics, sanitizers, clang-tidy, timing, and profiling. |
| [Python instrumentation](.github/skills/aoc-python-instrumentation/SKILL.md) | Tests, interpreter checks, cProfile, timeit, and allocation measurements. |
| [Rust instrumentation](.github/skills/aoc-rust-instrumentation/SKILL.md) | Cargo tests, Clippy, formatting, build profiles, timing, and profiling. |
| [Quality review](.github/skills/aoc-quality-review/SKILL.md) | Invited post-solve review of correctness, complexity, design, and idiomatic code. |

Skills extend the coach's knowledge in the same conversation. Load the chosen
language skill first; add algorithm, instrumentation, performance, or review
skills only when the discussion calls for them.

## Quick start

1. Open this repository (or your AoC workspace) in VS Code with Copilot Chat.
2. In **Chat: Open Customizations**, check that **AoC Skills Coach** and the
   eleven skills are discovered. Start a fresh chat if you just installed them.
3. Select **AoC Skills Coach** and tell it the puzzle day and part, language,
   what you have tried, and how much explanation you want.
4. Stay in that conversation as you reason, implement, test, and—if invited—
   review the solution.

For example:

> Day 5 part 1, Rust. Here is the statement and my parser. Please explain
> things in detail, one step at a time. Coach me, but don't edit my files.

The coach should clarify the problem and your current understanding, then load
the relevant skill in the same conversation. It follows the sample-first
red-green loop and waits for you to make the next implementation decision.

## Use in another AoC repository

Copy these into the puzzle workspace:

- [The coach agent](.github/agents/aoc-skills-coach.agent.md) to
  `.github/agents/`.
- The complete [skills directory](.github/skills/) to `.github/skills/`.

Those files are the complete runtime package; no other files from this
repository are required. If the destination workspace has its own Copilot
instructions, the coach follows whichever rule is stricter.

The coach adapts to the workspace's build and test setup. This repository also
includes optional [day scaffolds](templates/README.md) for all four languages and a
[scaffold script](scripts/new_day.sh); neither is required to use the workflow.

## Architecture and evaluation

The [workflow guide](references/skill-workflow.md) explains the teaching
contract, skill routing, sample-first loop, and contains a Mermaid architecture
diagram. Reusable [evaluation scenarios](references/skill-workflow-evals.json)
exercise coaching, edit-consent, measurement, and review boundaries.

Scenario simulations and link checks are useful smoke tests, not proof of
automatic skill selection, permission enforcement, or improved learning
outcomes. Validate discovery and behavior in the Copilot client you plan to
use.

## Privacy

Advent of Code inputs are personalized. Keep real inputs, answers, and any
reports containing them local. Do not upload or commit them. Public puzzle
statement samples may be used in tests.
