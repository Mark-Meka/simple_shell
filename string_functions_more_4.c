#include "shell.h"

/**
 * **strtow - splits a string into words, repeated are ignored
 * @str: the input string
 * @d: the delimeter string
 *
 * Return: a pointer to an array of strings
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, number_of_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (!is_delim([i + 1], d) || !str[i + 1]))
			number_of_words++;

	if (number_of_words == 0)
		return (NULL);
	s = malloc((1 + number_of_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < number_of_words; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
