#include "shell.h"
/**
 * hsh - a function that checks for shell loop
 * @info: information
 * @av: arguemnt vector
 * Return: 1 or 0
 */
int hsh(info_t *info, char **av)
{
	ssize_t x = 0;
	int y = 0;

	while (x != -1 && y != -2)
	{
		clear_data(info);
		if (interact(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		x = get_input(info);
		if (x != -1)
		{
			set_data(info, av);
			y = find_builtin(info);
			if (y == -1)
				find_cmd(info);
		}
		else if (interact(info))
			_putchar('\n');
		free_data(info, 1);

	}
	write_history(info);
	free_data(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (y == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (y);
}
/**
 * find_builtin - a function that checks for builtin
 * @info: information
 * Return: builtin command
 */
int find_builtin(info_t *info)
{
	int a = 0, y = -1;
	builtin_table builtintbl[] = {
		{"exit", _myquit},
		{"env", _myenvironment},
		{"help", _myassist},
		{"history", _myprev},
		{"setenv", _mysetenviron},
		{"unsetenv", _myunsetenviron},
		{"cd", _mycdir},
		{"alias", _myalias},
		{NULL, NULL}
	};
	while (builtintbl[a].type)
	{
		if (_strcmp(info->argv[0], builtintbl[a].type) == 0)
		{
			info->line_count++;
			y = builtintbl[a].func(info);
			break;
		}
		a++;
	}
	return (y);

}
/**
 * find_cmd - a function that checks the commands
 * @info: information
 * Return: command
 */
void find_cmd(info_t *info)
{
	int a = 0, m = 0;
	char *path = NULL;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	while (info->arg[a])
	{
		if (!is_delimeter(info->arg[a], "\t\n"))
			m++;
		a++;
	}
	if (!m)
		return;
	path = find_route(info, _getenviron(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interact(info) || _getenviron(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_err(info, "not found\n");
		}
	}
}
/**
 * fork_cmd - a function that forks a command
 * @info: information
 * Return: commands
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");/*Error code*/
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_data(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_err(info, "Permission denied\n");
		}
	}

}

