#include "simpleshell.h"

int main(int argc, char **argv, char **env)
{
	char *line;
	int ret = 0;

	while (1)
	{
		ret = sh_getline(&line);
		if (ret == ERROR)
		{
			continue ;
		}
		if (ret == EOT)
			exit(EXIT_SUCCESS);
		printf("%s\n", line);
	}
	free(line);
	return (EXIT_SUCCESS);
}

/**
 * sh_getline - getline 
 *
 *

int sh_getline(char **line)
{
	int buf_size = 1, pos = 0;
	char c;

	*line = malloc(sizeof(char) * 1);
	while ((ret = read(STDIN_FILENO, &c, 1)) > 0)
	{
		*(*line + pos++) = (c == '\n')
	}
}
