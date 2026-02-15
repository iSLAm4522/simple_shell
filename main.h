#ifndef MAIN_H
#define MAIN_H

extern char **environ;
extern int last_exit_status;

/* Define a constant for command not found error code */
#define INITIAL_TOKENS 10
#define CMD_NOT_FOUND 127

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

/* Header file for helpers */
int is_builtin_command(char *command);
int execute_builtin_command(int idx);

/* Header file for builtins */
int builtin_exit_shell(void);
int builtin_env(void);


/* Header file for utils */
char *trim_whitespace(char *str);

/* String utility function prototypes */
int string_length(const char *str);
char *string_duplicate(const char *str);
char *string_copy(char *dest, const char *src);
char *string_concat(char *dest, const char *src);
int string_compare(const char *s1, const char *s2);

#endif /* MAIN_H */
