#include "shell.h"

/**
 * _eputs - print an input string stderr
 * @str: string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int index;

	if (!str)
		return;

	for (index = 0; str[index] != '\0'; index++)
	{
		_eputchar(str[index]);
	}
}

/**
 * _eputchar - writes character c to stderr
 * @c: The character to print
 * Return: on success 1.
 * On error, -1 is returned, and errno is set appropriately
 */
int _eputchar(char c)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buf, index);
		index = 0;
	}
	(c != BUF_FLUSH) ? (buf[index++] = c) : 0;
	return (1);
}
/**
 * _putfd - char c to given file description
 * @c: The char to print
 * @fd: The file descriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(fd, buf, index);
		index = 0;
	}
	(c != BUF_FLUSH) ? (buf[index++] = c) : 0;

	return (1);
}

/**
 * _putsfd - writes character c to given file descriptor
 * @str: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: on success 1.
 * on error, -1 is returned, and errno is set appropriately.
 */
int _putsfd(char *str, int fd)
{
	int index = 0;

	if (!str)
		return (0);

	for (index = 0; str[index] != '\0'; index++)
	{
		index += _putfd(str[index], fd);
	}

	return (index);
}

