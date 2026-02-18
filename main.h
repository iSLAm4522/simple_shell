#ifndef MAIN_H
#define MAIN_H

/* Global variables */
extern char **environ;

/* Define a constant for command not found error code */
#define INITIAL_TOKENS 10
#define CMD_NOT_FOUND 127
#define EXIT_ILLEGAL_NUMBER 2

/**
 * struct shell_context - Structure to hold shell state and configuration
 * @program_name: Name of the shell program
 * @last_exit_status: Exit status of the last executed command
 * @my_environ: Custom environment array
 */
typedef struct shell_context
{
	char *program_name;
	int last_exit_status;
	char **my_environ;
} shell_context_t;

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
int shell_loop(shell_context_t *ctx);
char *read_input(void);
char **parse_input(char *input);
int execute_cmd(shell_context_t *ctx, char **args);
char *find_command_path(char *command);

/* Header file for builtins helpers */
int is_builtin_command(char *command);
int execute_builtin_command(shell_context_t *ctx, int idx, char **args,
char *input);
char *get_cwd(void);

/* Header file for builtins */
int builtin_exit_shell(shell_context_t *ctx, char **args, char *input);
int builtin_env(shell_context_t *ctx, char **args, char *input);
int builtin_setenv(shell_context_t *ctx, char **args, char *input);
int builtin_unsetenv(shell_context_t *ctx, char **args, char *input);
int builtin_pwd(shell_context_t *ctx, char **args, char *input);
int builtin_cd(shell_context_t *ctx, char **args, char *input);
void free_my_environ(shell_context_t *ctx);

/* Header file for utils */
char *trim_whitespace(char *str);
int string_to_int(char *str, char **endptr);
char *get_env_var(const char *name);

/* String utility function prototypes */
int string_length(const char *str);
char *string_duplicate(const char *str);
char *string_copy(char *dest, const char *src);
char *string_concat(char *dest, const char *src);
int string_compare(const char *s1, const char *s2);

#endif /* MAIN_H */
