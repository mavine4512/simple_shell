#include "shell.h"
/**
 * get_history_file - a function that gets history file
 * @info: information
 * Return: history file
 */
char *get_history_file(info_t *info)
{
	char *b, *d;

	d = _getenviron(info, "HOME=");
	if (!d)
		return (NULL);
	b = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
	if (!b)
		return (NULL);
	b[0] = 0;
	_strcpy(b, d);
	_strcat(b, "/");
	_strcat(b, HIST_FILE);
	return (b);
}
/**
 * write_history - A function that writes the history
 * @info: information
 * Return: written history
 */
int write_history(info_t *info)
{
	list_t *node = NULL;
	ssize_t d;
	char *fname = get_history_file(info);

	if (!fname)
		return (-1);/*checking filename*/
	d = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (d == -1)
		return (-1);
	node = info->history;
	while (node != NULL)
	{
		_putsfd(node->str, d);
		_putfd('\n', d);
		node = node->next;
	}
	_putfd(BUF_FLUSH, d);
	close(d);
	return (1);
}
/**
 * read_history - a function that reads the history
 * @info: information
 * Return: history
 */
int read_history(info_t *info)
{
	char  *buffer = NULL, *fname = get_history_file(info);
	ssize_t d, dlen, filesize = 0;
	int a, end = 0, linenumber = 0;
	struct stat st;

	if (!fname)
		return (0);
	d = open(fname, O_RDONLY);
	free(fname);
	if (d == -1)
		return (0);
	if  (!fstat(d, &st))
		filesize = st.st_size;
	if (filesize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (filesize + 1));
	if (!buffer)
		return (0);
	dlen = read(d, buffer, filesize);
	buffer[filesize] = 0;
	if (dlen <= 0)
		return (free(buffer), 0);
	close(d);
	for (a = 0; a < filesize; a++)
	{
		if (buffer[a] == '\n')
		{
			buffer[a] = 0;
			build_history_list(info, buffer + end, linenumber++);
			end = a + 1;
		}
	}
	if (end != a)
		build_history_list(info, buffer + end, linenumber++);
	free(buffer);
	info->histcount = linenumber;
	for (; info->histcount >= HIST_MAX; info->histcount--)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}
/**
 * build_history_list - a function that bulds history
 * @info: information
 * @buf: buffer
 * @linecount: count of the lines
 * Return: history list
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}
/**
 * renumber_history - a function that renumbers history
 * @info: information
 * Return: renumbered history
 */
int renumber_history(info_t *info)
{
	int a = 0;
	list_t *node;

	node = info->history;

	while (node)
	{
		node->num = a;
		node = node->next;
		a++;
	}
	info->histcount = a;
	return (a);
}

