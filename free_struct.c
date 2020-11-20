#include "simpleshell.h"

int	free_scrpt_lst(scrpt_lst **head)
{
	scrpt_lst	*node;
	int		i;

	if (!head)
		return (0);
	node = *head;
	while (node)
	{
		i = 0;
		while (node->av[i])
		{
			free
			++i;
		}
		node = node->next;
	}
}
