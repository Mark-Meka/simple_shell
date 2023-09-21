#include "shell.h"
/**
 * main - Entry point for the simple_shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	char input[MAX_INPUT_LENGTH], *args[2];
	char *path = getenv("PATH");
	char full_path[MAX_INPUT_LENGTH];
	char *command = input;

	printf("Betty rules!\n");

	while (printf("simple_shell$ ") && fgets(input, sizeof(input), stdin))
	{
		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0)
			break;

		while ((command = strsep(&path, ":")))
		{
			printf(full_path, "%s/%s", command, input);
			if (access(full_path, F_OK) == 0)
				break;
		}

		if (command == NULL)
		{
			printf("Command does not exist: %s\n", input);
			continue;
		}
		pid_t pid = fork();

		if (pid == 0)
		{
			args[0] = full_path;
			args[1] = NULL;
			execve(full_path, args, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}
