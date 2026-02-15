#include "main.h"

/**
 * builtin_exit_shell - Exit the shell program
 *
 * Return: Always returns 0, but exits before return
 */
int builtin_exit_shell(void)
{
	exit(last_exit_status);
	return (0);
}

/**
 * builtin_env - Print environment variables
 *
 * Return: Always returns 0
 */
int builtin_env(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}
