#include "main.h"

/**
 * take_environ - Returns a copy of the environment variables.
 * @arr: Structure containing the environment variables.
 * 
 * Return: The environment variablesas an array of strings .
 */
const char *const *take_environ(data *arr)
{
	if (!arr->envrmt || arr->rep_env)
	{
		arr->envrmt = vector_display(arr->env);
		arr->rep_env = 0;
	}
	return ((const char *const *)arr->envrmt);
}

/**
 * adjustenv - Adds or updates an environment variable.
 * @arr: Structure containing the environment variables.
 * 
 * @var: The name of the environment variable to add.
 * @value: The value of the environment variable to add or update.
 * 
 * Return: 0 if the environment variable was successful or updated, else 1.
 */

int adjustenv(data *arr, char *var, char *value)
{
	char *buff = NULL;
	node *nod;
	char *p;

	if (!var || !value)
		return (1);


	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);

	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);

	nod = arr->env;
	while (nod)
	{
		p = begin(nod->ptr, var);
		if (p && *p == '=')
		{
			free(nod->ptr);
			nod->ptr = buff;
			arr->rep_env = 1;
			return (0);
		}
		nod = nod->next;
	}
	append_node_end(&(arr->env), buff, 0);
	free(buff);
	arr->rep_env = 1;
	return (0);
}

/**
 * notsetenv - Removes an environment variable.
 * @arr: Structure containing the environment variables.
 * @var: The name of the environment variable to be remove.
 * Return: 1 if the environment variable was successfull removed, else 0.
 */
int notsetenv(data *arr, char *var)
{
	node *nod = arr->env;
	size_t ind = 0;
	char *k;

	if (!nod || !var)
		return (0);

	while (nod)
	{
		k = begin(nod->ptr, var);
		if (k && *k == '=')
		{
			arr->rep_env = removenode_nindex(&(arr->env), ind);
			
			ind = 0;
			nod = arr->env;
			continue;
		}
		nod = nod->next;
		ind++;
	}

	return (arr->rep_env);
}
