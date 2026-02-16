#include "main.h"

/**
* shell_loop - Main loop of the shell program
* @ctx: Pointer to shell context containing program name and exit status
*
* Description: Continuously reads user input and processes commands
* in an infinite loop until the program is terminated.
*
* Return: Always 0 (Success)
*/

int shell_loop(shell_context_t *ctx)
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
			exec_status = execute_builtin_command(ctx, builtin_idx, tokens, input);
		}
		else
			exec_status = execute_cmd(ctx, tokens);

		ctx->last_exit_status = exec_status;
		free(tokens);
		free(input);
		tokens = NULL;
		input = NULL;
	}

	return (exec_status);
}
