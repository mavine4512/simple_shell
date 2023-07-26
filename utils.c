#include "shell.h"

/**
 * is_chain - checks if character in buffer is a delimiter
 * @info: information
 * @buf: memory location
 * @p: character
 * Return: 1 or 0
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t b = *p;
	int f = 0;

	switch (buf[b])
	{
		case '|':
			if (buf[b + 1] == '|')
			{
				buf[b] = 0;
				b++;
				info->cmd_buf_type = CMD_OR;
				f = 1;
			}
			break;
		case '&':
			if (buf[b + 1] == '&')
			{
				buf[b] = 0;
				b++;
				info->cmd_buf_type = CMD_AND;
				f = 1;
			}
			break;
		case ';':
			buf[b] = 0;
			info->cmd_buf_type = CMD_CHAIN;
			f = 1;
			break;
		default:
			break;
	}
	if (f)
	{
		*p = b;
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * check_chain - A program function that checks chain
 * @info: information
 * @buf: memory location
 * @p: current location
 * @i: head
 * @len: length
 * Return: chain
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t b = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			b = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			b = len;
		}
	}
	*p = b;
}

/**
 * replace_alias - function that replaces aliases
 * @info: information
 * Return: alias
 */
int replace_alias(info_t *info)
{
	char *n;
	list_t *node;
	int a = 0;

	for (a = 0; a < 10; a++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		n = _strchr(node->str, '=');
		if (!n)
			return (0);
		n = _strdup(n + 1);
		if (!n)
			return (0);
		info->argv[0] = n;
	}
	return (1);
}

/**
 * replace_variables - a function that replaces variables
 * @info: information
 * Return: replaced variables
 */
int replace_variables(info_t *info)
{
	int a;
	list_t *node;

	for (a = 0; info->argv[a]; a++)
	{
		if (info->argv[a][0] != '$' || info->argv[a][1])
			continue;
		if (!_strcmp(info->argv[a], "$?"))
		{
			replace_str(&(info->argv[a]),
					_strdup(conv_no(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[a], "$$"))
		{
			replace_str(&(info->argv[a]),
					_strdup(conv_no(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[a][1], '=');
		if (node)
		{
			replace_str(&(info->argv[a]),
					_strdup(_strchr(node->str
							, '=') + 1));
			continue;
		}
		replace_str(&info->argv[a], _strdup(""));
	}
	return (0);
}

/**
 * replace_str - a function that replaces a string
 * @old: old string
 * @new: new string
 * Return: string
 */
int replace_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

