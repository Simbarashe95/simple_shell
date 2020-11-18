#include "simpleshell.h"

/**
 * _strchr - search for a character in a string and returns its index
 *
 * @c: the character to find
 * @str: the string to look inside
 *
 * Return: index of the first occurence of the character, else length of str
 */

int _strchr(char c, char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

/**
 * sh_getline - getline
 */

int sh_getline(char **line, int fd)
{
	int ret, pos = 0, buf_size = 1;
	char c;

	*line = malloc(sizeof(char) * 1);
	while ((ret = read(fd, &c, 1)) > 0)
	{
		*(*line + pos) = (c == '\n') ? '\0' : c;
		if (*(*line + pos) == '\0')
			return (1);
		pos++;
		if (pos >= buf_size)
		{
			*line = _realloc(*line, buf_size, buf_size + 1);
			buf_size++;
		}
	}
	return ((ret == 0) ? EOF : -2);
}
