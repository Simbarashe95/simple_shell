#include "simpleshell.h"

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
	char	**sbuf;
	char	**tok;
	size_t	len;
	int	i, j;

	tok = strtoav(*str_init, " \n");
	
	/* test \*\/
	char **r;
	r = tok;
	while(*r)
	{
		printf("%s\n", *r);
		++r;
	}
	\* end of test */
	sbuf = tok;
	i = 0;
	while (tok[i])
	{
		j = 0;
		while (j < 4)
		{
			if (_strcmp(tok[i], dlm[j]) == 0)
			{
				free(tok[i]);
				tok[i] = NULL;
				create_node(head, sbuf, dlm[j][0]);
				/* need to check for delim in a row right below */
				*sbuf = tok[i + 1];
				/* some test */
				int k;
				k = 0;
				while (tok[i + 1 + k])
				{
					printf("HRER %s\n", tok[i+1+k]);
					k++;
				}
				/* end of test */
				break;
			}
				++j;
		}
		++i;
	}
	i = 0;
	while (1)
	{
		printf("tok[%d] : \"%s\"\n", i, tok[i]);
		++i;
	}

	printf("out\n");
	create_node(head, sbuf, '1');
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
