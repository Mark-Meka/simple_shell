#include "shell.h"
#include <string.h>

int main(void)
{
	pid_t pid;
	pid = fork();
	if (pid < 0)
	{
		printf("Fork Faild");
		return (1);
	}
	else if (pid == 0)
	{
		execlp("/bin/ls", "ls", NULL);
	}
	else
	{
		wait(NULL);
		printf("Child Complete");
	}
	return (0);
}
