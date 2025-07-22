#ifndef myhistory.h
#define myhistory.h

void save_history(const char *line);
void print_history();
void clear_history();
char *get_history_command(int index);

#endif

