#include "main.h"

/**
* read_input - reads input from user
* Return: pointer to input string
*/

char *read_input(void)
{
	char *input = NULL;

	size_t len = 0;
	ssize_t nread;

	nread = getline(&input, &len, stdin);
	if (nread == -1)
	{
		free(input);
		return (NULL);
	}

	if (nread > 0 && input[nread - 1] == '\n')
		input[nread - 1] = '\0';
	trim_whitespace(input);
	return (input);
}
