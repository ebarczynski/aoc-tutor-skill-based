"""Sample tests — the statement's worked example is the first failing test.

Zero-dependency runner:   python3 day01/test_solution.py
Or with pytest:           python3 -m pytest -q day01 --import-mode=importlib
(importlib mode avoids same-name module collisions when you collect several
days in one pytest session.)

Starts red on purpose: fill SAMPLE_EXPECTED_* with the answers printed in
the puzzle statement, then implement in solution.py until green.
"""

from pathlib import Path

import solution
from solution import parse, part1, part2

HERE = Path(__file__).parent
UNSET = -1  # sentinel: "expected value not filled in yet"
SAMPLE_EXPECTED_P1 = UNSET  # TODO: answer printed in the puzzle statement
SAMPLE_EXPECTED_P2 = UNSET  # TODO: answer printed in the puzzle statement


def _sample() -> str:
    text = (HERE / "input_sample.txt").read_text()
    if not text.strip():
        raise AssertionError(
            "input_sample.txt is empty — paste the statement's sample input"
        )
    return text


def test_part1_sample() -> None:
    if SAMPLE_EXPECTED_P1 == UNSET:
        raise AssertionError(
            "fill SAMPLE_EXPECTED_P1 with the answer from the puzzle statement, "
            "then implement part1"
        )
    assert part1(parse(_sample())) == SAMPLE_EXPECTED_P1


def test_part2_sample() -> None:
    if SAMPLE_EXPECTED_P2 == UNSET:
        raise AssertionError(
            "fill SAMPLE_EXPECTED_P2 with the answer from the puzzle statement, "
            "then implement part2"
        )
    assert part2(parse(_sample())) == SAMPLE_EXPECTED_P2


if __name__ == "__main__":
    failures = 0
    for case in (test_part1_sample, test_part2_sample):
        try:
            case()
            print(f"PASS: {case.__name__}")
        except (AssertionError, NotImplementedError) as exc:
            failures += 1
            print(f"FAIL: {case.__name__}: {exc}")
    if failures == 0:
        print("ALL GREEN — now run the real input: python3 solution.py 1 input.txt")
        raise SystemExit(0)
    print(f"{failures} failing — stay red until green")
    raise SystemExit(1)
