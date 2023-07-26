#include "shell.h"

/**
 * is_cmd - a function that checks for commandd
 * @info: information
 * @path: path to file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - a function that duplicates characters
 * @pathstr: path for string
 * @start: head node
 * @stop: last node
 * Return: duplicated characters
 */
char *duplicate_chars(char *pathstr, int start, int stop)
{
	int a = 0, y;
	static char buf[1024];

	for (y = 0, a = start; a < stop; a++)
	{
		if (pathstr[a] != ':')
		{
			buf[y++] = pathstr[a];
		}
	}
	buf[y]  = 0;
	return (buf);
}

/**
 * find_route - a function that checks the route
 * @info: information
 * @pathstr: path of string
 * @cmd: command
 * Return: path
 */
char *find_route(info_t *info, char *pathstr, char *cmd)
{
	char *path;
	int a = 0, r = 0;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = duplicate_chars(pathstr, r, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}

			if (is_cmd(info, path))
				return (path);
			if (!pathstr[a])
				break;
			r = a;
		}
		a++;
	}
	return (NULL);
}

