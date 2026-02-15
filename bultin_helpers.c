#include "main.h"

static char *builtin_commands[] = {

	"exit",
	NULL
};

static int (*builtin_functions[])(void) = {

	builtin_exit_shell,
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
* @idx: The index of the builtin command to execute
*
* Return: The return value of the builtin function, or -1 if not a builtin
*/
int execute_builtin_command(int idx)
{
	int max_idx = (sizeof(builtin_functions) / sizeof(builtin_functions[0])) - 1;

	if (idx < 0 || idx >= max_idx)
		return (-1);
	return (builtin_functions[idx]());
}
