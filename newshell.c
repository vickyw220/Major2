#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "builtins.h"
#include "pipeline.h"
#include "history.h"
#include "path.h"
#include "redirect.h"

#define MAX_ARGS 100

void print_error() {
    fprintf(stderr, "An error has occurred\n");
}

int main() {
    char *line = NULL;
    size_t len = 0;

    init_path();  // load path from env

    while (1) {
        printf("newshell> ");
        if (getline(&line, &len, stdin) == -1) break;

        save_history(line);
        line[strcspn(line, "\n")] = 0;

        char *args[MAX_ARGS];
        int i = 0;
        args[i] = strtok(line, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1)
            args[++i] = strtok(NULL, " ");
        args[i] = NULL;
        if (args[0] == NULL) continue;

        if (handle_builtin(args)) continue;

        if (contains_pipe(args)) {
            handle_pipeline(args);
            continue;
        }

        pid_t pid = fork();
        if (pid == 0) {
            handle_redirection(args);
            char *full_path = find_in_path(args[0]);
            if (full_path) {
                execv(full_path, args);
            }
            print_error();
            exit(1);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            print_error();
        }
    }

    restore_original_path(); // on exit
    free(line);
    return 0;
}
