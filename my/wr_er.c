#include "main.h"
/**
 * char_display - writes the character c to given fd.
 * @c: The character to print.
 * @fd: The filedescriptor to write to.
 *
 * Return: On success 1,
 * On failure, -1 is returned.
 */
int char_display(char d, int fd)
{
	static int z;
	static char buff[BUF_WRITE];

	if (d == NEGATIV || z >= BUF_WRITE)
	{
		write(fd, buff, z);
		z = 0;
	}
	if (d != NEGATIV)
		buff[z++] = d;
	return (1);
}
/**
 * string_display - prints an input string
 * @strr: the string to be printed
 * @fd: the filedescriptor to write to.
 *
 * Return: the number of chars put
 */
int string_display(char *strr, int fd)
{
	int y = 0;

	if (!strr)
		return (0);
	while (*strr)
	{
		y += char_display(*strr++, fd);
	}
	return (y);
}
