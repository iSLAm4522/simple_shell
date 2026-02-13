#include "main.h"


/**
* shell_loop - Main loop of the shell program
*
* Description: Continuously reads user input and processes commands
* in an infinite loop until the program is terminated.
*
* Return: Always 0 (Success)
*/

int shell_loop(void)
{
	char *input;
	char **tokens;
	int exec_status;

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

		exec_status = execute_cmd(tokens);
		(void)exec_status; /* Suppress unused variable warning */

		free(tokens);
		free(input);
		tokens = NULL;
		input = NULL;
	}

	return (0);
}
