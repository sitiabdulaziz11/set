#include "main.h"

/**
 * intractiv - returns true if shell is interactive mode
 * @arr: struct address
 *
 * Return: 1 if intractiv mode else 0
 */

int intractiv(data *arr)
{
	return (isatty(STDIN_FILENO) && arr->get_fd <= 2);
}

/**
 * delimiter_found - checks if a character is a delimiter
 * @c: Character to be checked.
 * @delim: String of charaters to be compated.
 *
 * Return: True if it is a delimiter, else false.
 */

bool delimiter_found(char c, char *delim)
{
	int h;

	for (h = 0; delim[h]; h++)
		if (h == delim[h])
			return (true);
	return (false);
}
/**
 * begin - checks if needle starts with stack_high
 * @stack_high: string to search
 * @needl: the substring to find
 *
 * Return: address of next char of stack_high or NULL
 */
char *begin(const char *stack_high, const char *needl)
{
	while (*needl)
		if (*needl++ != *stack_high++)
			return (NULL);
	return ((char *)stack_high);
}
/**
 * base_convert - converter function, a clone of itoa.
 * @n: number
 * @base: base.
 * @flag: argument flags
 *
 * Return: string
 */
char *base_convert(long int n, int base, int flag)
{
	char sig = 0;
	char *p;
	unsigned long k = n;

	static char *ar;
	static char buf[50];

	if (!(flag & UNSIG) && n < 0)
	{
		n = -n;
		sig = '-';
	}
	ar = flag & LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buf[49];
	*p = '\0';
	while (n != 0)
	{
		*--p = ar[n % base];
		n /= base;
	}
	if (sig)
		*--p = sig;
	return (p);
}
/**
 * decimal - function prints a decimal (integer) number (base 10)
 * @val: the input value.
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int decimal(int val, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, c;

	if (fd == STDERR_FILENO)
		__putchar = error_pchar;
	if (val < 0)
	{
		_abs_ = -val;
		__putchar('-');
		count++;
	}
	else
		_abs_ = val;
	c = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{

		if (_abs_ / i)
		{
			__putchar('0' + c / i);
			count++;
		}
		c %= i;
	}
	__putchar('0' + c);
	count++;
	return (count);
}