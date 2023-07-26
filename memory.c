#include "shell.h"

/**
 * bfree - a function that checks for NULL address
 * @pointer: pointer to address
 * Return: pointer
 */
int bfree(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}

