#include "shell.h"
/**
 * _strlen - returns the length of string
 *
 * @s: input parameter
 *
 * Return: integer (the length)
 */

int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - compare of two strings
 *
 * @s1: the first string
 * @s2: the second string
 *
 * Return: Negative or positive or zero
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		*s1++;
		*s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle start with haystack
 *
 * @haystack: string to search
 * @needle: string to find
 *
 * Return: address of next char of haystack or NULL
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concat two strings
 *
 * @dest: the first parameter
 * @src: the second parameter
 *
 * Return: pointer to string
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		*dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (*ret);
}
