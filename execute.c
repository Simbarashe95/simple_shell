#include "simpleshell.h"

int	do_builtin(data_t *data, cmd_lst_t *node)
{
	char	*names[] = {"cd", NULL};
	int	(*func_p[])() = {};
	int	i = 0;

	while (names[i])
	{
		if (!_strcmp(names[i], node->av[0]))
			func_p[i]();
		else
			return (-1);
		++i;
	}
	return (0);
}

int	do_execve(data_t *data, cmd_lst_t *node)
{
	pid_t		c;
	int		status = 34;

	c = fork();
	wait(&status);
	if (c == 0)
	{
		execve(node->av[0], node->av, data->env);
		return (0);
	}
	node->exe = 1;
	return (0);
}

int	execute(data_t *data, cmd_lst_lst_t **head)
{
	cmd_lst_lst_t	*llav_node;
	cmd_lst_t	*node;

	llav_node = *head;
	printf("WE got to execute\n");
	while (llav_node)
	{
		printf("In execute llav_node->list = [%s]\n", llav_node->list);
		node = llav_node->head;
		while (node)
		{
			printf("av[0] = [%s]\n", node->av[0]);
			if (_strchr(node->av[0], '/'))
			{
				if (!(node->flag) || (node->flag == '&' && node->prev && node->prev->exe == 1) || (node->flag == '|' && node->prev && node->prev->exe == 0))
					do_execve(data, node);
			}
			else
			{
				if (do_builtin(data, node) == -1)
					return (-1);
			}
			node = node->next;
		}
		llav_node = llav_node->next;
	}
	return (0);
}
