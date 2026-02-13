#include "main.h"

/**
* execute_cmd - executes a command in a child process
* @args: array of arguments for the command
*
* Return: 0 on success, exit status of child process, or -1 on failure
*/

int	execute_cmd(char **args)
{
	pid_t pid;
	int	status;

	if (!args || args[0] == NULL)
		return (0);

	if (args[1] != NULL)
	{
		fprintf(stderr, "./shell: No such file or directory\n");
		return (-1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (-1);
	}
	return (-1);
}
