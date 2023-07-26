#include "main.h"
/**
 * other_alias - replaces an aliases in the tokenized string
 * @arr: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int other_alias(data *arr)
{
	int i;
	node *nod;
	char *p;

	for (i = 0; i < 10; i++)
	{
		nod = start_node(arr->alias, arr->av[0], '=');
		if (!nod)
			return (0);
		free(arr->av[0]);
		p = _strchr(nod->ptr, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		arr->av[0] = p;
	}

	return (1);
}
/**
 * var_handle - replaces vars in the tokenized string
 * @arr: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int var_handle(data *arr)
{
	int i = 0;
	node  *nod;

	for (i = 0; arr->av[i]; i++)
	{
		if (arr->av[i][0] != '$' || !arr->av[i][1])
			continue;
		if (!_strcmp(arr->av[i], "$?"))
		{
			string_replace(&(arr->av[i]), _strdup(base_convert(arr->status, 10, 0)));
			continue;
		}
		if (!_strcmp(arr->av[i], "$$"))
		{
			string_replace(&(arr->av[i]), _strdup(base_convert(getpid(), 10, 0)));
			continue;
		}
		nod = start_node(arr->env, &arr->av[i][1], '=');
		if (nod)
		{
			string_replace(&(arr->av[i]), _strdup(_strchr(nod->ptr, '=') + 1));
			continue;
		}
		string_replace(&arr->av[i], _strdup(""));
	}
	return (0);
}