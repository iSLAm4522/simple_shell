#include "main.h"

/**
* execute_cmd - executes a command in a child process
* @ctx: Pointer to shell context containing program name
* @args: array of arguments for the command
*
* Return: 0 on success, exit status of child process, or -1 on failure
*/

int	execute_cmd(shell_context_t *ctx, char **args)
{
	char *cmd_path;
	pid_t pid;
	int	status;

	if (!args || args[0] == NULL)
		return (0);

	cmd_path = find_command_path(args[0]);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", ctx->program_name, args[0]);
		return (CMD_NOT_FOUND);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror(ctx->program_name);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (-1);
	}
	return (-1);
}
