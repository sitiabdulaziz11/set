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

