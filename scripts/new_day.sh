#!/usr/bin/env bash
# Scaffold a new AoC day from templates/: ./scripts/new_day.sh <NN> <c|cpp|python|rust>
# The scaffold starts red on purpose — paste the statement's sample, fill the
# expected answers, watch the test fail, implement. See templates/README.md.
set -euo pipefail

usage() { echo "usage: $0 <NN> <c|cpp|python|rust>" >&2; exit 2; }

[ $# -eq 2 ] || usage
DAY="$1"
LANG_T="$2"
[[ "$DAY" =~ ^[0-9]{1,2}$ ]] || { echo "day must be 1-2 digits, e.g. 07" >&2; exit 2; }
DAY="$(printf '%02d' "$((10#$DAY))")"   # normalize 7 -> 07
DAY_HUMAN="$((10#$DAY))"                # 07 -> 7 (for "Day 7" style prose)
case "$LANG_T" in c|cpp|python|rust) ;; *) usage ;; esac

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SRC="$REPO_ROOT/templates/$LANG_T"
DST="$(pwd)/day$DAY"
[ -d "$SRC" ] || { echo "template missing: $SRC" >&2; exit 1; }
[ -e "$DST" ] && { echo "day$DAY already exists" >&2; exit 1; }

mkdir -p "$DST"
cp -R "$SRC/." "$DST/"
rm -rf "$DST/build"

# Rename day01 tokens -> dayNN: file names, crate/package names, usage strings,
# and the human-readable "Day 01" prose. Process substitution keeps the loops
# out of pipeline subshells (set -e would otherwise abort mid-scaffold), and
# the identity guard makes DAY=01 a clean no-op.
while IFS= read -r f; do
  new="${f//day01/day$DAY}"
  if [ "$f" != "$new" ]; then mv "$f" "$new"; fi
done < <(find "$DST" -depth -name '*day01*')
while IFS= read -r f; do
  LC_ALL=C sed -i.bak -e "s/day01/day$DAY/g" -e "s/Day 01/Day $DAY_HUMAN/g" "$f"
  rm -f "$f.bak"
done < <(find "$DST" -type f -not -path '*/build/*')

echo "day$DAY ($LANG_T) scaffolded — it is red on purpose:"
echo "  1. paste the statement's sample into day$DAY/input_sample.txt"
if [ "$LANG_T" = c ]; then
  echo "  2. fill the SAMPLE_EXPECTED value and set its _SET flag to true"
else
  echo "  2. fill the SAMPLE_EXPECTED constants in the test file"
fi
echo "  3. run the test (see templates/README.md) — red, then implement"
