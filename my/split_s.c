#include "main.h"

/**
 * **_strtok - splits a string into words. Repeat delimiters are ignored
 * @ptr: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **_strtok(char *ptr, char *d)
{
	int i, j, k, m, wnum = 0;
	char **p;

	if (ptr == NULL || ptr[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; ptr[i] != '\0'; i++)
		if (!delimiter_found(ptr[i], d) && (delimiter_found(ptr[i + 1], d) || !ptr[i + 1]))
			wnum++;
	if (wnum == 0)
		return (NULL);
	p = malloc((1 + wnum) * sizeof(char *));
	if (!p)
		return (NULL);
	for (i = 0, j = 0; j < wnum; j++)
	{
		while (delimiter_found(ptr[i], d))
			i++;
		k = 0;
		while (!delimiter_found(ptr[i + k], d) && ptr[i + k])
			k++;
		p[j] = malloc((k + 1) * sizeof(char));
		if (!p[j])
		{
			for (k = 0; k < j; k++)
				free(p[k]);
			free(p);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			p[j][m] = ptr[i++];
		p[j][m] = 0;
	}
	p[j] = NULL;
	return (p);
}

/**
 * display_ptr - prints only the str element of a list_s linked list
 * @f: pointer to first node
 *
 * Return: size of list
 */
size_t display_ptr(const node *f)
{
	size_t n = 0;

	while (f)
	{
		_puts(f->ptr ? f->ptr : "(nil)");
		_puts("\n");
		f = f->next;
		n++;
	}
	return (n);
}