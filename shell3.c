#include "shell.h"
int main(void)
{
	char input[MAX_INPUT_LENGTH];

	while (1)
	{
		printf("simple_shell$ ");
		
		if (!fgets(input, sizeof(input), stdin))
			break;
		input[strcspn(input, "\n")] = '\0';

		if (access(input, X_OK) == 0)
		{
			pid_t pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (pid == 0)\
			{
				char *args[] = {input, NULL};
				execve(input, args, environ);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			else
			{
				int status;
				waitpid(pid, &status, 0);
			}
		}
		else
		{
			fprintf(stderr, "%s: command not found\n", input);
		}
	}
	return 0;
}
