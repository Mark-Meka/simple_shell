#include "main.h"

int main(int ac, char **argv)
{
	char *command = 1024;
	size_t len = 0;
	ssize_t reader;
	const char *delim = " \n";
	int token_num = 0;
	char *token;
	int i;

	/* declar void variables */
	(void)ac;

	/* infite loop */
	while(1)
	{
		printf("$ ");
		reader = getline(&command, &len, stdin);
		
		/* check if getlind faild or not */
		if (reader == -1)
		{
			printf("Exiting Shell......\n");
			return (-1);
		}
		if (command == -1)
		{
			perror("Allocation Error");
			return (1);
		}
		
		/************** split the string (command) & returns an array of each word *************/
		/* calculate the total number of token */
		token = strtok(command, delim);

		while (token != NULL)
		{
			token_num++;
			token = strtok(NULL, delim);
		}
		token_num++;

		/* Allocate to in array */
		argv = malloc(sizeof(char *) * token_num);

		/* store each token in the array */
		token = strtok(

		printf("%s\n", command);

		/* free up allocated memory */
		free(command);
	}
	return (0);
}
