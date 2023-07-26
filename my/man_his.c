#include "main.h"

/**
 * take_history - gets the history file.
 * @arr: parameter struct.
 *
 * Return: allocated string containg history file.
 */

char *take_history(data *arr)
{
	char *buff, *fol;

	fol = value_env(arr, "HOME=");
	if (!fol)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(fol) + _strlen(H_NAME) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, fol);
	_strcat(buff, "/");
	_strcat(buff, H_NAME);
	return (buff);
}

/**
 * history_creation - creates a file, or appends to an existing file.
 * @arr: the parameter struct.
 *
 * Return: 1 on success, else -1.
 */
int history_creation(data *arr)
{
	ssize_t fd;
	char *fn;
	node *nod = NULL;

	fn = take_history(arr);
	if (!fn)
		return (-1);

	fd = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (fd == -1)
		return (-1);
	for (nod = arr->history; nod; nod = nod->next)
	{
		string_display(nod->ptr, fd);
		char_display('\n', fd);
	}
	char_display(NEGATIV, fd);
	close(fd);
	return (1);
}
/**
 * take_history - adds entry to a history linked list
 * @arr: contains simulated arguments for a function pointer,
 * @buf: buffe
 * @linecount: the history linecount, hlines
 *
 * Return: Always 0
 */
int new_history(data *arr, char *buf, int linecount)
{
	node *nod = NULL;

	if (arr->history)
		nod = arr->history;
	append_node_end(&nod, buf, linecount);

	if (!arr->history)
		arr->history = nod;
	return (0);
}
/**
 * comment_place - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: 0;
 */

void comment_place(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}