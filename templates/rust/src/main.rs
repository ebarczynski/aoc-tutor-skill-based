//! Day 01 — Advent of Code (edition 2024, std-first).
//!
//! Red-green first: fill SAMPLE_EXPECTED_* in the tests module with the
//! answers printed in the puzzle statement, `cargo test` (red), implement,
//! `cargo test` (green), then time the real input:
//!
//!     cargo run --release -- 1 input.txt

use std::fs;
use std::process::ExitCode;
use std::time::Instant;

/// Parse raw input into your model. Name the type after what it *is*
/// (grid, event, machine state) — not after the text it came from.
/// Vec<&str> is a placeholder; a small enum or struct usually pays off.
fn parse(input: &str) -> Vec<&str> {
    input.lines().collect()
}

fn part1(_model: &[&str]) -> i64 {
    todo!("part1 — only after the sample test is red")
}

fn part2(_model: &[&str]) -> i64 {
    todo!("part2 — it usually reuses part 1's model; think before rewriting")
}

fn main() -> ExitCode {
    let mut args = std::env::args().skip(1);
    let part: u8 = match args.next().and_then(|a| a.parse().ok()) {
        Some(1) => 1,
        Some(2) => 2,
        _ => {
            eprintln!("usage: day01 <1|2> <input-file>");
            return ExitCode::from(2);
        }
    };
    let Some(path) = args.next() else {
        eprintln!("usage: day01 <1|2> <input-file>");
        return ExitCode::from(2);
    };
    let Ok(input) = fs::read_to_string(&path) else {
        eprintln!("cannot read {path}");
        return ExitCode::from(2);
    };
    let model = parse(&input);
    let start = Instant::now();
    let answer = if part == 1 { part1(&model) } else { part2(&model) };
    let ms = start.elapsed().as_secs_f64() * 1000.0;
    println!("part {part}: {answer} ({ms:.1} ms)");
    ExitCode::SUCCESS
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Sentinel: "expected value not filled in yet".
    const UNSET: i64 = -1;
    /// TODO: the answer printed in the puzzle statement for the sample.
    const SAMPLE_EXPECTED_P1: i64 = UNSET;
    /// TODO: the answer printed in the puzzle statement for the sample.
    const SAMPLE_EXPECTED_P2: i64 = UNSET;

    fn sample() -> String {
        fs::read_to_string(concat!(env!("CARGO_MANIFEST_DIR"), "/input_sample.txt"))
            .expect("paste the statement's sample input into input_sample.txt")
    }

    #[test]
    fn part1_sample() {
        assert_ne!(
            SAMPLE_EXPECTED_P1, UNSET,
            "fill SAMPLE_EXPECTED_P1 with the answer from the puzzle statement"
        );
        assert_eq!(part1(&parse(&sample())), SAMPLE_EXPECTED_P1);
    }

    #[test]
    fn part2_sample() {
        assert_ne!(
            SAMPLE_EXPECTED_P2, UNSET,
            "fill SAMPLE_EXPECTED_P2 with the answer from the puzzle statement"
        );
        assert_eq!(part2(&parse(&sample())), SAMPLE_EXPECTED_P2);
    }
}
