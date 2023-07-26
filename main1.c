#include "shell.h"
/**
 * main - a function that shows where function starts
 * @argc: arguement count
 * @argv: arguement vector of dimensional arrays
 * Return: 0 or 1
 */
int main(int argc, char **argv)
{
	int f = 2;
	info_t info = INFO_INIT;

	__asm__("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (f)
			: "r" (f));
	if (argc == 2)
	{
		f = open(argv[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info.readfd = f;
	}
	populate_env_list(&info);
	read_history(&info);
	hsh(&info, argv);
	return (EXIT_SUCCESS);
}

