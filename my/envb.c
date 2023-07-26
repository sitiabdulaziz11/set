#include "main.h"

/**
 * value_env - gets the value of an environ variable.
 * @arr: contains simulated arguments for a function pointer.
 * @name: env var name.
 *
 * Return: the value.
 */

char *value_env(data *arr, const char *name)
{
	char *p;
	node *nod = arr->env;

	while (nod)
	{
		p = begin(nod->ptr, name);
		if (p&& *p)
			return (p);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * test_setenv - Checks if an environment variable has been set.
 * @arr: contains simulated arguments for a function pointer.
 * Return: 0 if set, else 1
 */
int test_setenv(data *arr)
{
	if (arr->ac != 3)
	{
		show_error("Incorrect number of arguements\n");
		return (1);
	}

	if (adjustenv(arr, arr->av[1], arr->av[2]))
		return (0);
	return (1);
}

/**
 * test_notsetenv - Remove an environment variable
 * @arr: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 * Return: Always 0
 */
int test_notsetenv(data *arr)
{
	int x;

	if (arr->ac == 1)
	{
		show_error("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= arr->ac; x++)
		notsetenv(arr, arr->av[x]);

	return (0);
}

/**
 * displayenv_fun - prints the current environment
 * @arr: contains simulated arguments for a function pointer.
 * Return: Always 0.
 */
int displayenv_fun(data *arr)
{
	display_ptr(arr->env);
	return (0);
}