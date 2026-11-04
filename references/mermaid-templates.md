# Mermaid templates for puzzle decomposition

Ready-made shapes for the coaches. Rendering: VS Code Copilot Chat renders mermaid blocks; if not, paste into mermaid.live.

## 1. Data-flow decomposition (default shape)

Use for almost every puzzle: parse → model → solve → report. Part 2 usually branches at "model".

```mermaid
flowchart LR
    A[Raw input\nlines] --> B[Parse\nregex / from_chars / split]
    B --> C[Model\nVec&lt;Record&gt; / grid]
    C --> D{Part 1\nsolve}
    C --> E{Part 2\nsolve}
    D --> F[Answer 1]
    E --> G[Answer 2]
```

## 2. Grid as graph (BFS/DFS/Dijkstra)

Use for maze/path puzzles; make the state tuple explicit — the part-2 twist usually lives in `extra`.

```mermaid
flowchart TD
    S["start (r0,c0)"] --> N1["(r,c)\nfacing=up"]
    S --> N2["(r,c)\nfacing=right"]
    N1 --> V{"visited\n(r,c,extra)?"}
    V -- no --> ENQ["enqueue neighbours\nrespecting walls/cost"]
    V -- yes --> SKIP["skip"]
    ENQ --> Q[Priority queue / FIFO]
    Q --> GOAL{"goal?"}
    GOAL -- yes --> ANS["distance / path"]
```

## 3. State machine (simulation puzzles)

Use when the puzzle describes a machine, crabs, lanternfish, intcode… Enum states make illegal states unrepresentable.

```mermaid
stateDiagram-v2
    [*] --> Parsing
    Parsing --> Running: model built
    Running --> Running: step()
    Running --> CycleFound: fingerprint repeats
    CycleFound --> FastForward: jump k*cycle_len
    FastForward --> Running
    Running --> Done: termination condition
    Done --> [*]
```

## 4. Algorithm decision flow

Use when comparing approaches with the trainee (pairs with aoc-algorithms output).

```mermaid
flowchart TD
    Q{Input size?} -- "&le;10^4" --> BRUTE[Brute force\nkeep it simple]
    Q -- "&le;10^6" --> SORTED[Sort / heap / sweep\nO(n log n)]
    Q -- "&ge;10^9" --> MATH{Structure?}
    MATH -- "repeats" --> CYCLE[Cycle detection]
    MATH -- "counting" --> DP[DP / digit DP / CRT]
    MATH -- "closed form" --> FORM[Arithmetic series]
```

## 5. Sequence view of the red-green loop

Use when the trainee keeps skipping the sample test.

```mermaid
sequenceDiagram
    participant T as Trainee
    participant P as Program
    T->>P: run on sample input
    P-->>T: FAIL (red) - expected N, got M
    Note over T: one observation, one change
    T->>P: run again
    P-->>T: PASS (green)
    T->>P: run on real input
    P-->>T: answer + measured runtime
```
