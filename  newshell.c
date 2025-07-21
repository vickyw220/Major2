//main file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "builtins.h"
#include "pipeline.h"
#include "history.h"

#define MAX_ARGS 100

void print_error() {
    fprintf(stderr, "An error has occurred\n");
}

int main() {
    char *line = NULL;
    size_t len = 0;

    while (1) {
        printf("newshell> ");
        if (getline(&line, &len, stdin) == -1) break;

        //save line
        save_history(line);

        //newline
        line[strcspn(line, "\n")] = 0;

        //tokenize imput
        char *args[MAX_ARGS];
        int i = 0;
        args[i] = strtok(line, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1)
            args[++i] = strtok(NULL, " ");
        args[i] = NULL;
        if (args[0] == NULL) continue;

        // built n check
        if (handle_builtin(args)) continue;

        //pipe check
        if (contains_pipe(args)) {
            handle_pipeline(args);
            continue;
        }

        //the redirection command
        pid_t pid = fork();
        if (pid == 0) {
            handle_redirection(args);
            execvp(args[0], args);
            print_error();
            exit(1);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            print_error();
        }
    }
    free(line);
    return 0;
}
