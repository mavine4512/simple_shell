#include "shell.h"

/**
 * _setmem - a function that sets memory
 * @s: pointer to memory
 * @b: byte
 * @n: number
 * Return: memory
 */
char *_setmem(char *s, char b, unsigned int n)
{
	unsigned int a = 0;

	while (a < n)
	{
		s[a] = b;
		a++;
	}
	return (s);
}

/**
 * ffree - a function that frees strings
 * @pp: string
 * Return: freed string
 */
void ffree(char **pp)
{
	char **i = pp;

	if (!pp)
		return;
	for (; *pp; pp++)
	{
		free(*pp);
	}
	free(i);
}

/**
 * _realloc - a function that reallocates memory
 * @pointer: pointer to memory
 * @old_size: previous size
 * @new_size: current size
 * Return: reallocated memory
 */
void *_realloc(void *pointer, unsigned int old_size, unsigned int new_size)
{
	char *x;

	if (!pointer)
		return (malloc(new_size));
	if (!new_size)
		return (free(pointer), NULL);
	if (new_size == old_size)
		return (pointer);
	x = malloc(new_size);
	if (!x)
	{
		return (NULL);
	}
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		x[old_size] = ((char *)pointer)[old_size];
	free(pointer);
	return (x);
}

