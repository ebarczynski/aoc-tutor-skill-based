"""Day 01 — Advent of Code (Python 3.12+, stdlib-first).

Red-green: fill SAMPLE_EXPECTED_* in test_solution.py with the answers
printed in the puzzle statement, run the test (red), implement, run again
(green). Only then run the real input — the CLI times every run:

    python3 day01/solution.py 1 day01/input.txt
"""

from __future__ import annotations

import sys
import time
from pathlib import Path


def parse(text: str) -> list[str]:
    """Raw input text -> your model. Rename the return type once you know
    its shape (dataclasses for records, enums for states); AoC rewards a
    model that makes part 2 a transformation instead of a rewrite."""
    return text.splitlines()


def part1(model: list[str]) -> int:
    """TODO: implement — but only after the sample test is red."""
    raise NotImplementedError("part1 — sample test first")


def part2(model: list[str]) -> int:
    """TODO: it usually reuses part 1's model; think before rewriting."""
    raise NotImplementedError("part2 — sample test first")


def main(argv: list[str]) -> int:
    if len(argv) != 3 or argv[1] not in {"1", "2"}:
        print(f"usage: {argv[0]} <1|2> <input-file>", file=sys.stderr)
        return 2
    if not Path(argv[2]).is_file():
        print(f"cannot read {argv[2]}", file=sys.stderr)
        return 2
    model = parse(Path(argv[2]).read_text())
    start = time.perf_counter()
    answer = part1(model) if argv[1] == "1" else part2(model)
    ms = (time.perf_counter() - start) * 1000
    print(f"part {argv[1]}: {answer} ({ms:.1f} ms)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
