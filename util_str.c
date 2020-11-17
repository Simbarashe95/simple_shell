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
 * _strcpy - copies src into dst
 *
 * @dst: the destination string
 * @src: the source string
 *
 * Return: a pointer on the new allocated string
 */

char *_strcpy(char *dst, const char *src)
{
	int i = 0;

	while (src[i])
		dst[i] = src[i++];
	dst[i] = '\0';
	return (dst);
}
