#include "shell.h"

/**
 * get_environ - Returns a copy of the environment variables as an array of strings.
 * @info: Structure containing the environment variables.
 *		  Used to maintain constant function prototype.
 * Return: The environment variables as an array of strings.
 */

char **get_environ(info_s *info)
{
	/* If the environment variables have not been set or have been changed, update them. */
	if (!info->envirom || info->env_changed)
	{
		info->envirom = list_to_vector(info->env);
		info->env_changed = 0;
	}
	return (info->envirom);
}
/**
 * _printenv - prints the current environment
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 * Return: Always 0
 */
int _printenv(info_s *info)
{
	print_list_str(info->env);
	return (0);
}
/**
 * handle_exit - exits the shell
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */

int handle_exit(info_s *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = err_num(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			puts_err(info->argv[1]);
			putchar_err('\n');
			return (1);
		}
		info->error_code = err_num(info->argv[1]);
		return (-2);
	}
	info->error_code = -1;
	return (-2);
}
/**
 * err_num - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string,
 * converted integer else -1
 *
 */
int err_num(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
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
}/**
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
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
    }
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
		free_vector(info->envirom);
		info->envirom = NULL;
		if (info->fd_read > 2)
			close(info->fd_read);
		_putchar(NEG_ONE);
	}
    
}
/**
 * from_terminal - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if from_terminal mode else 0
 */

int from_terminal(info_s *info)
{
	return (isatty(STDIN_FILENO) && info->fd_read <= 2);
}
/**
 * is_delimiter - checks if a character is a delimiter
 * @c: Character to be checked.
 * @delimiters: String of charaters to be compated.
 *
 * This function compares a character to one or more of delimiters
 * to see if the character matches any of the delimiters.
 *
 * Return: True if it is a delimiter, else false.
 */

bool is_delimiter(char c, char *delimiters)
{
	int s;

	for (s = 0; delimiters[s]; s++)
		if (c == delimiters[s])
			return (true);
	return (false);
}

