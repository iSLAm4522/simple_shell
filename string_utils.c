#include "main.h"

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

/**
* string_compare - Compares two strings
* @s1: The first string
* @s2: The second string
*
* Return: 0 if strings are equal, negative if s1 < s2, positive if s1 > s2
*/
int string_compare(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (s1 ? 1 : (s2 ? -1 : 0));

	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
