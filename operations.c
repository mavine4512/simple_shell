#include "shell.h"

/**
 * _strlen - function that returns string length
 * @s: string character
 * Return: string length
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	for (a = 0; s[a] != '\0'; a++)
		;

	return (a);
}

/**
 * _strcmp - a function that compares a string
 * @s1: string one
 * @s2: string two
 * Return: compared string
 */
int _strcmp(char *s1, char *s2)
{
	for (; *s1 && *s2 && (*s1 == *s2); s1++, s2++)
		;
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);

}

/**
 * starts_with - a function that checks if a string a substring
 * @haystack: search string
 * @needle: found string
 * Return: string
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - a function that concatenates strings
 * @dest: destination
 * @source: source of string
 * Return: concatenated string
 */
char *_strcat(char *dest, char *source)
{
	char *est = dest;

	for (; *dest; ++dest)
	{
	}
	for (; *source; ++source, ++dest)
	{
		*dest = *source;
	}
	*dest = '\0';
	return (est);
}

