#include "simpleshell.h"

/**
 * expansion_path - search is the first argument is an executable in the PATH
 *
 * @arg: the first argument
 * @env: the environment variable
 */

void expansion_path(char **arg, char *path_var)
{
	char **path = NULL;
	int i = 0;
	char *bin_path = NULL, *tmp = _strdup(*arg);
	struct stat stats;

	if (is_builtin(tmp))
	{
		free(tmp);
		return ;
	}

	path = strtoav(path_var, ":");
	while (path && path[i])
	{
		tmp = _strdup(*arg);
		bin_path = NULL;
		if (path[i][_strlen(path[i]) - 1] != '/')
			path[i] = c_concat(path[i], '/');
		bin_path = str_concat(path[i], tmp);

		if (lstat(bin_path, &stats) == -1)
			free(bin_path);
		else
		{
			/* i++;
			while (path && path[i])
				free(path[i++]);
			if (path)
				free(path); */
			if (stats.st_mode & S_IFREG)
			{
				if (stats.st_mode & S_IXUSR)
				{
					tmp = NULL;
					*arg = _strdup(bin_path);
					free(bin_path);
					return ;
				}
				else
					printf("HANDLE PERMISSION ERROR\n");
			}
		}
		i++;
	}
	free(path_var);
}
