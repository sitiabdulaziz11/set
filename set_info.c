#include "shell.h"

/**
 * set_info - initializes info_s struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_s *info, char **av)
{
	int i = 0;

	info->prog_name = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2 + 1);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		else
		{
			for (i = 0; info->argv && info->argv[i]; i++)
			;
		}
		info->argc = i;
    }
}
/**
 * clear_info - initializes info_s struct
 * @info: struct address
 */
void clear_info(info_s *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * free_info - frees info_s struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_s *info, int all)
{
	free_vector(info->argv);
	info->argv = NULL;
	info->path = NULL;
    
	if (all)
	{
		if (info->env)
			free_list(&(info->env));
		free_vector(info->environ);
		info->environ = NULL;
		if (info->fd_read > 2)
			close(info->fd_read);
		_putchar(NEG_ONE);
	}
    
}
