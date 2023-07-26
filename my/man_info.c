#include "main.h"
/**
 * data_remove - remove datas to initializes the data struct.
 * @arr: struct address
 */
void data_remove(data *arr)
{
	arr->arg = NULL;
	arr->av = NULL;
	arr->path = NULL;
	arr->ac = 0;
}
/**
 * data_set - initializes data struct
 * @arr: struct address
 * @av: argument vector
 */
void data_set(data *arr, char **av)
{
	int i = 0;

	arr->pname = av[0];
	if (arr->arg)
	{
		arr->av = _strtok(arr->arg, " \n");
		if (!arr->av)
		{
			arr->av = malloc(sizeof(char *) * 2);
			if (arr->av)
			{
				arr->av[0] = _strdup(arr->arg);
				arr->av[1] = NULL;
			}
		}
		for (i = 0; arr->av && arr->av[i]; i++)
			;
		arr->ac = i;
		other_alias(arr);
		var_handle(arr);
	}
}
/**
 * data_free - frees info_s struct fields
 * @arr: struct address
 * @n: true if freeing all fields
 */
void data_free(data *arr, int n)
{
	twod_free(arr->av);
	arr->av = NULL;
	arr->path = NULL;
	if (n)
	{
		if (!arr->buff)
			free(arr->arg);
		if (arr->env)
			node_frre(&(arr->env));
		if (arr->history)
			node_frre(&(arr->history));
		if (arr->alias)
			node_frre(&(arr->alias));
		twod_free(arr->envrmt);
		arr->envrmt = NULL;
		free_buffer((void **)arr->buff);
		if (arr->get_fd > 2)
			close(arr->get_fd);
		_putchar(NEGATIV);
	}
}
