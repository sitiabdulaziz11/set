#include "main.h"

/**
 * accept_array - array chained commands.
 * @arr: parameter struct
 * @buf: address of buffer
 * @l: address of len var
 *
 * Return: bytes read
 */
ssize_t accept_array(data *arr, char **buf, size_t *l)
{
	ssize_t t = 0;
	size_t p = 0;

	if (!*l) 
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, interrupt_sigint);
		if (GETLINE)
		{
			t = getline(buf, &p, stdin);
		}
		else
		{
			t = _getline(arr, buf, &p);
		}
		if (t > 0)
		{
			if ((*buf)[t - 1] == '\n')
			{
				(*buf)[t - 1] = '\0'; /* remove trailing newline */
				t--;
			}
			arr->flag = 1;
			comment_place(*buf);
			new_history(arr, *buf, arr->hline++); 
			{
				*l = t;
				arr->buff = buf;
			}
		}
	}
	return (t);
}

/**
 * accept_data - gets a lines.
 * @arr: parameter struct
 *
 * Return: bytes read
 */
ssize_t accept_data(data *arr)
{
	static char *buf; 
	static size_t i, j, lent;
	ssize_t z = 0;
	char **buff, *p;

	buff = &(arr->arg);
	_putchar(NEGATIV);
	z = accept_array(arr, &buf, &lent);
	if (z == -1)
		return (-1);
	if (lent) 
	{
		j = i;		 
		p = buf + i; 

		filter_connection(arr, buf, &j, i, lent);
		while (j < lent) 
		{
			if (connected(arr, buf, &j))
				break;
			j++;
		}
		i = j + 1;	  
		if (i >= lent) 
		{
			i = lent = 0; 
			arr->buff_type = FLAG;
		}
		*buff = p;			 
		return (_strlen(p)); 
	}
	*buff = buf;
	return (z);	 
}

/**
 * take_buf - reads a buffer
 * @arr: parameter struct
 * @buf: buffer
 * @m: size
 *
 * Return: r
 */
ssize_t take_buf(data *arr, char *buf, size_t *m)
{
	ssize_t r = 0;

	if (*m)
		return (0);
	r = read(arr->get_fd, buf, BUF_READ);
	if (r >= 0)
		*m = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @arr: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @l: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(data *arr, char **ptr, size_t *l)
{
	static char buf[BUF_READ];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *np = NULL, *c;

	p = *ptr;
	if (p && l)
		s = *l;
	if (i == len)
		i = len = 0;

	r = take_buf(arr, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	if (c)
		k = 1 + (unsigned int)(c - buf);
	else
		k = len;
	np = _realloc(p, s, s ? s + k : k + 1);
	if (!np)
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(np, buf + i, k - i);
	else
		_strncpy(np, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = np;

	if (l)
		*l = s;
	*ptr = p;
	return (s);
}

/**
 * interrupt_sigint - handle ctrl-C
 * @num: the signal number
 *
 * Return: void
 */
void interrupt_sigint(int num)
{
	(void)num;
	_puts("\n");
	_puts("$ ");
	_putchar(NEGATIV);
}
