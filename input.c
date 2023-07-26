#include "shell.h"
/**
 * clear_data - function that initializes structure
 * @info: information
 * Return: initialized data
 */
void clear_data(info_t *info)
{

	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * set_data - a function that initializes structure
 * @info: information
 * @av: arguement array
 * Return: data
 */
void set_data(info_t *info, char **av)
{
	int a = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		while (info->argv && info->argv[a])
		{
			a++;
		}
		info->argc = a;

		replace_alias(info);
		replace_variables(info);
	}
}
/**
 * free_data - a function that frees data
 * @info: information
 * @all: all data
 * Return: freed data
 */
void free_data(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}

}

