#include "shell.h"

void Mark_print(const char *message)
{
	write(STDOUT_FILENO, message, strlen(message));
}
