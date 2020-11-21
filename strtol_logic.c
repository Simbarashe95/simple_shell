#include "simpleshell.h"

/**
 * _memcpy - copies memory area
 * @dest: the memory to write at
 * @src: the memory to write from
 * @n: the number of bytes to write
 *
 * Return: 0 if error else dest
 **/
char	*_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i = 0;

	while (i < n)
	{
		dest[i] = src[i];
		++i;
	}
	return (dest);
}

/**
 * _realloc - a function that reallocates a memory block
 * @ptr: a pointer to the memory previously allocated
 * @os: the old size in bytes of the allocated ptr
 * @ns: the new size in bytes of the new memory block
 *
 * Return: a pointer to the newly allocated block or NULL
 **/
void	*_realloc(void *ptr, unsigned int os, unsigned int ns)
{
	void	*r;

	if (!ptr)
	{
		r = malloc(ns);
		return (r ? r : 0);
	}
	if (os == ns)
		return (ptr);
	if (!ns)
	{
		free(ptr);
		return (0);
	}
	r = malloc(ns);
	if (!r)
		return (0);
	if (ns < os)
		_memcpy(r, ptr, ns);
	else
		_memcpy(r, ptr, os);
	free(ptr);
	return (r);
}

/**
 * _strncpy - copy n char of a source string to dest
 *@src: the source string
 *@dest: the destination string
 * @n: the number of elements to copy
 *
 *Return: pointer to the dest string
 **/
char	*_strncpy(char *dest, char *src, int n)
{
	int	i = 0;

	if (!dest || !src)
		return (dest);
	while (i < n)
	{
		dest[i] = *src;
		if (*src)
			++src;
		++i;
	}
	return (dest);
}

int	stralloc(char ***r, char *str, int i, size_t size)
{
	char	*buf;

	buf = (char *)malloc(i + 1);
	if (!buf)
		return (-1);
	buf = _strncpy(buf, str, i);
	buf[i] = '\0';
	*r = _realloc(*r, size * sizeof(void *), (size + 1) * sizeof(void *));
	if (!(*r))
		return (-1);
	(*r)[size - 1] = buf;
	return (1);
}

/**
 * strtoav - a function that splits a string into words
 * @str: the string in which to find the words
 * @delim: a string delimeter
 *
 * Return: a newly allocated list of words found in str
 **/
char	**strsplit(char *str)
{
	char	**r;
	char	*buf;
	int	i;
	size_t	size;

	if (!str || !*str)
		return (0);
	size = 1;
	r = malloc((size) * sizeof(char *));
	if (!r)
		return (0);
	i = 0;
	while (str[i])
	{
		if ((str[i] == '|' && str[i + 1] == '|') || (str[i] == '&' && str[i + 1] == '&'))
		{
			if (stralloc(&r, str, i, size) == -1)
			{
				while (size > 0)
					free(r[--size]);
				free(r);
				return (0);
			}
			++size;
			str += i + 2;
			i = -1;
		}
		++i;
	}
	if (stralloc(&r, str, i, size) == -1)
	{
		while (size > 0)
			free(r[--size]);
		free(r);
		return (0);
	}
	++size;
	r[size - 1] = NULL;
	return (r);
}

/*
int	main(int ac, char **av)
{
	char	**r;

	r = strsplit(av[1]);
	while (*r)
	{
		printf("%s\n", *r);
		++r;
	}
	return (0);
}
*/
