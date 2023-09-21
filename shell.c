#include "shell.h"
#include <string.h>
/**
 * main - Entry point for the simple_shell.
 *
 * Return: Always 0.
 */
char *findExecutable(const char *command)
{
	char *path = getenv("PATH");
	char *token = strtok(path, ":");

	while (token != NULL)
	{
		char executablePath[256];
		snprintf(executablePath, sizeof(executablePath), "%s/%s", token, command);

		if (access(executablePath, X_OK) == 0)
		{
			return strdup(executablePath);
		}

		token = strtok(NULL, ":");
	}
	return (NULL);
}

int main (void)
{
	char input[MAX_INPUT_LENGTH], *args[4], *token;

	while (fgets(input, sizeof(input), stdin))
	{
		char** env = environ;

		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0)
			break;

		token = strtok(input, " ");
		args[0] = token;
		args[1] = NULL;

		if (strcmp(args[0], "ls") == 0)
		{
			char *executablePath = findExecutable("ls");
			if (executablePath != NULL)
			{
				args[0] = executablePath;
			}
			else
			{
				printf("ls: command not found\n");
				continue;
			}
		}

		else if (strcmp(args[0], "/bin/ls")  == 0 || strcmp(args[0], "./htbn_ls") == 0)
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

		else if (strcmp(args[0], "/bin/echo") == 0)
		{
			token = strtok(NULL, " ");
			if (token != NULL)
			{
				args[1] = token;
				token = strtok(NULL, " ");
			}
		}

		else if (strcmp(args[0], "env") == 0)
		{
			while (*env != NULL)
			{
				printf("%s\n", *env);
				env++;
			}
		
			token = strtok(NULL, " ");
			if (token != NULL)
			{
				args[1] = token;
				token = strtok(NULL, " ");
			}
		}

		else if ( strcmp(args[0], "                ") == 0)
			break;
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
	exit(EXIT_SUCCESS);
	
}
