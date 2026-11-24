#ifndef AOC_DAY01_H
#define AOC_DAY01_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    /* TODO: Replace this placeholder with the puzzle's data model. */
    int placeholder;
} day01_model;

bool day01_parse(FILE *input, day01_model *model);
bool day01_part1(const day01_model *model, int64_t *answer);
bool day01_part2(const day01_model *model, int64_t *answer);

#endif
