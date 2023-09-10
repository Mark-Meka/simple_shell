#include "shell.h"

/**
 * _strncpy - copies a string
 *
 * @dest: the first parameter
 * @src: the second parameter
 * @n: hte number of characters to be copied
 *
 * Return: the copied string
 */

char *_strncpy(char *dest, char *src, n)
{
	int i, j;
	char *s = dest;

	i = 0;

	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;

		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strcnat - concat two strings
 *
 * @dest: the first string
 * @src: the second string
 * @n: the number of bytes
 *
 * Return: the concatented string
 */

char *_strcnat(char *dest, char *src, char *n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * _strchr - locates a character in string
 *
 * @s: the first parameter
 * @c: the second parameter
 *
 * Return: the pointer to memory area
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
