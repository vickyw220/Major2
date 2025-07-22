#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "path.h"

#define MAX_PATHS 100
static char *path_list[MAX_PATHS];
static int path_count = 0;
static char *original_path = NULL;

void init_path() {
    char *env = getenv("PATH");
    if (env) original_path = strdup(env);

    char *copy = strdup(env);
    char *token = strtok(copy, ":");
    while (token && path_count < MAX_PATHS) {
        path_list[path_count++] = strdup(token);
        token = strtok(NULL, ":");
    }
    free(copy);
    update_env_path();
}

void print_path() {
    for (int i = 0; i < path_count; i++) {
        printf("%s", path_list[i]);
        if (i < path_count - 1) printf(":");
    }
    printf("\n");
}

void add_path(const char *p) {
    if (path_count < MAX_PATHS) {
        path_list[path_count++] = strdup(p);
        update_env_path();
    }
}

void remove_path(const char *p) {
    for (int i = 0; i < path_count; i++) {
        if (strcmp(path_list[i], p) == 0) {
            free(path_list[i]);
            for (int j = i; j < path_count - 1; j++)
                path_list[j] = path_list[j + 1];
            path_count--;
            update_env_path();
            break;
        }
    }
}

void update_env_path() {
    char buffer[4096] = "";
    for (int i = 0; i < path_count; i++) {
        strcat(buffer, path_list[i]);
        if (i < path_count - 1) strcat(buffer, ":");
    }
    setenv("PATH", buffer, 1);
}

void restore_original_path() {
    if (original_path) {
        setenv("PATH", original_path, 1);
        free(original_path);
        original_path = NULL;
    }
}

char *find_in_path(const char *cmd) {
    static char full[1024];
    for (int i = 0; i < path_count; i++) {
        snprintf(full, sizeof(full), "%s/%s", path_list[i], cmd);
        if (access(full, X_OK) == 0) return full;
    }
    return NULL;
}
