# Model selection & token economics

These agents are written for **low-cost models** and pin them deliberately — model choice is part of the example this repo sets. Authored against `haiku 5.5` and `luna 6`; **rename to the exact model IDs your VS Code model picker offers** if they differ. The `model` field accepts a prioritized array — the first available model runs — so the same file works across machines with slightly different catalogs.

## Per-agent pinning

Every agent carries `model: ['haiku 5.5', 'luna 6']` (preferred order, fallback second). We deliberately did **not** guess which of the two reasons better: if you know, put your stronger cheap model first in exactly two places — `AoC Algorithms` (complexity trade-offs are the reasoning-heaviest role) and `AoC Review` (the comprehension gate must catch hand-waving). Mechanical lanes (build/test/parse idioms) are safe on either.

Optional, Copilot harness only: `model-policy: preferred` in frontmatter expresses "prefer this list, don't hard-require it". Not forwarded to converted plugin agents — don't rely on `required`.

## Seeing token consumption

- **`chat.subagents.showCreditUsage: true`** — required setting; credit usage is hidden by default. With it on, every subagent response pill, hover, and screen-reader label shows AI credit usage.
- **Agents window**: the subagent pill shows model, elapsed time, and active tool call; open the subagent chat to inspect its full transcript (read-only, persists across reloads).
- **Delegation ledger**: the coach ends every delegating response with one line per subagent invocation (who, what, outcome). Combined with the pill, that gives per-step cost attribution.
- Each delegation costs roughly **brief + result duplicated in two contexts** plus the subagent's own file reads (ESTIMATE — measure with the setting above; do not trust vibes).

## Pros and cons of the subagent design (as implemented here)

Pros:

- Context isolation — long sanitizer logs and build output live in the subagent chat, never bloat the coach conversation.
- Per-agent contracts — the no-spoiler ladder and tool restrictions are enforced per lane, not per chat.
- Cost control per role — upgrade one agent via its `model` array without touching the rest; cheap models suffice for mechanical lanes.
- Parallel-capable — independent questions can go to independent subagents (the coach protocol still caps parallel briefs for small models).

Cons:

- Stateless one-shot invocations — no follow-up questions to a running subagent; every brief must be self-contained, and brief + result count against both contexts.
- Small models mis-delegate — hence the coach's hard rules: one lane subagent per turn, no solution code in briefs, inline fallback when delegation fails.
- Cost-tier guard — a subagent model above the main model's cost tier refuses to run and reports available models (documented VS Code behavior). Keep coach and lanes in the same tier; that is why everything pins the same pair.
- No nested subagents by default (`chat.subagents.allowInvocationsFromSubagents`, depth ≤ 5 if enabled) — the coach is the only orchestrator, by design.

## When NOT to delegate

Per the VS Code guidance: quick lookup or small edit → direct request, no delegation overhead. In this repo: restate, mermaid decomposition, algorithm sketches, representation advice — the ladder's thinking rungs — are coach-inline work. Delegate diagnostics, idiom questions, and reviews; keep teaching decisions in the main chat.
