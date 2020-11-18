#include "simpleshell.h"

/**
 * _putchar - calculates the length of a string
 *
 * @str: the string
 *
 * Return: length of the string, or 0 is string is NULL or empty
 */

int _strlen(char *str)
{
	int len = 0;

	if (str)
		while (str[len])
			len++;

	return (len);
}

/**
 * _puts - writes a string on the POSIX stdout
 *
 * @str: the string to write
 *
 * Return: length of str on success, 0 if nothing has been written, -1 on error
 */

int _puts(char *str)
{
	return (write(STDOUT_FILENO, str, _strlen(str)));
}

/**
 * _strdup - allocates a new space in memory which contains
 * a copy of the string given as a parameter
 *
 * @str: the string to duplicate
 *
 * Return: a pointer to the new string, or NULL if str = NULL or fail
 */

char *_strdup(char *str)
{
	char *new_str;
	int i = 0;

	if (str == NULL)
		return (NULL);
	new_str = malloc(sizeof(char) * _strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
