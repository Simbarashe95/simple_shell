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
	return (write(1, str, _strlen(str)));
}
