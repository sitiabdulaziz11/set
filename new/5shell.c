#include "shell.h"

/**
 * check_file_in_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *check_file_in_path(info_s *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_executable(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_executable(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_s *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->sep_buff);*/
		free(*buf);
		*buf = NULL;
		
/*#if USE_GETLINE*/
		r = getline(buf, &len_p, stdin);
/*#else
		r = _getline(info, buf, &len_p);
#endif*/
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->lc_flag = 1;
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->sep_buff = buf;
			}
		}
	}
	return (r);
}
/**
 * print_list_str - prints only the str element of a list_s linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_s *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}
/**
 * free_vector - frees memory allocated to a 2D character array
 * @vec: Vector to be freed.
 *
 * Return: Nothing.
 */

void free_vector(char **vec)
{
	char **ptr = vec;

	if (!vec)
		return;
	while (*vec)
		free(*vec++);

	free(ptr);
}/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_s **head_ptr)
{
	list_s *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
/**
 * gather_env - populates env linked list
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 * Return: Always 0
 */
 
int gather_env(info_s *info)
{
	list_s *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_s *add_node_end(list_s **head, const char *str, int num)
{
	list_s *new_node, *node;
	
	if (!head)
		return (NULL);
	
	node = *head;
	new_node = malloc(sizeof(list_s));
	if (!new_node)
		return (NULL);
	
	_memset((void *)new_node, 0, sizeof(list_s));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 *
 * Return: s- a pointer to the memory area of s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;
	
	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}