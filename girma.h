#ifndef GIRMA_H
#define GIRMA_H

#include "libs/collections/vector.h"
#include "libs/core/str.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

int command(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char command[256];
    vsnprintf(command, sizeof(command), fmt, args);
    va_end(args);
    return system(command);
}

int directory_contains(const char *path, const char *filename) {
    DIR *dir = opendir(path);
    struct dirent *entry;

    if (dir == NULL) {
        perror("opendir");
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, filename) == 0) {
            closedir(dir);
            return 1;
        }
    }

    closedir(dir);
    return 0;
}

void download_file(char *url, char *output) {
    command("curl %s -o '%s'", url, output);
}

typedef struct {
    char *std_lib;
    char *c_lib;
} Module;


Module modules[] = {
    {"std::io", "<stdio.h>"},
    {"std::string", "<string.h>"},
    {"std::assert", "<assert.h>"},
    {"std::lib", "<stdlib.h>"},
    {"std::time", "<time.h>"},
    {"std::locale", "<locale.h>"},
    {"std::errno", "<errno.h>"},
    {"std::arg", "<stdarg.h>"},
    {"std::limits", "<limits.h>"},
    {"std::threads", "<threads.h>"},
    {"std::atomic", "<stdatomic.h>"},
    {"std::complex", "<complex.h>"},
    {"std::bool", "<stdbool.h>"},
    {"std::int", "<stdint.h>"},
    {"std::ctypes", "<ctype.h>"},
    {"std::math", "<math.h>"},
    {"linux::unistd", "<unistd.h>"},
};

typedef struct {
    char *girma_preprocessor;
    char *c_preprocessor;
} Preprocessor;

Preprocessor preprocessor[] = {
    {"OS(linux)", "defined __linux__"},
    {"OS(windows)", "defined _WIN32"},
    {"COMPILER(gcc)", "defined __GNUC__"},
    {"COMPILER(clang)", "defined __clang__"},
};

int translate(char *input, char *output) {
    FILE *input_file = fopen(input, "r");
    FILE *output_file = fopen(output, "w");

    int line_count = 0;

    if (input_file == NULL || output_file == NULL) {
        return 1;
    }

    char line[2048];
    while (fgets(line, sizeof(line), input_file)) {
        line_count++;

        if (contains(line, "#use")) {
            char *m_line = replace(line, "#use", "#include");

            for (int i = 0; i < sizeof(modules) / sizeof(Module); i++) {
                if (contains(m_line, modules[i].std_lib)) {
                    m_line = replace(m_line, modules[i].std_lib, modules[i].c_lib);
                }
            }

            m_line = replace(m_line, ";", "");
            strcpy(line, m_line);
            fprintf(output_file, "%s", line);
        } else if (contains(line, "#macro")) {
            char *m_line = replace(line, "#macro", "#define");
            strcpy(line, m_line);
            fprintf(output_file, "%s", line);
        } else if (contains(line, "$if")) {
            char *m_line = replace(line, "$if", "#if");
            for (int i = 0; i < sizeof(preprocessor) / sizeof(Preprocessor); i++) {
                if (contains(m_line, preprocessor[i].girma_preprocessor)) {
                    m_line = replace(m_line, preprocessor[i].girma_preprocessor, preprocessor[i].c_preprocessor);
                }
            }

            strcpy(line, m_line);
            fprintf(output_file, "%s", line);
        }
        else {
            fprintf(output_file, "%s", line);
        }


    }

}


#endif // GIRMA_H



