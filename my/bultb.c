#include "main.h"

/**
 * exit_fun - exits the shell.
 * @arr: contains simulated arguments for a function pointer.
 * Return: exits with a given exit status.
 */
int exit_fun(data *arr)
{
	int test;

	if (arr->av[1]) 
	{
		test = number_of_err(arr->av[1]);
		if (test == -1)
		{
			arr->status = 2;
			error_display(arr, "Illegal number: ");
			show_error(arr->av[1]);
			error_pchar('\n');
			return (1);
		}
		arr->code_err = number_of_err(arr->av[1]);
		return (-2);
	}
	arr->code_err = -1;
	return (-2);
}
/**
 * cd_fun - changes the current directory of the process.
 * @arr: contains simulated arguments for a function pointer.
 *
 * Return: 0
 */

int cd_fun(data *arr)
{
	char *v, *fol, buf[1024];
	int ret;

	v = getcwd(buf, 1024);
	if (!v)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!arr->av[1])
	{
		fol = value_env(arr, "HOME=");
		if (!fol)
			ret = chdir((fol = value_env(arr, "PWD=")) ? fol : "/");
		else
			ret = chdir(fol);
	}
	else if (_strcmp(arr->av[1], "-") == 0)
	{
		if (!value_env(arr, "OLDPWD="))
		{
			_puts(v);
			_putchar('\n');
			return (1);
		}
		_puts(value_env(arr, "OLDPWD=")), _putchar('\n');
		ret = chdir((fol = value_env(arr, "OLDPWD=")) ? fol : "/");
	}
	else
		ret = chdir(arr->av[1]);

	if (ret == -1)
	{
		error_display(arr, "can't cd to ");
		show_error(arr->av[1]), error_pchar('\n');
	}
	else
	{
		adjustenv(arr, "OLDPWD", value_env(arr, "PWD="));
		adjustenv(arr, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * help_fun - prints a message for aa function not implemented
 * @arr:	contains simulated arguments for a function pointer.
 * Return: 0
 */
int help_fun(data *arr)
{
	char **array;

	array = arr->av;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*array);

	return (0);
}
/**
 * history_fun - displays the history list, one command by line, preceded.
 * @arr: contains simulated arguments for a function pointer.
 *	Return: Always 0.
 */
int history_fun(data *arr)
{
	display_ptr(arr->history);
	return (0);
}