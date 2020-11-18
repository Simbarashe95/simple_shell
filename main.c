#include "simpleshell.h"

/**
 * main - entry point of our shell
 */

int main(int argc, char **argv, char **env)
{
	data_t *data;
	int fd;

	data = sh_data_new(argv, env);
	if (argc > 1)
	{
		data->mode = FROMFILE;
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			sh_data_delete(data);
			return (EXIT_FAILURE);
		}
		sh_start(data, fd);
	}
	else
	{
		if (isatty(STDIN_FILENO))
			data->mode = INTERACTIVE;
		else
			data->mode = NONINTERACTIVE;
		sh_start(data, STDIN_FILENO);
	}
	sh_data_delete(data);
	return (EXIT_SUCCESS);
}

/**
 * sh_start - when the type of execution has been choosen, parses and executes
 * commands
 *
 * @data: the data_t structure
 * @fd: the file descriptor to read
 *
 * Return: EXIT_SUCCESS always because all errors should be treated
 */

int sh_start(data_t *data, int fd)
{
	char *line = NULL;
	int ret = 0;

	if (data->mode == INTERACTIVE)
		_puts("$ > ");

	while ((ret = sh_getline(&line, fd)) != EOF)
	{
		printf("%s\n", line);
		if (data->mode == INTERACTIVE)
			_puts("$ > ");
	}
	if (line)
		free(line);
	if (data->mode == FROMFILE)
		close(fd);
	return (EXIT_SUCCESS);
}
