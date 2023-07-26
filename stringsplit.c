#include "shell.h"

/**
 * strtow - a function that splits strings
 * @str: string
 * @d: delimeter
 * Return: split string
 */
char **strtow(char *str, char *d)
{
	char **g;
	int a, b, c, f, s_word = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delimeter(str[a], d) && (is_delimeter(str[a + 1], d) || !str[a + 1]))
			s_word++;
	if (s_word == 0)
		return (NULL);
	g = malloc((1 + s_word) * sizeof(char *));
	if (!g)
		return (NULL);
	for (a = 0, b = 0; b < s_word; b++)
	{
		for (; is_delimeter(str[a], d); a++)
			;
		for (c = 0; !is_delimeter(str[a + c], d) && str[a + c]; c++)
			;
		g[b] = malloc((c + 1) * sizeof(char));
		if (!g[b])
		{
			c = 0;
			while (c < b)
			{
				free(g[c]);
				c++;
			}
			free(g);
			return (NULL);
		}
		for (f = 0; f < c; f++)
			g[b][f] = str[a++];
		g[b][f] = 0;
	}
	g[b] = NULL;
	return (g);
}

/**
 * strtow2 - a function that splits strings
 * @str: string
 * @d: delimiter
 * Return: split string
 */
char **strtow2(char *str, char d)
{
	int a, b, c, f, s_word = 0;
	char **g;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				(str[a] != d && !str[a + 1]) || str[a + 1] == d)
			s_word++;
	if (s_word == 0)
		return (NULL);
	g = malloc((1 + s_word) * sizeof(char *));
	if (!g)
		return (NULL);
	for (a = 0, b = 0; b < s_word; b++)
	{
		for (a = 0; str[a] == d && str[a] != d; a++)
			;
		for (c = 0; str[a + c] != d && str[a + c] && str[a + c] != d; c++)
			;
		g[b] = malloc((c + 1) * sizeof(char));
		if (!g[b])
		{
			for (c = 0; c < b; c++)
				free(g[c]);
			free(g);
			return (NULL);
		}
		f = 0;
		while (f < c)
		{
			g[b][f] = str[a++];
			f++;
		}
		g[b][f] = 0;
	}
	g[b] = (NULL);
	return (g);
}

