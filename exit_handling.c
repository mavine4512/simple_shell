#include "shell.h"

/**
 * *_strncpy - copies a string
 * @dest: the destination string to be copied to
 * @source: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
 */
char *_strncpy(char *dest, char *source, int n)
{
	int index, num;
	char *s = dest;

	for (index = 0; source[index] != '\0' && index < n - 1; index++)
	{
		dest[index] = source[index];
	}
	if (index < n)
	{
		for (num = index; num < n; num++)
		{
			dest[num] = '\0';
		}
	}
	return (s);
}

/**
 * *_strncat - concatenates two strings
 * @dest: the first string
 * @source: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *_strncat(char *dest, char *source, int n)
{
	int index, num;
	char *s = dest;

	for (index = 0; dest[index] != '\0'; index++)
		;
	for (num = 0; source[num] != '\0' && num < n; num++)
	{
		dest[index] = source[num];
		index++;
	}
	if (num < n)
		dest[index] = '\0';
	return (s);
}

/**
 * *_strchr - will locate a character in a string
 * @s: string to be parsed
 * @c: character to look for
 * Return:(s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

