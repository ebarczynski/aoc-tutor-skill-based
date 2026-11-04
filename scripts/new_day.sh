#!/usr/bin/env bash
# Scaffold a new AoC day from templates/: ./scripts/new_day.sh <NN> <cpp|python|rust>
# The scaffold starts red on purpose — paste the statement's sample, fill the
# expected answers, watch the test fail, implement. See templates/README.md.
set -euo pipefail

usage() { echo "usage: $0 <NN> <cpp|python|rust>" >&2; exit 2; }

[ $# -eq 2 ] || usage
DAY="$1"
LANG_T="$2"
[[ "$DAY" =~ ^[0-9]{1,2}$ ]] || { echo "day must be 1-2 digits, e.g. 07" >&2; exit 2; }
DAY="$(printf '%02d' "$((10#$DAY))")"   # normalize 7 -> 07
DAY_HUMAN="$((10#$DAY))"                # 07 -> 7 (for "Day 7" style prose)
case "$LANG_T" in cpp|python|rust) ;; *) usage ;; esac

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SRC="$REPO_ROOT/templates/$LANG_T"
DST="$(pwd)/day$DAY"
[ -d "$SRC" ] || { echo "template missing: $SRC" >&2; exit 1; }
[ -e "$DST" ] && { echo "day$DAY already exists" >&2; exit 1; }

mkdir -p "$DST"
cp -R "$SRC/." "$DST/"

# Rename day01 tokens -> dayNN: file names, crate/package names, usage strings,
# and the human-readable "Day 01" prose. Process substitution keeps the loops
# out of pipeline subshells (set -e would otherwise abort mid-scaffold), and
# the identity guard makes DAY=01 a clean no-op.
while IFS= read -r f; do
  new="${f//day01/day$DAY}"
  if [ "$f" != "$new" ]; then mv "$f" "$new"; fi
done < <(find "$DST" -depth -name '*day01*')
while IFS= read -r f; do
  sed -i "s/day01/day$DAY/g; s/Day 01/Day $DAY_HUMAN/g" "$f"
done < <(grep -rl -e 'day01' -e 'Day 01' "$DST")

echo "day$DAY ($LANG_T) scaffolded — it is red on purpose:"
echo "  1. paste the statement's sample into day$DAY/input_sample.txt"
echo "  2. fill the SAMPLE_EXPECTED constants in the test file"
echo "  3. run the test (see templates/README.md) — red, then implement"
