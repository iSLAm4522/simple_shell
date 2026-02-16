#include "main.h"

/**
 * builtin_exit_shell - Exit the shell program
 * @args: The arguments passed to the exit command
 * @input: The input string to free
 *
 * Return: Always returns 0, but exits before return
 */
int builtin_exit_shell(char **args, char *input)
{
	int exit_code = last_exit_status;

	if (args && args[1])
		exit_code = atoi(args[1]);
	free(args);
	free(input);
	exit(exit_code);
	return (0);
}

/**
 * builtin_env - Print environment variables
 * @args: The arguments passed to the env command (ignored)
 * @input: The input string (ignored)
 *
 * Return: Always returns 0
 */
int builtin_env(char **args, char *input)
{
	char **env = environ;
	(void)args;
	(void)input;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}
