#include "simpleshell.h"

/**
 * str_concat - concatenates two strings
 *
 * @s1: the first string
 * @s2: the second string
 *
 * Return: a pointer to the new string, or NULL on failure
 */

char *str_concat(char *s1, char *s2)
{
	char *str;
	inti = 0, j = 0;

	if (s1 == NULL && s2 != NULL)
		return (_strdup(s2));
	if (s2 == NULL && s1 != NULL)
		return (_strdup(s1));
	str = malloc(sizeof(char) * (_strlen(s1) + _strlen(s2) + 1));
	if (!str)
		return (NULL);
	if (s1 != NULL && s2 != NULL)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		while (s2[j])
		{
			str[i + j] = s2[j];
			j++;
		}

	}
	str[i + j] = '\0';
	return (str);
}

/**
 * _strndup - allocates a new space in memory which contains
 * a copy of the string given as a parameter until n length
 *
 * @str: the string to duplicate
 * @n: the max length
 *
 * Return: a pointer to the new string, or NULL if str = NULL or fail
 */

char *_strndup(char *str, int n)
{
	char *new_str;
	int	i = 0;

	if (str == NULL)
		return (NULL);
	new_str = malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return (NULL);
	while (str[i] && i < n)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/**
 * is_env_fmt - checks if a character is upper or digit
 *
 * @c: the character to test
 *
 * Return: 1 if yes, 0 if no
 */

int is_env_fmt(char c)
{
	if ((c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z')
			|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

/**
 * expansion - handles all expansions and replacement functions
 *
 * @data: the data_t structure
 *
 * Return: an int
 */

int expansion(data_t *data)
{
	cmd_lst_lst_t   *llav_head = data->llav_head;
	cmd_lst_t *node;
	int i = 0, j = 0;

	while (llav_head)
	{
		printf("llav_node(%d): [%s]\n", i, llav_head->list);
		node = (llav_head->head);
		j = 0;
		while (node)
		{
			expansion_var_alias(llav_head->av, data);
			printf("node (%d) cmds: [%s] exe: [%d]\n", j, node->cmd, node->exe);
			node = node->next;
			++j;
		}
		llav_head = llav_head->next;
		++i;
	}
}

/**
 * expansion_var_alias - expands the $X variables and replaces aliases
 *
 * @av: the arguments of our commands
 * @data: the data_t structure
 */

void expansion_var_alias(char **av, data_t *data)
{
	int i = 0, j = 0, k;
	char *tmp, *val, *new_av = NULL;

	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '$' && is_env_fmt(av[i][j + 1]))
			{
				j++;
				k = j;
				while (av[i][k] && is_env_fmt(av[i][k]))
					k++;
				tmp = _strndup(av[i] + j, k - j + 1);
				val = sh_get_env_var(tmp);
				new_av = str_concat(new_av, val);
				free(tmp);
				if (val)
					free(val);
			}
			j++;
		}
		i++;
	}
}
