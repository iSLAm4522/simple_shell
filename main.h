#ifndef MAIN_H
#define MAIN_H

extern char **environ;

/* Header file for main.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

/* Function prototypes */
int shell_loop(void);
char *read_input(void);
char **parse_input(char *input);
int execute_cmd(char **args);
char *find_command_path(char *command);
int is_command_executable(char *command);
char *trim_whitespace(char *str);

#endif /* MAIN_H */
