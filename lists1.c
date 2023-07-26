#include "shell.h"
/**
 * list_len - a function that lists length
 * @h: pointer to head
 * Return: length
 */
size_t list_len(const list_t *h)
{
	size_t a = 0;

	while (h != NULL)
	{
		h = h->next;
		a++;
	}
	return (a);
}
/**
 * list_to_strings - a function that lists strings
 * @head: first pointer
 * Return: string lists
 */
char **list_to_strings(list_t *head)
{
	size_t a = list_len(head), b = 0;
	char *str, **chr;
	list_t *node = head;

	if (!head || !a)
		return (NULL);
	chr = malloc(sizeof(char *) * (a + 1));
	if (!chr)
		return (NULL);

	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			while (b < a)
			{
				free(chr[b]);
				b++;
			}
			free(chr);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		chr[a] = str;
	}
	chr[a] = NULL;
	return (chr);
}
/**
 * print_list - a function that prints lists
 * @h: head pointer
 * Return: list
 */
size_t print_list(const list_t *h)
{
	size_t a = 0;

	for (a = 0; h != NULL; h = h->next, a++)
	{
		_puts(conv_no(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
	}
	return (a);
}
/**
 * node_starts_with - a function that shows where node begins from
 * @node: pointer
 * @prefix: tring before strings
 * @c: character
 * Return: node start
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *g = NULL;

	for (; node; node = node->next)
	{
		g = starts_with(node->str, prefix);
		if (g && ((c == -1) || (*g == c)))
			return (node);
	}
	return (NULL);
}
/**
 * get_node_index -  a function that gets node index
 * @head: pointer at head
 * @node: pointer
 * Return: 
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a;

	for (a = 0; head; head = head->next, a++)
	{
		if (head == node)
			return (a);
	}
	return (-1);
}

