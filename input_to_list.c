#include "simpleshell.h"

/**
 * _strstr - a function that locates a substring
 * @haystack: the string to search in
 * @needle: the string to find
 *
 * Return: the position of needle in haystack or 0 if error or no match
 *
 **/
char	*_strstr(char *haystack, char *needle)
{
	unsigned int	i;

	if (!haystack)
		return (0);
	if (!needle || !*needle)
		return (haystack);
	while (*haystack)
	{
		i = 0;
		while (haystack[i] == needle[i])
		{
			++i;
			if (!needle[i])
				return (haystack);
		}
		++haystack;
	}
	return (0);
}

/**
 * _strcmp - compare two strings
 * @s1: one string to compare
 * @s2: second string to compare
 *
 * Return: 0 if same char diff if not
 **/
int	_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i] || !s2[i])
			return (s1[i] - s2[i]);
		++i;
	}
	return (s2[i] ? -s2[i] : 0);
}

int	create_node(scrpt_lst **head, char **s, char d)
{
	scrpt_lst	*node;
	scrpt_lst	*buf;

	if (!*s)
		return (0);
	node = malloc(sizeof(scrpt_lst));
	if (!node)
		return (-1);
	node->av = s;
	node->flag = d;
	node->next = NULL;
	node->prev = NULL;
	if (!*head)
		*head = node;
	else
	{
		buf = *head;
		while (buf->next)
			buf = buf->next;
		node->prev = buf;
		buf->next = node;
	}
	return (1);
}

int	create_list(char **str_init, size_t *n, scrpt_lst **head)
{
	char	*dlm[4] = { ";", "||", "&&", "\n"};
	char	**tok;
	size_t	len;
	int	i, j, k;

	tok = strtoav(*str_init, " \n");
	i = 0;
	k = 0;
	while (tok[i])
	{
		printf("tok[%d] -> [%s]\n", i, tok[i]);
		j = 0;
		while (j < 4)
		{
			if (_strcmp(tok[i], dlm[j]) == 0)
			{
				free(tok[i]);
				tok[i] = NULL;
				printf("2 tok[%d] [%p] -> [%s]\n", i, tok + i, tok[i]);
				create_node(head, tok + k, dlm[j][0]);
				printf("3 tok[%d] [%p] -> [%s]\n", 0, tok, tok[0]);
				/* need to check for delim in a row right below */
				printf("4 tok[%d] [%p] -> [%s]\n", 0, tok, tok[0]);
				k = i + 1;
				break;
			}
			++j;
		}
		++i;
	}
	i = 0;
	printf("4 tok[%d] [%p] -> [%s]\n", k, tok + k, tok[k]);
	printf("out k = %d\n", k);
	create_node(head, tok + k, '1');
	return (1);
}


int	get_line()
{
	char	*str_init;
	char	*str_buf;
	scrpt_lst	*head = NULL;
	size_t	n = 0;
	ssize_t	r = 0;


	r = getline(&str_init, &n, stdin);
	create_list(&str_init, &n, &head);

	int	i, j;
	i = 0;
	while(head)
	{
		j=0;
		while(head->av[j])
		{
			printf("node (%i) string (%i): %s delim: %c\n", i, j, head->av[j], head->flag);
			++j;
		}
		++i;
		head = head->next;
	}
	printf("str init= %s\n", str_init);
	return (1);
}

int	main(int ac, char **av)
{
	pid_t	p, c;
	int	status;
	char *argv[2];

	//	getline --> strtok --> fork --> execve --> back to start;
	while (1)
	{
		printf("$ ");
		get_line();
	}
	return (0);
}
