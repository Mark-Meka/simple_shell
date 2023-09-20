#include "shell.h"

int main(void)
{
	M I[P];

	while (F("#cisfun$ ") && fgets(I, P, stdin))
	{
		I[strcspn(I, "\n")] = '\0';
		if (!strcmp(I, "exit"))
			E;
		if (!strcmp(I, "env"))
		{
			M *e = *environ;

			while (e)
				F("%s\n", e), e = *(environ++);
			continue;
		}
		pid_t pid;

		if ((pid = fork()) == -1)
			E;
		if (pid == 0)
		{
			M *a[] = { I, NULL };

			execve(I, a, environ);
			perror(I);
			E;
		}
		else
		{
			int s;

			waitpid(pid, &s, 0);
		}
	}
	return (0);
}
