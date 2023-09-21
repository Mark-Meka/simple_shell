#include "shell.h"
/**
 * execute_command - Execute a command specified by the user.
 *
 * This function takes a command string entered by the user, searches for
 * the command in the directories listed in the PATH environment variable,
 * and executes it if found. If the command is not found, it prints an error
 * message.
 *
 * @command: The command string to execute.
 */
void execute_command(const char *command)
{
	char *path = getenv("PATH");

	if (path == NULL)
	{
		fprintf(stderr, "PATH environment variable not set.\n");
		exit(EXIT_FAILURE);
	}
	char *path_copy = strdup(path);

	if (path_copy == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	char *token = strtok(path_copy, ":");

	while (token != NULL)
	{
		char command_path[MAX_INPUT_LENGTH];

		snprintf(command_path, sizeof(command_path), "%s/%s", token, command);

		if (access(command_path, X_OK) == 0)
		{
			execv(command_path, (char *[]){command, NULL});
			perror("execv");
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, ":");
	}

	fprintf(stderr, "Command not found: %s\n", command);
	exit(EXIT_FAILURE);
}
