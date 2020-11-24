#include "simpleshell.h"

/**
 * main - entry point of our shell
 */

int main(int argc, char **argv, char **env)
{
	data_t *data;
	int fd;

	data = sh_data_new(argv, env);
	if (argc > 1) //im what cases ac == 2 ?
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
	cmd_lst_lst_t	*head = NULL;
	char		*line = NULL;
	int		ret = 0;

	if (data->mode == INTERACTIVE)
		_puts("$ > ");

	while ((ret = sh_getline(&line, fd)) != EOF)
	{
		printf("line at sh_start = [%s]\n", line);
		/* TESTS  
		cmd_lst_lst_t *llav;
		cmd_lst_t *node;
		llav = head;
		int i = 0, j = 0;;
		while (llav)
		{
			printf("llav_node(%p): [%s]\n", llav, llav->list);
			node = (llav->head);
			j = 0;
			while (node)
			{
				printf("node (%d) cmds: [%s] exe: [%d]\n", j, node->cmd, node->exe);
				node = node->next;
				++j;
			}
			llav = llav->next;
			++i;
		}
		printf("OH\n");

		 END TESTS */
		
		if (parser(line, &head) != -1)
		{
			printf("Parser passed\n");
			data->llav_head = head;
			//expansion(data, &head);
			printf("Expansion passed\n");
			execute(data, &head);
			printf("Execute passed\n");
			free_all(&head);
			printf("Free_all passed\n");
		}
		data->lines++;

		if (data->mode == INTERACTIVE)
			_puts("$ > ");
	}
	if (line)
		free(line);
	if (data->mode == FROMFILE)
		close(fd);
	return (EXIT_SUCCESS);
}
