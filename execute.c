#include "simpleshell.h"

int	execute(data_t *data, scrpt_lst **head)
{
	scrpt_lst	*node;
	pid_t		c;
	int		status;

	if (!head)
		return (-1);
	status = 4;
	node = *head;
	while (node)
	{
			printf("status = [%d]\n", status);
			printf("node: av[0] = [%s] flag = [%c]\n", node->av[0], node->flag);
		c = fork();
		wait(&status);
		//check status to know if it went well for && and ||
		if (c == 0)
		{
			if ((node->flag == ';') || (node->flag == '&' && status == 0) || (node->flag == '|' && status != 0 ))
				execve(node->av[0], node->av, data->env);
			return (0);
		}
		node = node->next;
	}
	return (0);
}

