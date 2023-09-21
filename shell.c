#include "shell.h"
/**
 * main - Entry point for the simple_shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	char input[MAX_INPUT_LENGTH], *args[3];

	args[2] = NULL;

	while (printf("simple_shell$ ") && fgets(input, sizeof(input), stdin))
	{
		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0)
			break;

		if (fork() == 0)
		{
			args[0] = "ls";
			args[1] = "-laR";
			execvp(args[0], args);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		wait(NULL);
	}
	return (0);
}
