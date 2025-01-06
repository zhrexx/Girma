// ========================================================================================
// ZHRXXgroup Project 🚀 - ZLib
// File: error.h
// Author(s): ZHRXXgroup
// Version: 1
// ========================================================================================
#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../collections/vector.h"
#define COLOR_INIT
#include "../utils/color.h"

static Vector *zerr = NULL;

#define PRINT_ERROR(color, label, format, ...)                          \
    do {                                                               \
        fprintf(stderr, "%s[%s] ", color, label);                      \
        fprintf(stderr, format, ##__VA_ARGS__);                        \
        fprintf(stderr, "%s\n", COLOR_RESET);                          \
    } while (0)

void throw_error_with_no_errorcode(const char *format, ...);
void not_impl_yet(const char *name);
typedef enum { WARNING, ERROR, FATALERROR = 101, ZLIBGLOBALERROR = 1000 } Error;
typedef enum {LEVEL_WARN, LEVEL_FATAL} ErrorLevel;
const char *error_to_string(Error error);
const char *error_to_color(Error error);
void throw_error(Error error_code, const char *msg, ...);
void init_zerr();

void throw_error_with_no_errorcode(const char *format, ...) {
    va_list args;
    va_start(args, format);
    PRINT_ERROR(COLOR_RED, "ERROR", format, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

void not_impl_yet(const char *name) {
    throw_error_with_no_errorcode("'%s' is not implemented yet!", name);
}

const char *error_to_string(Error error) {
    switch (error) {
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        case FATALERROR: return "FATALERROR";
        case ZLIBGLOBALERROR: return "ZLIB_GLOBAL_ERROR";
        default: return "Unknown Error";
    }
}

const char *error_to_color(Error error) {
    switch (error) {
        case WARNING: return COLOR_YELLOW;
        case ERROR: return COLOR_RED;
        case FATALERROR: return COLOR_RED;
        case ZLIBGLOBALERROR: return COLOR_RED;
        default: return COLOR_RESET;
    }
}

ErrorLevel error_to_level(Error error) {
    switch (error) {
        case WARNING: return LEVEL_WARN;
        case ERROR: return LEVEL_FATAL;
        case FATALERROR: return LEVEL_FATAL;
        case ZLIBGLOBALERROR: return LEVEL_FATAL;
        default: return LEVEL_FATAL;
    }
}

void init_zerr() {
    zerr = (Vector *)malloc(sizeof(Vector));
    if (!zerr) {
        fprintf(stderr, "Failed to allocate memory for zerr (zerr = ZLIB ERRORSTREAM = ~stderr)\n");
        exit(EXIT_FAILURE);
    }

    vector_init(zerr, 10, sizeof(Error));
}
void push_error(Error error_code) {
    if (zerr == NULL) {
        init_zerr();
    }

    vector_push(zerr, &error_code);
}

bool check_error(Error error_code) {
    if (zerr == NULL) {
        init_zerr();
    }

    return vector_contains(zerr, &error_code);
}


void throw_error(Error error_code, const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    PRINT_ERROR(error_to_color(error_code), error_to_string(error_code), msg, args);
    va_end(args);
    push_error(error_code);
    if (error_to_level(error_code) == LEVEL_FATAL) {
        exit(EXIT_FAILURE);
    }
}


#endif // ERROR_H
