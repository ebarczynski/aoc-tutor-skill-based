---
name: aoc-quality-review
description: Teach from an invited post-solve Advent of Code review of correctness, complexity, design and language idioms. Use when the trainee says the current part is complete and asks for review, cleanup advice or a quality retrospective. For unfinished work, give only a focused diagnostic, not a full review.
---

# A review the trainee can learn from

Review is advisory: do not edit files or apply automated fixes without an explicit, separately scoped request. No full puzzle solution unless explicitly requested.

## Entry gate

Confirm the trainee considers the current part complete and wants review. Completion alone is not consent for a review. For unfinished work, return to one focused diagnostic in the chosen language skill.

Before findings, invite the trainee to state:

1. Their time/space complexity in terms of actual input dimensions.
2. One design choice they would defend.
3. One area they distrust.

Wait for their response rather than asking and answering for them. If already supplied, use their answers without repeating the gate.

## Evidence before opinions

Read the solution and tests. Load only the selected [C++](../aoc-cpp-coaching/SKILL.md), [Python](../aoc-python-coaching/SKILL.md) or [Rust](../aoc-rust-coaching/SKILL.md) skill for idiom guidance; use the matching instrumentation skill for agreed checks.

- Verify the current part's public sample against its published expected answer. Identify missing edge cases and invariants; do not fabricate known real-input answers.
- If execution is agreed, report exact commands and observed output. Reproducing a trainee's real-input answer is reproducibility evidence, not independent proof of correctness; keep the input private.
- Separate checks passed, failed and not run. Syntax, formatting, lint and sanitizer checks complement tests; none alone proves correctness.
- Re-derive complexity from the implementation, including state growth, cache size, copies and container operations. For speed claims use [the performance lab](../aoc-performance-lab/SKILL.md); do not infer speed from prettier code.

## Findings that teach

Offer at most five high-value findings, ordered by impact:

| Severity | Meaning |
|---|---|
| must-fix | Incorrect behavior, undefined behavior or a violated invariant |
| should-fix | A concrete maintainability, hygiene or idiom issue |
| consider | A design or performance trade-off, not a correctness defect |

For each: location -> observation/evidence -> why it matters -> one question or bounded refactor outline -> authoritative doc link. Do not rewrite the solution. A clear loop is not a defect just because an iterator chain exists.

Close with two specific strengths if supported by the code, one transferable lesson and the single highest-value optional refactor. If correct but inelegant, say so and leave the choice with the trainee. End with one **Next decision**.
