#include "simpleshell.h"

int	parse_logic_op(cmd_lst_lst **llav_head, cmd_lst *lav_head) // create the list of char**av -> linked list of cmds
{
	cmd_lst_lst	*node;
	char		**list;
	int		i;

	if (!llav_head)
		return (-1);
	node = *llav_head;
	while (node)
	{
		list = strtok2(node->list, {"&&","||", 0});
		i = 0;
		while (list[i])
		{
			add_cmd_lst(list[i], lav_head);
			++i;
		}
		node = node->next;
	}
}

int	parse_ctrl_op(char *input, cmd_lst_lst **head) // create the list of char ***lav -> linked list of commands list
{
	char	**lists;
	int	i = 0;

	lists = strtoav(input, ";\n");
	//store str for history opr free(str)
	if (!lists)
		return (-1);
	while (lists[i])
	{
		add_cmd_lst_lst(lists[i], head);
		++i;
	}
	return (1);
}

int	parser(char *input) //char * to char ****llav
{
	cmd_lst_lst	*llav_head;
	cmd_lst		*lav_head;
	char	**parse_logical_op;

	head = NULL;
	if (parse_ctrl_op(input, &llav_head) == -1)
		return (-1);
	if (parse_logic_op(&llav_head, &lav_head) == -1)
		return (-1);
	
}
