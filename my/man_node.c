#include "main.h"
/**
 * start_node - returns node whose string starts with prefix.
 * @nod: pointer to list head
 * @prefix: string to check.
 * @c: the next character after prefix to check.
 *
 * Return: match node or null
 */

node *start_node(node *nod, char *prefix, char c)
{
	char *p = NULL;

	while (nod)
	{
		p = begin(nod->ptr, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (nod);
		nod = nod->next;
	}
	return (NULL);
}
/**
 * length- gets the length of linked list.
 * @h: Pointer to first node.
 *
 * Return: Size of list.
 */
size_t length(const node *f)
{
	size_t g = 0;

	while (f)
	{
		f = f->next;
		g++;
	}
	return (g);
}

/**
 * vector_display - returns an array of strings of the list->str
 * @first: pointer to first node
 *
 * Return: Array of strings.
 */

char **vector_display(node *first)
{
	node *nod = first;
	size_t w, j;
	char **var;
	char *str;

	w = length(first);
	if (!first || !w)
		return (NULL);
	var = malloc(sizeof(char *) * (w + 1));

	if (!var)
		return (NULL);
	for (w = 0; nod; nod = nod->next, w++)
	{
		str = malloc(_strlen(nod->ptr) + 1);
		if (!str)
		{
			for (j = 0; j < w; j++)
				free(var[j]);
			free(var);
			return (NULL);
		}
		str = (char*)_strcpy(str, nod->ptr);
		var[w] = str;
	}
	var[w] = NULL;
	return (var);
}