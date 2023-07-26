#include "main.h"

/**
 * start_shell - main control for the shell progra.
 * @arr: pointer to an data struct containing shell information
 * @av: array of strings containing arguments to the shell
 *
 * Return: the status of the last executed builtin command
 */
int start_shell(data *arr, char **av)
{
	ssize_t input_result = 0;
	int value_from_builtin = 0;

	while (input_result != -1 && value_from_builtin != -2)
	{
		data_remove(arr);

		
		if (intractiv(arr))
			_puts("$ ");

		error_pchar(NEGATIV);
		input_result = accept_data(arr);

		if (input_result != -1)
		{
			data_set(arr, av);
			value_from_builtin = builtin_commands(arr);

			if (value_from_builtin == -1)
				test_cmd(arr);
		}
		else if (intractiv(arr))
			_putchar('\n');

		data_free(arr, 0);
	}

	history_creation(arr);

	/* Free memory and exit */
	data_free(arr, 1);
	if (!intractiv(arr) && arr->status)
		exit(arr->status);

	/* Handle exit with error */
	if (value_from_builtin == -2)
	{
		if (arr->code_err == -1)
			exit(arr->status);
		exit(arr->code_err);
	}

	return (value_from_builtin);
}

/**
 * builtin_commands - finds a builtin commands.
 * @arr: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if  successfull,
 * 1 if  not successful,
 * 2 if builtin signals exit().
 */
int builtin_commands(data *arr)
{
	int i, value_from_builtin = -1;

	bult_cmd bult[] = {
		{"cd", cd_fun},
		{"env", displayenv_fun},
		{"exit", exit_fun},
		{"help", help_fun},
		{"setenv", test_setenv},
		{"history", history_fun},
		{"notsetenv", test_notsetenv},
		{NULL, NULL}
		};

	for (i = 0; bult[i].cmd; i++)
		if (_strcmp(arr->av[0], bult[i].cmd) == 0)
		{
			arr->line++;
			value_from_builtin = bult[i].fun(arr);
			break;
		}
	return (value_from_builtin);
}

/**
 * test_cmd - searches for a command in PATH or the current directory
 * @arr: a pointer to the parameter and return info struct
 *
 * Return: void
 */
void test_cmd(data *arr)
{
	char *pth = NULL;
	int t, wcount;

 arr->path = arr->av[0];
	if (arr->flag == 1)
	{
		arr->line++;
		arr->flag = 0;
	}

	for (t = 0, wcount = 0; arr->arg[t]; t++)
		if (!delimiter_found(arr->arg[t], " \t\n"))
			wcount++;

	if (!wcount)
		return;

	pth = test_filepath(arr, value_env(arr, "PATH="), arr->av[0]);
	if (pth)
	{
		arr->path = pth;
		process_makings(arr);
	}
	else
	{
		if ((intractiv(arr) || value_env(arr, "PATH=") || arr->av[0][0] == '/') && executable_file(arr, arr->av[0]))
			process_makings(arr);
		else if (*(arr->arg) != '\n')
		{
			arr->status = 127;
			error_display(arr, "not found\n");
		}
	}
}

/**
 * process_making - forks a new process to run the command.
 * @arr: pointer to the parameter & return arr struct.
 * 
 * Return: void
 */
void process_makings(data *arr)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return;
	}
	if (pid == 0)
	{
		const char *const *exec_arg;

		exec_arg = (const char *const *)arr->av;
		if (execve(arr->path, exec_arg, take_environ(arr)) == -1)
		{
			data_free(arr, 1);
				if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(arr->status));
		if (WIFEXITED(arr->status))
		{
			arr->status = WEXITSTATUS(arr->status);

			/* Print error message for permission denied errors */
			if (arr->status == 126)
				error_display(arr, "Permission denied\n");
		}
	}
}
