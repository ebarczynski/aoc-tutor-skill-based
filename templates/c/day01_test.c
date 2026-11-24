#include "day01.h"

#include <inttypes.h>
#include <string.h>

/* Fill each published answer and set its flag to true, independently. */
static const bool SAMPLE_EXPECTED_P1_SET = false;
static const int64_t SAMPLE_EXPECTED_P1 = 0;
static const bool SAMPLE_EXPECTED_P2_SET = false;
static const int64_t SAMPLE_EXPECTED_P2 = 0;

int main(int argc, char **argv)
{
    if (argc != 2 || (strcmp(argv[1], "1") != 0 && strcmp(argv[1], "2") != 0)) {
        fprintf(stderr, "usage: day01_test <1|2>\n");
        return 2;
    }
    const bool part1 = strcmp(argv[1], "1") == 0;
    if (!(part1 ? SAMPLE_EXPECTED_P1_SET : SAMPLE_EXPECTED_P2_SET)) {
        fprintf(stderr, "fill SAMPLE_EXPECTED_P%s and set SAMPLE_EXPECTED_P%s_SET to true\n",
                argv[1], argv[1]);
        return 1;
    }
    FILE *input = fopen("input_sample.txt", "r");
    if (input == NULL) {
        perror("input_sample.txt");
        return 1;
    }
    day01_model model;
    const bool parsed = day01_parse(input, &model);
    const int close_status = fclose(input);
    if (!parsed || close_status != 0) {
        fprintf(stderr, "failed to parse or close input_sample.txt\n");
        return 1;
    }
    int64_t answer;
    const bool ok = part1 ? day01_part1(&model, &answer) : day01_part2(&model, &answer);
    if (!ok) {
        return 1;
    }
    const int64_t expected = part1 ? SAMPLE_EXPECTED_P1 : SAMPLE_EXPECTED_P2;
    if (answer != expected) {
        fprintf(stderr, "FAIL part %s: expected %" PRId64 ", got %" PRId64 "\n",
                argv[1], expected, answer);
        return 1;
    }
    printf("PASS part %s on sample\n", argv[1]);
    return 0;
}
