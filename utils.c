#include "main.h"

/**
* get_env_var - Gets the value of an environment variable
* @name: The name of the environment variable
*
* Return: Pointer to the value of the environment variable,
* or NULL if not found
*/
char *get_env_var(const char *name)
{
	int i;
	int len;

	if (!name || !environ)
		return (NULL);

	len = string_length(name);
	for (i = 0; environ[i]; i++)
	{
		if (string_length(environ[i]) > len && environ[i][len] == '=')
		{
			int j;
			int match = 1;

			for (j = 0; j < len; j++)
			{
				if (environ[i][j] != name[j])
				{
					match = 0;
					break;
				}
			}
			if (match)
				return (environ[i] + len + 1);
		}
	}
	return (NULL);
}

/**
* trim_whitespace - Removes leading and trailing whitespace from a string
* @str: The string to trim
*
* Return: Pointer to the trimmed string (modified in place)
*/

char *trim_whitespace(char *str)
{

	char *start, *end;

	if (!str)
		return (NULL);

	start = str;
	while (*start && (*start == ' ' || *start == '\t' ||
		*start == '\n' || *start == '\r'))
		start++;

	if (*start == '\0')
	{
		*str = '\0';
		return (str);
	}

	end = start;
	while (*end != '\0')
		end++;
	end--;

	while (end > start && (*end == ' ' || *end == '\t' ||
		*end == '\n' || *end == '\r'))
		end--;
	*(end + 1) = '\0';

	if (start != str)
	{
		char *src = start, *dst = str;

		while (*src != '\0')
		{
			*dst = *src;
			dst++;
			src++;
		}
		*dst = '\0';
	}
	return (str);
}

/**
* string_to_int - Converts a string to an integer
* @str: The string to convert
* @endptr: Pointer to store the end of the converted string
*
* Return: The integer value of the string
*/
int string_to_int(char *str, char **endptr)
{
	int res = 0;
	int sign = 1;

	if (!str)
	{
		if (endptr)
			*endptr = str;
		return (0);
	}

	while (*str == ' ' || *str == '\t')
		str++;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}

	if (*str < '0' || *str > '9')
	{
		if (endptr)
			*endptr = str;
		return (0);
	}

	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}

	if (endptr)
		*endptr = str;
	return (sign * res);
}
