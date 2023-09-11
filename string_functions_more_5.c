#include "shell.h"

/**
 * **strtow2 - split string into words
 *
 * @str: the input string
 * @d: the delimeter
 *
 * Return: a pointer to an array of strings
 */

char *strtow2(char *str, char *d)
{
	int i, j, k, m, number_of_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
			(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			number_of_words++;
	if (number_of_words == NULL)
		return (NULL);
	s = malloc((i + number_of_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < number_of_words; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
	k = 0;
	while (str[i + k] != d && str[i + k] && str[i + k] != d)
		k++;
	s[j] = malloc((k + 1) * sizeof(char));
	if (!s[j])
	{
		for (k = 0; k < j; k++)
			free(s[k]);
		return (NULL);
	}
	for (m = 0; m < k; m++)
		s[j][m] = str[i++];
	s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
