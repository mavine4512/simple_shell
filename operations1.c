#include "shell.h"
/**
 * _putchar - a program function that writes a character
 * @c: character
 * Return: a character
 */
int _putchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int a;

	(c == BUF_FLUSH || a >= WRITE_BUF_SIZE) ? (write(1, buf, a), a = 0) : 0;
	(c != BUF_FLUSH) ? (buf[a++] = c) : 0;
	return (1);
}
/**
 * _strdup -  a function that checks for duplicates
 * @str: string
 * Return: a duplicate
 */
char *_strdup(const char *str)
{
	char *est;
	int len = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	est = malloc(sizeof(char) * (len + 1));
	if (!est)
		return (NULL);
	len++;
	while (len--)
	{
		est[len] = *--str;
	}
	return (est);
}
/**
 * _puts - a function that checks for input string
 * @str: string
 * Return: input string
 */
void _puts(char *str)
{
	int a = 0;

	if (!str)
		return;

	for (; str[a] != '\0'; a++)
	{
		_putchar(str[a]);
	}

}
/**
 * _strcpy - a function that copies a string
 * @dest: destination
 * @source: source of string
 * Return: copied string
 */
char *_strcpy(char *dest, char *source)
{
	int a;

	if (dest == source || source == 0)
		return (dest);

	for (a = 0; source[a]; a++)
	{
		dest[a] = source[a];
	}
	dest[a] = 0;
	return (dest);
}

