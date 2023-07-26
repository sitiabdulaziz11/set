#include "main.h"

/**
 * main - Entry point to shell program
 * @ac: Number of arguments passed into the shell executable.
 * @av: Vector containing arguments passed.
 *
 * Return: 0 on success or 1 on failure.
 */
int main(int ac, char **av)
{
	data arr[] = {0, 0, 0, NULL, 0, \
	 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, };
	int fd = 2;

	fd += 3;
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);

			if (errno == ENOENT)
			{
				show_error(av[0]);
				show_error("Can't open ");
				show_error(av[1]);
				error_pchar('\n');
				error_pchar(NEGATIV);
				exit(127);
			}

			return (EXIT_FAILURE);
		}

		arr->get_fd = fd;
	}

	/*collect_env(arr);*/
	start_shell(arr, av);

	return (EXIT_SUCCESS);
}
