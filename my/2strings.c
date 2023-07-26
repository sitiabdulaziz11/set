#include "main.h"

/**
 * _strchr - search for a character.
 * @s: pointer or searched value
 * @c: search for
 * Return: s or null
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (*s == c)
		return (s);
	return ('\0');
}
/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int len = 0, l;
	char *result;

	while (str[l] != '\0')
		len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	for (len++; len--;)
		result[len] = *--str;
	return (result);
}
/**
 * _strncat - concatenate two string that use n bytes from src.
 * @dest: destination
 * @src: source
 * @n: number of bytes
 *
 * Return: dest.
 */
char *_strncat(char *dest, char *src, int n)
{
	int k;
	int q;

	q = 0;
	while (dest[q] != '\0')
		q++;
	k = 0;
	while (n > 0 && src[k] != '\0')
	{
		dest[q] = src[k];
		q++;
		k++;
		n--;
	}
	dest[q] = 0;
	return (dest);
}
/**
 * _strcmp - to compare two strings.
 * @s1: source
 * @s2: destination
 * Return: value
 */
int _strcmp(char *s1, char *s2)
{
	int t;

	t = 0;
	while (s1[t] == s2[t])
	{
		if (s1[t] == '\0' && s2[t] == '\0')
			break;
		t++;
	}
	return (s1[t] - s2[t]);
}
/**
 * _strncpy - copy strings
 * @dest: destination
 * @src: source
 * @n: number of char
 *
 * Return: dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int h;
	int r;

	h = 0;
	r = 0;
	while (n > 0 && src[h] != 0)
	{
		dest[r] = src[h];
		r++;
		h++;
		n--;
	}
	while (n > 0)
	{
		dest[r] = '\0';
		r++;
		n--;
	}
	return (dest);
}
