#include "shell.h"

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
 * get_environ - Returns a copy of the environment variables as an array of strings.
 * @info: Structure containing the environment variables.
 *		  Used to maintain constant function prototype.
 * Return: The environment variables as an array of strings.
 */

char** get_environ(info_s* info) 
{
    /* If the environment variables have not been set or have been changed, update them. */
    if (!info->envirom || info->env_changed) {
        // Free the old environment variables if they exist
        if (info->envirom) {
            for (int i = 0; info->envirom[i] != NULL; i++) {
                free(info->envirom[i]);
            }
            free(info->envirom);
        }

        // Count the number of environment variables
        int env_count = 0;
        list_t* env_ptr = info->env;
        while (env_ptr != NULL) {
            env_count++;
            env_ptr = env_ptr->next;
        }

        // Allocate memory for the environment variables array
        info->envirom = (char**)malloc((env_count + 1) * sizeof(char*));
        if (!info->envirom) {
            // Handle allocation failure if needed
            return NULL;
        }

        // Copy the environment variables to the new array
        env_ptr = info->env;
        for (int i = 0; i < env_count; i++) {
            info->envirom[i] = strdup(env_ptr->var);
            env_ptr = env_ptr->next;
        }
        info->envirom[env_count] = NULL; // Null-terminate the array
        info->env_changed = 0;
    }

    return info->envirom;
}
/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_s *info, char **ptr, size_t *length)
{
	static char buf[BUFFER_SIZE_READ];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
**_strncpy - copies a string
*@dest: the destination string to be copied to
*@src: the source string
*@n: the amount of characters to be copied
*Return: the concatenated string
*/
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous memory allocated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer of old block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	p = malloc(new_size);
	if (!p)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}