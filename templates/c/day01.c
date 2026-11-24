#include "day01.h"

#include <inttypes.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv)
{
    if (argc != 3 || (strcmp(argv[1], "1") != 0 && strcmp(argv[1], "2") != 0)) {
        fprintf(stderr, "usage: day01 <1|2> <input-file>\n");
        return 2;
    }
    FILE *input = fopen(argv[2], "r");
    if (input == NULL) {
        perror(argv[2]);
        return 2;
    }
    day01_model model;
    const bool parsed = day01_parse(input, &model);
    const int close_status = fclose(input);
    if (!parsed || close_status != 0) {
        fprintf(stderr, "failed to parse or close %s\n", argv[2]);
        return 1;
    }
    const clock_t start = clock();
    if (start == (clock_t)-1) {
        fprintf(stderr, "process CPU clock unavailable\n");
        return 1;
    }
    int64_t answer;
    const bool ok = strcmp(argv[1], "1") == 0
                        ? day01_part1(&model, &answer)
                        : day01_part2(&model, &answer);
    const clock_t end = clock();
    if (!ok) {
        return 1;
    }
    if (end == (clock_t)-1 || end < start) {
        fprintf(stderr, "process CPU clock unavailable or wrapped\n");
        return 1;
    }
    const double ms = ((double)end - (double)start) * 1000.0 / (double)CLOCKS_PER_SEC;
    printf("part %s: %" PRId64 " (%.3f ms CPU time)\n", argv[1], answer, ms);
    return 0;
}
