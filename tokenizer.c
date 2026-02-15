#include "main.h"


/**
* parse_input - Tokenizes the input string into an array of tokens
* @input: The input string to be tokenized
*
* Return: A pointer to an array of token strings, NULL-terminated,
* or NULL on error
*/

char **parse_input(char *input)
{
	char **tokens, **new_tokens;
	char *token;
	const char *delm = " \t\r\n";

	size_t position = 0;
	size_t size = INITIAL_TOKENS;

	if (!input)
		return (NULL);

	tokens = malloc(sizeof(char *) * size);
	if (!tokens)
	{
		fprintf(stderr, "Allocation error\n");
		return (NULL);
	}

	token = strtok(input, delm);
	while (token != NULL)
	{
		if (position >= size)
		{
			size *= 2;
			new_tokens = realloc(tokens, sizeof(char *) * size);
			if (!new_tokens)
			{
				fprintf(stderr, "Reallocation error\n");
				free(tokens);
				return (NULL);
			}
			tokens = new_tokens;
		}
		tokens[position] = token;
		position++;
		token = strtok(NULL, delm);
	}
	tokens[position] = NULL;
	return (tokens);
}
