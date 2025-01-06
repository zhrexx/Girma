// ========================================================================================>
// ZHRXXgroup Project 🚀 - ZLib
// File: logger.h
// Author(s): ZHRXXgroup
// Version: 1
// ========================================================================================>



#ifndef LOGGER_H
#define LOGGER_H
typedef enum {
    LOG_SUCCESS,
    LOG_INFO,
    LOG_WARNING,
    LOG_DEBUG,
    LOG_TRACE,
    LOG_ERROR
} LOG_LEVEL;

#include <stdio.h>

void logger_log(LOG_LEVEL level, const char *message);

//---------------------------------------------------
//---------------------------------------------------


static const char *color_white = "\033[0;37m";
static const char *color_red = "\033[0;31m";
static const char *color_green = "\033[0;32m";
static const char *color_yellow = "\033[0;33m";
static const char *color_blue = "\033[0;34m";
static const char *color_reset = "\033[0m";

void logger_log(LOG_LEVEL level, const char *message) {
    switch (level) {
        case LOG_SUCCESS:
            printf("%s[SUCCESS] %s%s\n", color_green, message, color_reset);
            break;
        case LOG_INFO:
            printf("%s[INFO] %s%s\n", color_blue, message, color_reset);
            break;
        case LOG_WARNING:
            printf("%s[WARNING] %s%s\n", color_yellow, message, color_reset);
            break;
        case LOG_DEBUG:
            printf("%s[DEBUG] %s%s\n", color_white, message, color_reset);
            break;
        case LOG_TRACE:
            printf("%s[TRACE] %s%s\n", color_white, message, color_reset);
            break;
        case LOG_ERROR:
            printf("%s[ERROR] %s%s\n", color_red,message, color_reset);
            break;
    }


}


#endif
