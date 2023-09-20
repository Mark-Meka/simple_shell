#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

/**
 * main - Entry point for the simple_shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	char input[MAX_INPUT_LENGTH], *args[2];

	while (printf("simple_shell$ ") && fgets(input, sizeof(input), stdin))
	{
		input[strcspn(input, "\n")] = '\0';

		if (fork() == 0)
		{
			args[0] = input;
			args[1] = NULL;
			execve(input, args, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		wait(NULL);
	}
	return (0);
}
