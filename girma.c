#include <stdio.h>
#include <string.h>
#include "girma.h"
#include "libs/collections/vector.h"
#include "libs/utils/logger.h"

int main(int argc, char **argv) {
    Vector args = parse_pargs(argc, argv);

    if (vector_contains(&args, "--help")) {
        printf("| Girma Help |\n");
        printf("|> Modes:    |\n");
        printf("|>> translate\n");
        printf("|>> compile\n");
        vector_free(&args);
        return 0;
    }
    if (vector_len(&args) <= 2) {
        logger_log(LOG_INFO, "Usage: <binary> <mode> <input>");
        vector_free(&args);
        return 1;
    }
    char *mode = vector_get_str(&args, 1);
    char *input = vector_get_str(&args, 2);
    if (strcmp(mode, "translate") == 0) {
        char output[1024];
        snprintf(output, sizeof(output), "%s.out", input);
        translate(input, output);
    } else if (strcmp(mode, "compile") == 0) {
        logger_log(LOG_ERROR, "Not implemented yet!");
        logger_log(LOG_ERROR, "Please use clang/gcc <translated_girma_file.c> -o <output>");
    }
    else {
        printf("Unknown mode: %s\n", mode);
    }

    vector_free(&args);
    return 0;
}

