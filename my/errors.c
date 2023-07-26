#include "main.h"
/**
 * print_error - prints an error message
 * @arr: the parameter & return info struct
 * @error: string containing specified error typ
 * 
 * Return: 0 if no numbers in string.
 */
void error_display(data *arr, char *error)
{
	show_error(arr->pname);
	show_error(": ");
	decimal(arr->line, STDERR_FILENO);
	show_error(": ");
	show_error(arr->av[0]);
	show_error(": ");
	show_error(error);
}
/**
 * show_error - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void show_error(char *str)
{
	int o = 0;

	if (!str)
		return;
	while (str[o] != '\0')
	{
		error_pchar(str[o]);
		o++;
	}
}
/**
 * error_pchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On failure, -1 is returned
 */
int error_pchar(char c)
{
	static int i;
	static char buf[BUF_WRITE];

	if (c == NEGATIV || i >= BUF_WRITE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != NEGATIV)
		buf[i++] = c;
	return (1);
}