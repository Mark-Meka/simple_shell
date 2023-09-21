#include "shell.h"
/**
 * main - main function that sets shell loop function
 * @ac: argument count/not set
 * @av: argument vector
 * Return: Exits if successful.
 */

int main(int argc, char **argv)
{
	argc = argc;
	argv = argv;

	printf("\t********** Welcome to Our Shell **********\n");

	shell_loop();

	return (EXIT_SUCCESS);
}
