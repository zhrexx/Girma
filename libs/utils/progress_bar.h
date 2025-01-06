#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <stdio.h>

typedef struct {
    int width;
    int total_steps;
    int current_step;
    char fill_char;
    char empty_char;
} ProgressBar;

void progress_bar_init(ProgressBar *bar, int total_steps, int width);
void progress_bar_update(ProgressBar *bar, int step);
void progress_bar_finish(ProgressBar *bar, char *message);

//------------------------------------------------------------------------
//------------------------------------------------------------------------

void progress_bar_init(ProgressBar *bar, int total_steps, int width) {
    bar->width = width;
    bar->total_steps = total_steps;
    bar->current_step = 0;
    bar->fill_char = '#';
    bar->empty_char = '-';
}

void progress_bar_update(ProgressBar *bar, int step) {
    bar->current_step = step;
    float progress_ratio = (float)step / bar->total_steps;
    int fill_length = (int)(progress_ratio * bar->width);

    printf("\r[");
    for (int i = 0; i < bar->width; i++) {
        if (i < fill_length) {
            putchar(bar->fill_char);
        } else {
            putchar(bar->empty_char);
        }
    }
    printf("] %d%%", (int)(progress_ratio * 100));
    fflush(stdout);
}

//void progress_bar_finish(ProgressBar *bar) {
//    progress_bar_update(bar, bar->total_steps);
//    printf("\n");
//}

void progress_bar_finish(ProgressBar *bar, char *message) {
    bar->current_step = bar->total_steps;
    int fill_length = bar->width;

    printf("\r[");
    for (int i = 0; i < fill_length; i++) {
        putchar(bar->fill_char);
    }
    printf("] %s\n", message);
    fflush(stdout);
}

#endif

