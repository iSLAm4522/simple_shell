#include "main.h"

/**
 * builtin_exit_shell - Exit the shell program
 * @ctx: Pointer to shell context containing program name
 * @args: The arguments passed to the exit command
 * @input: The input string to free
 *
 * Return: Always returns 0, but exits before return
 */
int builtin_exit_shell(shell_context_t *ctx, char **args, char *input)
{
	int exit_code = ctx->last_exit_status;

	if (args && args[1])
	{
		char *endptr;

		exit_code = string_to_int(args[1], &endptr);
		if (*endptr != '\0' || exit_code < 0)
		{
			fprintf(stderr, "%s: 1: exit: Illegal number: %s\n",
				ctx->program_name, args[1]);
			free(args);
			free(input);
			exit(EXIT_ILLEGAL_NUMBER);
		}
	}
	free(args);
	free(input);
	exit(exit_code);
	return (0);
}

/**
 * builtin_env - Print environment variables
 * @ctx: Pointer to shell context (unused)
 * @args: The arguments passed to the env command (ignored)
 * @input: The input string (ignored)
 *
 * Return: Always returns 0
 */
int builtin_env(shell_context_t *ctx, char **args, char *input)
{
	char **env = environ;

	(void)ctx;
	(void)args;
	(void)input;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}
