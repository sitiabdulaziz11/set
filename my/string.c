#include "main.h"
/**
 *  _strlen - return the length of string.
 * @s: coming string.
 *
 * Return: len
 */
int _strlen(char *s)
{
	int r;

	r = 0;
	while (s[r] != '\0')
	{
		r++;
	}
	return (r);
}

/**
 * _strcpy - copies string source (src) to destination (des).
 * @dest: destination
 * @src: source
 *
 * Return: dest
 */
char *_strcpy(char *dest, char *src)
{
	int k;
	int b;

	k = 0;
	b = 0;
	while (src[b])
	{
		dest[k] = src[b];
		k++;
		b++;
	}
	dest[k] = '\0';
	return (dest);
}
/**
 * _strcat - To concatenate two string.
 * @dest: destination
 * @src: source
 *
 * Return: dest
 */
char *_strcat(char *dest, char *src)
{
	int i;
	int n;
	int k;

	for (k = 0; dest[k] != 0;)
		k++;
	i = 0;
	n = k;
	while (src[i])
	{
		dest[n] = src[i];
		n++;
		i++;
	}
	dest[n] = '\0';
	return (dest);
}
