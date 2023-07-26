#include "main.h"
/**
 * _puts - print string
 * @str: recevied string.
 */
void _puts(char *str)
{
	int y;

	for (y = 0; str[y] != '\0'; y++)
	{
		_putchar(str[y]);
	}
	_putchar('\n');
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * number_of_err - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string.
 *
 */
int number_of_err(const char *s)
{
    int result = 0;
    bool is_negative = false; 

    while (*s == ' ' || *s == '\t')
        s++;

    if (*s == '-')
    {
        is_negative = true;
        s++;
    }
    else if (*s == '+')
    {
        s++;
    }

    for (; *s != '\0'; s++)
    {
        if (*s >= '0' && *s <= '9')
        {
            if (result > (INT_MAX - (*s - '0')) / 10)
                return (is_negative ? INT_MIN : INT_MAX);

            result = result * 10 + (*s - '0');
        }
        else
        {
            return (-1);
        }
    }
    return (is_negative ? -result : result);
}
