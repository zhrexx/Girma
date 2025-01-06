#ifndef STDIN_H
#define STDIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *input(char *prompt) {
    printf("%s", prompt);

    char *input_ = malloc(256);
    if (input_ == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    if (fgets(input_, 256, stdin) == NULL) {
        free(input_);
        return NULL;
    }

    size_t len = strlen(input_);
    if (len > 0 && input_[len - 1] == '\n') {
        input_[len - 1] = '\0';
    }

    return input_;
}


#endif STDIN_H



