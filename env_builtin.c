#include "simpleshell.h"

/**
 * bi_env - env builtin
 *
 * @data: the data_t struct
 */

int bi_env(data_t *data)
{
	int i = 0;
	printf("ENV builtin \n");

	while (data && data->env && data->env[i])
	{
		write(STDOUT_FILENO, data->env[i], _strlen(data->env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}
