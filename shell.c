#include "shell.h"
/*
 * main - The main shell
 *
 * Return: Always 0.
 */

int main(void) {
	char command[120];

	while (true) 
	{
		display_prompt();
		read_command(command, sizeof(command));
		execute_command(command);
	}
	return (0);
}
