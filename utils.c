#include "main.h"

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
