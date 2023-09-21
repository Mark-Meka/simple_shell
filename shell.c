#include "shell.h"
/**
 * main - Entry point for the simple_shell.
 *
 * Return: Always 0.
 */

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	printf("\t********** Welcome to Our New custom C-Shell **********\n\n");
	printf("\t\t********** Made for ALX Kenya **********\n\n");

	shell_loop();

	return (EXIT_SUCCESS);
}
