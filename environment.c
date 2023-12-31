#include "shell.h"

/**
 * _myenvironment - prints current environment variables
 * @info: struct containing potential args. Used to maintain
 *       constant function prototype.
 * Return: Always 0
 */
int _myenvironment(info_t *info)
{
	print_ls_string(info->env);
	return (0);
}

/**
 * _getenviron - gets value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 * @name: environment variable name
 * Return: the value
 */
char *_getenviron(info_t *info, const char *name)
{
	list_t *node;
	char *p;

	for (node = info->env; node != NULL; node = node->next)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
	}
	return (NULL);
}

/**
 * _mysetenviron - Initialize a new environment var
 *       or modify an existing onr
 * @info: Structure containing potential arguments. used to maintain
 *           constant function prototype.
 * Return: Always 0
 */
int _mysetenviron(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * _myunsetenviron - Rem environment variable
 * @info: Structure containing potential arguments. used to maintain
 *   constant function prototype.
 * Return: Always 0.
 */
int _myunsetenviron(info_t *info)
{
	int index;

	if (info->argc == 1)
	{
		_puts("Too few arguements.\n");
		return (1);
	}
	index = 1;
	while (index <= info->argc)
	{
		_unsetenv(info, info->argv[index]);
		index++;
	}
	return (0);
}

/**
 * populate_env_list - populates environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 *       constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t index;

	index = 0;
	while (environ[index])
	{
		add_node_end(&node, environ[index], 0);
		index++;
	}
	info->env = node;
	return (0);
}

