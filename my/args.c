#include "main.h"

/**
 * executable_file - determines if a file is an executable command
 * @arr: the info struct
 * @pth: path to the file
 *
 * Return: 1 if true, 0 otherwise.
 */
bool executable_file(data *arr, char *pth)
{
	struct stat sr;

	(void)arr;
	if (!pth || stat(pth, &sr) != 0)
		return (0);

	if (S_ISREG(sr.st_mode))
	{
		return (true);
	}
	return (false);
}
/**
 * test_filepath - finds this cmd in the PATH string.
 * @arr: the info struct
 * @pstr: the PATH string
 * @cmd: the cmd to find.
 *
 * Return: full path of cmd if found or NULL.
 */
char *test_filepath(data *arr, char *pstr, char *cmd)
{
	int f = 0, h = 0;
	char *path;

	if (!pstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && begin(cmd, "./"))
	{
		if (executable_file(arr, cmd))
			return (cmd);
	}
	while (2)
	{
		if (!pstr[f] || pstr[f] == ':')
		{
			path = mult_chars(pstr, h, f);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (executable_file(arr, path))
				return (path);
			if (!pstr[f])
				break;
			h = f;
		}
		f++;
	}
	return (NULL);
}
