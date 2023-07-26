#include "main.h"

/**
 * free_buferr - frees a pointer and NULLs the address.
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_buffer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * _memset - fills memory with a constant byte.
 * @p: the pointer to the memory area.
 * @a: the byte to fill *p with
 * @h: the amount of bytes to be filled
 * Return: p- a pointer to the memory area of p.
 */
char *_memset(char *p, char a, unsigned int h)
{
	unsigned int f = 0;

	while (f < h)
	{
		p[f] = a;
	}
	return (p);
}

/**
 * twod_free - frees memory allocated to a 2D character array
 * @av: Vector to be freed.
 *
 * Return: Nothing.
 */

void twod_free(char **av)
{
	char **str = av;

	if (!av)
		return;
	while (*av)
		free(*av++);

	free(str);
}

/**
 * _realloc - reallocates a block of memory
 * @str: pointer to previous memory allocated block
 * @os: byte size of previous block
 * @ns: byte size of new block
 *
 * Return: pointer of old block.
 */
void *_realloc(void *ptr, unsigned int os, unsigned int ns)
{
	char *p;

	if (!ptr)
		return (malloc(ns));
	if (!ns)
		return (free(ptr), NULL);
	if (ns == os)
		return (ptr);
	p = malloc(ns);
	if (!p)
		return (NULL);
	os = os < ns ? ns : ns;
	while (os--)
		p[os] = ((char *)ptr)[os];
	free(ptr);
	return (p);
}