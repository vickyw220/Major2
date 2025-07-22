#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtins.h"
#include "history.h"
#include "path.h"

int handle_builtin(char **args) {
    if (strcmp(args[0], "exit") == 0) {
        restore_original_path();
        exit(0);
    }

    if (strcmp(args[0], "myhistory") == 0) {
        print_history();
        return 1;
    }

    if (strcmp(args[0], "path") == 0) {
        if (args[1] == NULL) {
            print_path();
        } else if (strcmp(args[1], "+") == 0 && args[2]) {
            add_path(args[2]);
        } else if (strcmp(args[1], "-") == 0 && args[2]) {
            remove_path(args[2]);
        } else {
            printf("Invalid usage of path command\n");
        }
        return 1;
    }

    return 0;
}
