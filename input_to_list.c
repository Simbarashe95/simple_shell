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

int	count_delim(char *str)
{
	int	cnt = 0;
	int	i = 0;

	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == ';')
			++cnt;
		else if (str[i] == '&' && str[i + 1] == '&')
		{
			++i;
			++cnt;
		}
		else if (str[i] == '|' && str[i + 1] == '|')
		{
			++i;
			++cnt;
		}
		++i;
	}
	return (cnt);
}

int	add_spaces(char **str)
{
	char	*new;
	int	cdlm;
	int	i, j;

	cdlm = count_delim(*str);
	if (cdlm == 0)
		return (1);
	new = malloc(_strlen(*str) + cdlm * 2 + 1);
	if (!new)
		return (-1);
	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == ';')
		{
			new[j] = ' ';
			new[++j] = ';';
			new[++j] = ' ';
		}
		else if ((*str)[i] == '|' && (*str)[i + 1] == '|')
		{
			new[j] = ' ';
			new[++j] = '|';
			new[++j] = '|';
			new[++j] = ' ';
			++i;
		}
		else if ((*str)[i] == '&' && (*str)[i + 1] == '&')
		{
			new[j] = ' ';
			new[++j] = '&';
			new[++j] = '&';
			new[++j] = ' ';
			++i;
		}
		else
		{
			new[j] = (*str)[i];
		}
		++i;
		++j;
	}
	new[j] = '\0';
	free(*str); //stocker str
	*str = new;
	return (1);
}

int	create_list(char **str_init, scrpt_lst **head)
{
	char	*dlm[3] = { ";", "||", "&&"};
	char	**tok;
	int	i, j, k;
	char	flag = '1';

	if (add_spaces(str_init) == -1)
		return (-1);
	tok = strtoav(*str_init, " \t");
	//free(*str_init);
	if (!tok)
		return (-1);
	i = 0;
	k = 0;
	while (tok[i])
	{
		j = 0;
		while (j < 3)
		{
			if (_strcmp(tok[i], dlm[j]) == 0)
			{
				//printf("tok[%d] = [%s]\n", i , tok[i]); 
				//printf("k = [%d] i + 1 = [%d]\n", k , i +1);
				free(tok[i]);
				tok[i] = NULL;
				if (create_node(head, tok + k, flag) != 1)
					return (-1);
				flag = dlm[j][0];
				/* need to check for delim in a row right below */
				k = i + 1;
				break;
			}
			++j;
		}
		++i;
	}
	i = 0;
	if (create_node(head, tok + k, flag) != 1)
		return (-1);
	return (1);
}

/*
int	get_line()
{
	char	*str_init;
	char	*str_buf;
	scrpt_lst	*head = NULL;
	size_t	n = 0;
	ssize_t	r = 0;

	r = getline(&str_init, &n, stdin);
	create_list(&str_init, &head);
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
*/
