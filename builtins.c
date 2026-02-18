#include "main.h"

/* Static variable to track our custom environment */
static char **my_environ;

/**
 * copy_environ - Creates a deep copy of the environment
 *
 * Return: Pointer to newly allocated environment copy, or NULL on failure
 */
static char **copy_environ(void)
{
	char **new_env;
	int i, count = 0;

	while (environ[count])
		count++;

	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);

	for (i = 0; i < count; i++)
	{
		new_env[i] = string_duplicate(environ[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
	}
	new_env[count] = NULL;
	return (new_env);
}

/**
 * free_my_environ - Frees the custom environment array
 */
void free_my_environ(void)
{
	int i;

	if (my_environ)
	{
		for (i = 0; my_environ[i]; i++)
			free(my_environ[i]);
		free(my_environ);
		my_environ = NULL;
	}
}


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
			free_my_environ();
			exit(EXIT_ILLEGAL_NUMBER);
		}
	}
	free(args);
	free(input);
	free_my_environ();
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

/**
 * builtin_setenv - Initialize or modify an environment variable
 * @ctx: Pointer to shell context
 * @args: The arguments (args[1] = variable, args[2] = value)
 * @input: The input string (unused)
 *
 * Return: 0 on success, 1 on failure
 */
int builtin_setenv(shell_context_t *ctx, char **args, char *input)
{
	char **new_environ, *new_var;
	int i, count, var_len, found_idx = -1;

	(void)input;
	if (!args || !args[1] || !args[2])
	{
		fprintf(stderr, "%s: 1: setenv: missing arguments\n", ctx->program_name);
		return (1);
	}
	if (!my_environ)
	{
		my_environ = copy_environ();
		if (!my_environ)
		{
			fprintf(stderr, "%s: 1: setenv: allocation failed\n", ctx->program_name);
			return (1);
		}
		environ = my_environ;
	}
	var_len = string_length(args[1]);
	count = 0;
	while (my_environ[count])
	{
		if (string_length(my_environ[count]) > var_len &&
			my_environ[count][var_len] == '=')
		{
			int j, match = 1;

			for (j = 0; j < var_len; j++)
			{
				if (my_environ[count][j] != args[1][j])
				{
					match = 0;
					break;
				}
			}
			if (match)
				found_idx = count;
		}
		count++;
	}
	new_var = malloc(var_len + string_length(args[2]) + 2);
	if (!new_var)
	{
		fprintf(stderr, "%s: 1: setenv: allocation failed\n", ctx->program_name);
		return (1);
	}
	string_copy(new_var, args[1]);
	string_concat(new_var, "=");
	string_concat(new_var, args[2]);
	if (found_idx >= 0)
	{
		free(my_environ[found_idx]);
		my_environ[found_idx] = new_var;
		return (0);
	}
	new_environ = malloc(sizeof(char *) * (count + 2));
	if (!new_environ)
	{
		fprintf(stderr, "%s: 1: setenv: allocation failed\n", ctx->program_name);
		free(new_var);
		return (1);
	}
	for (i = 0; i < count; i++)
		new_environ[i] = my_environ[i];
	new_environ[count] = new_var;
	new_environ[count + 1] = NULL;
    free(my_environ);
	my_environ = new_environ;
	environ = my_environ;
	return (0);
}

/**
 * builtin_unsetenv - Remove an environment variable
 * @ctx: Pointer to shell context
 * @args: The arguments (args[1] = variable name)
 * @input: The input string (unused)
 *
 * Return: 0 on success, 1 on failure
 */
int builtin_unsetenv(shell_context_t *ctx, char **args, char *input)
{
	char **new_environ;
	int i, j, count, var_len, found_idx = -1;

	(void)input;
	if (!args || !args[1])
	{
		fprintf(stderr, "%s: 1: unsetenv: missing variable name\n", ctx->program_name);
		return (1);
	}
	if (!my_environ)
	{
		my_environ = copy_environ();
		if (!my_environ)
		{
			fprintf(stderr, "%s: 1: unsetenv: allocation failed\n", ctx->program_name);
			return (1);
		}
		environ = my_environ;
	}
	var_len = string_length(args[1]);
	count = 0;
	while (my_environ[count])
	{
		if (string_length(my_environ[count]) > var_len &&
			my_environ[count][var_len] == '=')
		{
			int k, match = 1;

			for (k = 0; k < var_len; k++)
			{
				if (my_environ[count][k] != args[1][k])
				{
					match = 0;
					break;
				}
			}
			if (match)
				found_idx = count;
		}
		count++;
	}
	if (found_idx < 0)
		return (0);
	new_environ = malloc(sizeof(char *) * count);
	if (!new_environ)
	{
		fprintf(stderr, "%s: 1: unsetenv: allocation failed\n", ctx->program_name);
		return (1);
	}
	j = 0;
	for (i = 0; i < count; i++)
	{
		if (i != found_idx)
			new_environ[j++] = my_environ[i];
		else
			free(my_environ[i]);
	}
	new_environ[j] = NULL;
	free(my_environ);
	my_environ = new_environ;
	environ = my_environ;
	return (0);
}
