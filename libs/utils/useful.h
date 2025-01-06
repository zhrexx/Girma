// ========================================================================================>
// ZHRXXgroup Project 🚀 - ZLib
// File: useful.h
// Author(s): ZHRXXgroup
// Version: 1
// ========================================================================================>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>

bool verbose_mode = false;


// IMPORTANT
int needs_rebuild(const char *source_file, const char *executable, char **argv) {
    struct stat source_stat, exe_stat;

    if (stat(source_file, &source_stat) != 0) {
        fprintf(stderr, "Error: Source file '%s' not found.\n", source_file);
        return 1;
    }

    if (stat(executable, &exe_stat) != 0) {
        fprintf(stderr, "Warning: Executable '%s' not found.\n", executable);
        return 1;
    }

    if (source_stat.st_mtime > exe_stat.st_mtime) {
        if (verbose_mode) {
            printf("Source file '%s' is newer than executable '%s'. Rebuild required.\n", source_file, executable);
        }
        return 1;
    }

    if (verbose_mode) {
        printf("Executable '%s' is up-to-date. Running...\n", executable);
    }

    return 0;
}