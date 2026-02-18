#include "main.h"

static char *builtin_commands[] = {

	"exit",
	"env",
	"setenv",
	"unsetenv",
	"pwd",
	"cd",
	NULL
};

static int (*builtin_functions[])(shell_context_t *ctx, char **args,
	char *input) = {

	builtin_exit_shell,
	builtin_env,
	builtin_setenv,
	builtin_unsetenv,
	builtin_pwd,
	builtin_cd,
	NULL
};


/**
* is_builtin_command - Check if a command is a builtin command
* @command: The command to check
*
* Return: Index of builtin command or -1 if not found
*/
int is_builtin_command(char *command)
{
	int i = 0;

	while (builtin_commands[i] != NULL)
	{
		if (string_compare(command, builtin_commands[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/**
* execute_builtin_command - Execute a builtin command
* @ctx: Pointer to shell context
* @idx: The index of the builtin command to execute
* @args: The arguments for the builtin command
* @input: The input string
*
* Return: The return value of the builtin function, or -1 if not a builtin
*/
int execute_builtin_command(shell_context_t *ctx, int idx, char **args,
	char *input)
{
	int max_idx = (sizeof(builtin_functions) / sizeof(builtin_functions[0])) - 1;

	if (idx < 0 || idx >= max_idx)
		return (-1);
	return (builtin_functions[idx](ctx, args, input));
}

/**
* get_cwd - Get the current working directory
* Return: The current working directory, or NULL on failure
*/
char *get_cwd(void)
{
	char *cwd = getcwd(NULL, 0);

	if (!cwd)
		return (NULL);
	return (cwd);
}
