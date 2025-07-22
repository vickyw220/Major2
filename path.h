#ifndef PATH_H
#define PATH_H
void init_path();
void print_path();
void add_path(const char *p);
void remove_path(const char *p);
void update_env_path();
void restore_original_path();
char *find_in_path(const char *cmd);
#endif
