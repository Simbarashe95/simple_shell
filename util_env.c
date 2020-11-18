#include "simpleshell.h"

/**
 * sh_get_env - duplicates the environment from env variable
 *
 * @env: the env variable
 *
 * Return: pointer on char ** array of variables
 */

char **sh_get_env(char **env)
{
	int i = 0;
	char **new_env;

	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = 0;

	while (env[i])
	{
		new_env[i] = _strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void sh_delete_env(char **env)
{
	int i = 0;

	if (env)
	{
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
	}
}
