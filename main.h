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
int shell_loop(char *program_name);
char *read_input(void);
char **parse_input(char *input);
int execute_cmd(char *program_name, char **args);
char *find_command_path(char *command);


/* Utility function prototypes */
char *trim_whitespace(char *str);
int string_length(const char *str);
char *string_duplicate(const char *str);
char *string_copy(char *dest, const char *src);
char *string_concat(char *dest, const char *src);

#endif /* MAIN_H */
