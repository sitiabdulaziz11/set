#include "main.h"
/**
 * connected - test if current char in buffer is a conneted.
 * @arr: the parameter struct
 * @buf: the char buffer
 * @g: address of current position in buf
 *
 * Return: 1 if connected else 0
 */
bool connected(data *arr, char *buf, size_t *g)
{
	size_t d = *g;

	if (buf[d] == '|' && buf[d + 1] == '|')
	{
		buf[d] = 0;
		d++;
		arr->buff_type = OR;
	}
	else if (buf[d] == '&' && buf[d + 1] == '&')
	{
		buf[d] = 0;
		d++;
		arr->buff_type= AND;
	}
	else if (buf[d] == ';')
	{
		buf[d] = 0;
		arr->buff_type = CHAIN;
	}
	else
		return (false);
	*g = d;
	return (true);
}

/**
 * filter_connection - checks we should continue chaining based on last status
 * @arr: the parameter struct.
 * @buf: the char buffer.
 * @p: address of current position in buf.
 * @i: starting position in buf.
 * @len: length of buf.
 *
 * Return: Void
 */
void filter_connection(data *arr, char *buf, size_t *s, size_t i, size_t len)
{
	size_t j = *s;

	if (arr->buff_type == AND)
	{
		if (arr->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (arr->buff_type == OR)
	{
		if (!arr->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*s = j;
}
/**
 * mult_chars - duplicates characters
 * @div: the PATH string
 * @beg: starting index
 * @end: stopping index
 *
 * Return: pointer to new buffer (caller is responsible for freeing the memory)
 */
char *mult_chars(const char *div, int beg, int end)
{
    int len, i, k;
	char *buf;
	
	len = end - beg;
    buf = malloc((len + 1) * sizeof(char));
    if (buf == NULL)
	{
        return NULL;
    }
    k = 0;
    for (i = beg; i < end; i++) {
        if (div[i] != ':') {
            buf[k++] = div[i];
        }
    }
    buf[k] = '\0';

    return buf;
}

/**
 * string_replace - replaces string
 * @o: address of old string
 * @n: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int string_replace(char **o, char *n)
{
	free(*o);
	*o = n;

	return (1);
}
