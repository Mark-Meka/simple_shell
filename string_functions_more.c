#include "shell.h"

/**
 * _strcpy - copy a string
 *
 * @dest: the first parameter
 * @src: the second parameter
 *
 * Return: pointer to another string
 */

char *_strcpy(char *dest, char *src)
{
	int c = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[c])
	{
		dest[c] = src[c];
		c++;
	}
	dest[c] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 *
 * @str: the string to duplicate
 *
 * Return: pointer to duplicated string
 */

char *_strdup(const char *str)
{
	int l = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		l++;
	ret = malloc(sizeof(char) * (l + 1));
	if (!ret)
		return (NULL);
	for (l++; l--)
		ret[l] = *--str;
	return (ret);
}
/**
 * _puts - prints an input string
 *
 * @str: the string will be printed
 *
 * Return: nothing
 */

void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar - writes a character
 * @c: the character to print
 *
 * Return: on success 1 .
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}
