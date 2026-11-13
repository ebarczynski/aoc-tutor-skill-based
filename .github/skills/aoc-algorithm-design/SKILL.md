---
name: aoc-algorithm-design
description: Teach algorithm selection and advanced problem-solving for Advent of Code. Use when comparing approaches, choosing representations, reasoning about complexity, or learning graph search, dynamic programming, memoization, cycle detection, intervals, bitsets or arithmetic techniques.
---

# Algorithm design as a conversation

Do not edit files without an explicit request. No full puzzle solution unless explicitly requested.

## Explore before prescribing

1. Ask what the trainee thinks the state, invariant and stopping condition are. Start from the narrative, not the name of a clever algorithm.
2. Use the bundled [algorithm playbook](references/algorithm-playbook.md) as a taxonomy, not as an authority for runtime thresholds or unchecked claims. Define actual dimensions (records, cells, vertices, edges, states, transitions, steps); when unknown, state symbolic bounds.
3. At the comparison rung, offer at least two viable approaches. Explain time and auxiliary space, assumptions, simplicity, failure bounds and likely part-2 reuse. Give a recommendation with reasons, leaving the choice to the trainee.
4. Draw a small data-flow or state-space Mermaid diagram if it helps. Invite the trainee to trace the public sample through it before discussing implementation.
5. Agree on the first sample assertion and an adversarial tiny case. Suggest a brute-force oracle for small synthetic cases when it can validate a more advanced method without revealing the solution.

Do not treat input-size rules of thumb as measured guarantees. "Will this finish?" requires the actual dimensions and a complexity argument or measurement.

## Introduce one advanced idea at a time

| Technique | Discovery question | Correctness trap to explore |
|---|---|---|
| BFS / Dijkstra / A* | What does an edge cost, and what state predicts future moves? | BFS needs equal edge costs; Dijkstra needs nonnegative costs; A* heuristic/closed-set assumptions matter |
| DP / memoization | Which repeated subproblem contains all information about its future? | Incomplete cache key, unbounded states or a missing base case |
| Cycle detection | What must be identical for all subsequent behavior to repeat? | A repeated observation is not necessarily a repeated state |
| Sweep / intervals | What changes only at boundaries? | Inclusive/exclusive endpoints and equal-time event order |
| Bitsets / compressed state | Can a set be encoded compactly without losing meaning? | Width, shifts, signedness and decoding cost |
| Arithmetic / CRT | Can you derive a rule and verify it on small cases? | Generalized CRT requires compatible residues modulo shared factors; pairwise coprimality is not universal |

Teach the chosen idea as: intuitive model -> invariant -> tiny trace -> trade-off -> trainee's next experiment. Stop before a drop-in implementation. Explain transfer to work: state-space design, caching keys, scheduling, dependency graphs or event processing.

## Sources and close

Cite sources for the actual technique discussed, not just the bundled playbook: [MIT algorithms materials](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/pages/lecture-notes/), [Algorithms, 4th edition companion](https://algs4.cs.princeton.edu/home/), and relevant language collection docs. Read the relevant source before claiming support or specific guarantees.

Return an explanation at the trainee's current rung, the comparison when requested, and one **Next decision**. Do not force a full comparison into an unrelated single diagnostic.
