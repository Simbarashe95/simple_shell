#include "simpleshell.h"

int	free_av(char **av)
{
	int	i = 0;

	if (!av)
		return (-1);
	while (av[i])
	{
		free(av[i]);
		++i;
	}
	free(av);
	av = NULL;
	return (1);
}

void	free_cmd_lst(cmd_lst_t *node)
{
	if (node)
	{
		free_av(node->av);
		node->av = NULL;
		free(node->cmd);
		node->cmd = NULL;
	}
}

void	free_cmd_lst_lst(cmd_lst_lst_t *llav)
{
	cmd_lst_t	*node;

	if (llav)
	{
		node = llav->head;
		while (node)
		{
			free_cmd_lst(node);
			node = node->next;
		}
		free(llav->list);
		llav->list = NULL;
	}
}

int	free_all(cmd_lst_lst_t **head)
{
	cmd_lst_lst_t	*llav;
	cmd_lst_t	*node;

	if (!head)
		return (-1);
	llav = *head;
	while (llav)
	{
		free_cmd_lst_lst(llav);
		llav = llav->next;
	}
	head = NULL;
	return (1);
}
