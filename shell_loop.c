#include "main.h"

/* Global variable for last exit status */
int last_exit_status = 0;


/**
* shell_loop - Main loop of the shell program
* @program_name: Name of the program (argv[0])
*
* Description: Continuously reads user input and processes commands
* in an infinite loop until the program is terminated.
*
* Return: Always 0 (Success)
*/

int shell_loop(char *program_name)
{
	char *input;
	char **tokens;
	int exec_status = 0;
	int builtin_idx;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");

		input = read_input();
		if (input == NULL || input[0] == '\0')
		{
			if (input == NULL)
				break;
			free(input);
			continue;
		}

		tokens = parse_input(input);
		if (tokens == NULL)
		{
			fprintf(stderr, "Error: Failed to parse input\n");
			free(input);
			continue;
		}

		builtin_idx = is_builtin_command(tokens[0]);
		if (builtin_idx >= 0)
		{
			if (builtin_idx == 0) /* exit */
			{
				free(tokens);
				free(input);
			}
			exec_status = execute_builtin_command(builtin_idx);
		}
		else
			exec_status = execute_cmd(program_name, tokens);

		if (builtin_idx != 0)
		{
			free(tokens);
			free(input);
		}
		last_exit_status = exec_status;
		tokens = NULL;
		input = NULL;
	}

	return (exec_status);
}
