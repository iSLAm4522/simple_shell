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

/**
* string_length - Calculates the length of a string
* @str: The string to measure
*
* Return: The length of the string, or 0 if str is NULL
*/
int string_length(const char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (str[length] != '\0')
		length++;

	return (length);
}

/**
* string_duplicate - Creates a duplicate copy of a string
* @str: The string to duplicate
*
* Return: Pointer to the newly allocated duplicate string,
* or NULL if str is NULL
*/
char *string_duplicate(const char *str)
{
	int length;

	char *dup;

	int i;

	if (!str)
		return (NULL);

	length = string_length(str);
	dup = malloc(length + 1);
	if (!dup)
		return (NULL);

	for (i = 0; i < length; i++)
		dup[i] = str[i];
	dup[length] = '\0';

	return (dup);
}


/**
* string_copy - Copies a string from source to destination
* @dest: The destination string
* @src: The source string
*
* Return: Pointer to the destination string
*/
char *string_copy(char *dest, const char *src)
{
	char *d = dest;

	if (!dest || !src)
		return (dest);

	while (*src != '\0')
	{
		*d = *src;
		d++;
		src++;
	}
	*d = '\0';
	return (dest);
}

/**
* string_concat - Concatenates two strings
* @dest: The destination string
* @src: The source string to append
*
* Return: Pointer to the destination string
*/
char *string_concat(char *dest, const char *src)
{
	char *d = dest;

	if (!dest || !src)
		return (dest);

	while (*d != '\0')
		d++;
	while (*src != '\0')
	{
		*d = *src;
		d++;
		src++;
	}
	*d = '\0';
	return (dest);
}
