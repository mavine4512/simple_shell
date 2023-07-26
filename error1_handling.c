#include "shell.h"

/**
 * _eratoi - Convert a string to an integer
 * @s: string to be converted
 * Return: 0 if no number in str, convert number otherwise
 *   -1 on error
 */
int _eratoi(char *s)
{
	int index = 0;
	unsigned long int rslt = 0;

	if (*s == '+')
		s++;
	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			rslt *= 10;
			rslt += (s[index] - '0');
			if (rslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
		index++;
	}
	return (rslt);
}

/**
 * print_err - print an error msg
 * @info: Parameter & return info structure
 * @estr: string containing specified error type
 * Return: 0 if no nos in string, converted no otherwise
 *   -1 on error
 */
void print_err(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function prints a decimal (int) number in base 10
 * @input: the input number
 * @fd: the file descriptor to write to
 *
 * Return: number of chars printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int index, count = 0;
	unsigned int _abs_,  current;

	if (fd == STDERR_FILENO)
	{
		__putchar = _eputchar;
	}
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	index = 1000000000;
	while (index > 1)
	{
		if (_abs_ / index)
		{
			__putchar('0' + current / index);
			count++;
		}
		count %= index;
		index /= 10;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * conv_no - convert a number to a string
 * @num: the number
 * @base: the base
 * @flags: arguement flags
 * Return: the string representation of the number
 */
char *conv_no(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0, *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	(sign) ? (*--ptr = sign) : 0;
	return (ptr);
}

/**
 * rm_comments - function to replace 1st;
 * instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: Always 0;
 */
void rm_comments(char *buf)
{
	int index;

	index = 0;
	while (buf[index] != '\0')
	{
		(buf[index] == '#' && (!index || buf[index - 1] == ' ')) ?
			(buf[index] = '\0', 0) : 0;
		index++;
	}
}

