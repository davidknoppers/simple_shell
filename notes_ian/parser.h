#ifndef SHELL_H
#define SHELL_H

/*
#include <unistd.h>
#include <stdio.h>
*/

int executor(int *ac, char *argv[]);
char **parser(int *ac, char *str);
void reader(void);
/*
size_t _getline(char **line, size_t *n, FILE *stream);
char *_strtok(char *str, const char *delim);
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
*/

#endif
