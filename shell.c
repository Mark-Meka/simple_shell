#include "shell.h"
/**
 * main - Entry point for the simple_shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	char input[MAX_INPUT_LENGTH], *args[4], *token;

	while (printf("simple_shell$ ") && fgets(input, sizeof(input), stdin))
	{
		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0)
			break;

		token = strtok(input, " ");
		args[0] = token;
		args[1] = NULL;

		if (strcmp(args[0], "/bin/ls") == 0)
		{
			token = strtok(NULL, " ");
			if (token != NULL && strcmp(token, "-l") == 0)
			{
				args[1] = "-l";
				token = strtok(NULL, " ");
			}
			else if (token != NULL)
			{
				args[1] = token;
				token = strtok(NULL, " ");
			}
		}
		args[2] = token;
		args[3] = NULL;

		if (access(args[0], F_OK) == 0)
		{
			if (fork() == 0)
			{
				execve(args[0], args, NULL);
				perror("exit");
				exit(EXIT_FAILURE);
			}
			wait(NULL);
		}
		else
		{
			printf("command not found.\n");
		}
	}
	exit(EXIT_SUCCESS);
}
