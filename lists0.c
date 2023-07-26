#include "shell.h"

/**
 * add_node - a function that add a node
 * @head: first node
 * @str: string
 * @num: number
 * Return: added node
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *curr_head;

	if (!head)
		return (NULL);
	curr_head = malloc(sizeof(list_t));
	if (!curr_head)
		return (NULL);
	_setmem((void *)curr_head, 0, sizeof(list_t));
	curr_head->num = num;
	if (str)
	{
		curr_head->str = _strdup(str);
		if (!curr_head->str)
		{
			free(curr_head);
			return (NULL);
		}
	}
	curr_head->next = *head;
	*head = curr_head;

	return (curr_head);

}

/**
 * add_node_end - a function that adds a node at the end of list
 * @head: first node
 * @str: string
 * @num: number
 * Return: node at end
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *node, *new_node;

	if (!head)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_setmem((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		for (; node->next; node = node->next)
			;
		node->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}
/**
 * print_ls_string - a function that prints a string
 * @h: pointer
 * Return: string
 */
size_t print_ls_string(const list_t *h)
{
	size_t a;

	for (a = 0; h; h = h->next)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		a++;
	}
	return (a);
}

/**
 * delete_node_at_index - a function that deletes a node at index
 * @head: first node
 * @index: position of node
 * Return: node
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	unsigned int a = 0;
	list_t *node, *prev_node;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	for (a = 0, node = *head; node; a++, prev_node = node, node = node->next)
	{
		if (a == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
	}
	return (0);

}

/**
 * free_list - a function that frees list
 * @head_ptr: head pointer
 * Return: freed list
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head = *head_ptr;

	if (!head_ptr || !*head_ptr)
		return;
	for (node = head; node; node = next_node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
	}
	*head_ptr = NULL;
}

