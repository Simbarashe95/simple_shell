#include "simpleshell.h"

int	add_cmd_lst(char *cmd, cmd_lst_t **head, char flag)
{
	cmd_lst_t	*node;
	cmd_lst_t	*buf = 0;

	node = (cmd_lst_t *)malloc(sizeof(cmd_lst_t));
	if (!node)
		return (-1);
	node->cmd = cmd;
	node->av = strtoav(cmd, " \t");
	node->exe = 0;
	node->flag = flag;
	node->next = NULL;
	buf = *head;
	if (buf)
	{
		while (buf->next)
			buf = buf->next;
		buf->next = node;
		node->prev = buf;
	}
	else
	{
		*head = node;
		node->prev = NULL;
	}
	return (1);
}

int	add_cmd_lst_lst(char *list, cmd_lst_lst_t **head)
{
	cmd_lst_lst_t	*node;
	cmd_lst_lst_t	*buf;

	node = (cmd_lst_lst_t *)malloc(sizeof(cmd_lst_lst_t));
	if (!node)
		return (-1);
	node->list = list;
	node->head = NULL;
	node->next = NULL;
	buf = *head;
	if (buf)
	{
		while (buf->next)
			buf = buf->next;
		buf->next = node;
	}
	else
		*head = node;
	return (1);
}

int	parse_logic_op(cmd_lst_lst_t **llav_head) // create the list of char**av -> linked list of cmds
{
	cmd_lst_lst_t	*node;
	char		*list;
	int		i;

	if (!llav_head)
		return (-1);
	node = *llav_head;
	while (node)
	{
		list = node->list;
		strsplit(node, node->list);
		node = node->next;
	}
	return (1);
}

int	parse_ctrl_op(char *input, cmd_lst_lst_t **head) // create the list of char ***lav -> linked list of commands list
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

int	parser(char *input, cmd_lst_lst_t **llav_head)
{
	if (parse_ctrl_op(input, llav_head) == -1)
		return (-1);
	if (parse_logic_op(llav_head) == -1)
		return (-1);

	/* tests */
	cmd_lst_t	*node;
	cmd_lst_lst_t	*head;
	int i =0, j = 0;
	head = *llav_head;
	while(head)
	{
		printf("llav_node(%d): [%s]\n", i, head->list);
		printf("llav_head->head: (%p)\n", head->head);
		node = (head->head);
		printf("NOPE\n");
		j = 0;
		while (node)
		{
			printf("node (%d) cmds: [%s] av: [%p] flag: [%c]\n",j, node->cmd,node->av, node->flag);
			node = node->next;
			++j;
		}
		head = (head->next);
		++i;
	}
	/* end tests */
	return (1);
}
/*
int	main()
{
	char	*str;
	size_t	n;

	while (1)
	{
		printf("-> ");
		getline(&str, &n, stdin);
		parser(str);
	}
}
*/
