#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define historysize 20
static int historycount = 0;
static int historyindex = 0;
static char *history[historysize];
void save_history(const char *line) {
    if (line == NULL || strlen(line) == 0 || strcmp(line, "\n") == 0) return;

    if (history[historyindex]) {
        free(history[historyindex]);
    }
    history[historyindex] = strdup(line);
    historyindex = (historyindex + 1) % historysize;

    if (history_count < historysize) {
        history_count++;
    }
}
void print_history() {
    int start = (historyindex - historycount + historysize) % historysize;
    for (int i = 0; i < historycount; i++) {
        int index = (start + i) % historysize;
        printf("%d: %s", i, history[index]);
    }
}
void clear_history() {
    for (int i = 0; i < historysize; i++) {
        free(history[i]);
        history[i] = NULL;
    }
    historycount = 0;
    historyindex = 0;
}
char *get_history_command(int index) {
    if (index < 0 || index >= historycount) return NULL;
    int realindex = (historyindex - historycount + index + historysize) % historysize;
    return history[realindex] ? strdup(history[realindex]) : NULL;
}
