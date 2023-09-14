#include "shell.h"

int main(void)
{
	char *command = NULL, *command_copy = NULL;
	size_t len = 0;
	ssize_t reader;
	int token_num = 0;
	char *token;
	int i = 0;
	char **argv;

	printf("$ ");
	reader = getline(&command, &len, stdin);
	
	command_copy = malloc(sizeof(char) * reader);

	 if (command_copy == NULL)
	 {
		 perror("Allocation Error");
		 return (-1);
	 }

	 /* make a copy of the command */
	 strcpy(command_copy, command);

	/* check if getlind faild or not */
	if (reader == -1)
	{
		printf("Exiting Shell......\n");
		return (-1);
	}
	else
	{

		/************** split the string (command) & returns an array of each word *************/
		/* calculate the total number of token */
		token = strtok(command, " \n");

		while (token != NULL)
		{
			token_num++;
			token = strtok(NULL, " \n");
		}
		token_num++;

		/* Allocate to in array */
		argv = malloc(sizeof(char *) * token_num);

		/* store each token in the array */
		token = strtok(command_copy, " \n");

		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);

			token = strtok(NULL, " \n");
		}
		argv[i] = NULL;


		printf("%s\n", command);

		/* free up allocated memory */
		free(argv);
		free(command);
		free(command_copy);
	}
	return (0);
}