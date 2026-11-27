"""Sample tests — the statement's worked example is the first failing test.

Zero-dependency runner:   python3 day01/test_solution.py [1|2]
Or with pytest:           python3 -m pytest -q day01 --import-mode=importlib
(importlib mode avoids same-name module collisions when you collect several
days in one pytest session; select one part with -k part1 or -k part2.)

Starts red on purpose: fill SAMPLE_EXPECTED_* with the answers printed in
the puzzle statement, then implement in solution.py until green.
"""

import sys
from pathlib import Path

from solution import parse, part1, part2

HERE = Path(__file__).parent
# None means "not filled in yet"; every int, including -1, is a valid answer.
SAMPLE_EXPECTED_P1: int | None = None  # TODO: answer printed in the statement
SAMPLE_EXPECTED_P2: int | None = None  # TODO: answer printed in the statement


def _sample() -> str:
    path = HERE / "input_sample.txt"
    if not path.is_file():
        raise AssertionError(
            "input_sample.txt missing — paste the statement's sample input there"
        )
    text = path.read_text()
    if not text.strip():
        raise AssertionError(
            "input_sample.txt is empty — paste the statement's sample input"
        )
    return text


def test_part1_sample() -> None:
    if SAMPLE_EXPECTED_P1 is None:
        raise AssertionError(
            "fill SAMPLE_EXPECTED_P1 with the answer from the puzzle statement, "
            "then implement part1"
        )
    assert part1(parse(_sample())) == SAMPLE_EXPECTED_P1


def test_part2_sample() -> None:
    if SAMPLE_EXPECTED_P2 is None:
        raise AssertionError(
            "fill SAMPLE_EXPECTED_P2 with the answer from the puzzle statement, "
            "then implement part2"
        )
    assert part2(parse(_sample())) == SAMPLE_EXPECTED_P2


def main(argv: list[str]) -> int:
    cases = {"1": test_part1_sample, "2": test_part2_sample}
    if len(argv) > 2 or (len(argv) == 2 and argv[1] not in cases):
        print(f"usage: {argv[0]} [1|2]", file=sys.stderr)
        return 2
    selected = [cases[argv[1]]] if len(argv) == 2 else list(cases.values())
    failures = 0
    for case in selected:
        try:
            case()
            print(f"PASS: {case.__name__}")
        except (AssertionError, NotImplementedError) as exc:
            failures += 1
            print(f"FAIL: {case.__name__}: {exc}")
    if failures == 0:
        print("ALL GREEN — now run the real input: python3 solution.py 1 input.txt")
        return 0
    print(f"{failures} failing — stay red until green")
    return 1


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
