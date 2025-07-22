#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

#define HISTORY_SIZE 100
static char *entries[HISTORY_SIZE];
static int hist_index = 0, hist_count = 0;

void save_history(const char *line) {
    if (entries[hist_index]) free(entries[hist_index]);
    entries[hist_index] = strdup(line);
    hist_index = (hist_index + 1) % HISTORY_SIZE;
    if (hist_count < HISTORY_SIZE) hist_count++;
}

void print_history() {
    for (int i = 0; i < hist_count; i++) {
        int idx = (hist_index - hist_count + i + HISTORY_SIZE) % HISTORY_SIZE;
        printf("%d: %s", i + 1, entries[idx]);
    }
}
