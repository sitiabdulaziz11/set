#include "main.h"
/**
 *node_frre - frees all nodes of a list
 * @ptr_h: address of pointer to head node
 *
 * Return: void
 */
void node_frre(node **ptr_h)
{
	node *nod, *next_node, *head;

	if (!ptr_h || !*ptr_h)
		return;
	head = *ptr_h;
	nod = head;
	while (nod)
	{
		next_node = nod->next;
		free(nod->ptr);
		free(nod);
		nod = next_node;
	}
	*ptr_h = NULL;
}
/**
 * append_node_end - adds a node to the end of the list
 * @h: address of pointer to head node
 * @ptr: str field of node
 * @n: node index used by history
 *
 * Return: size of list
 */
node *append_node_end(node **h, const char *ptr, int value)
{
	node *nnode, *nod;

	if (!h)
		return (NULL);

	nod = *h;
	nnode = malloc(sizeof(node));
	if (!nnode)
		return (NULL);
	_memset((void *)nnode, 0, sizeof(node));
	nnode->value= value;
	if (ptr)
	{
		nnode->ptr = _strdup(ptr);
		if (!nnode->ptr)
		{
			free(nnode);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->next)
			nod = nod->next;
		nod->next = nnode;
	}
	else
		*h = nnode;
	return (nnode);
}

/**
 * removenode_nindex- deletes node at given index.
 * @first : address of pointer to first node
 * @ind: index of node to delete
 *
 * Return: 1 on success, 0 on failure.
 */
int removenode_nindex(node **first, unsigned int ind)
{
	node *nod, *old;
	unsigned int k = 0;

	if (!first || !*first )
		return (0);

	if (!ind)
	{
		nod = *first ;
		*first  = (*first )->next;
		free(nod->ptr);
		free(nod);
		return (1);
	}
	nod = *first ;
	while (nod)
	{
		if (k == ind)
		{
			old->next = nod->next;
			free(nod->ptr);
			free(nod);
			return (1);
		}
		k++;
		old = nod;
		nod = nod->next;
	}
	return (0);
}
