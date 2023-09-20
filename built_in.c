#include "shell.h"
/**
 * Function declarations
 */
int num_builtins(void);
int shell_cd(char **args);
int shell_exit(char **args);
int launch(char **args);
int execute(char **args);
/**
 * List of built-in commands
 */
char *builtin_str[] = {"cd", "exit"};
/**
 * Main entry point
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("shell> ");
		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
		char *args[64];
		int arg_count = 0;

		char *token = strtok(line, " \t\n");

		while (token != NULL)
		{
			args[arg_count] = token;
			arg_count++;

			token = strtok(NULL, " \t\n");
		}
		arg[arg_count] = NULL;

		if (arg_count > 0)
		{
			int status = execute(args);

			if (status == 0)
			{
				break;
			}
		}
	}

	free(line);
	exit(EXIT_SUCCESS);
}

/**
 * Function to count the number of built-in commands
 */
int num_builtins(void)
{
	return (sizeof(builtin_str) / sizeof(char *));
}

/**
 * Built-in command: Change directory
 */
int shell_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "shell: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("shell");
		}
	}
	return (1);
}

/**
 * Built-in command: Exit the shell
 */
int shell_exit(char **args)
{
	args = args;
	return (0);
}

/**
 * Function to launch an external program
 */
int launch(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("shell");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("shell");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		}

		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

/**
 * Function to execute a command (either built-in or external)
 */
int execute(char **args)
{
	if (args[0] == NULL)
	{
		return (1);
	}

	for (int i = 0; i < num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
		{
			return ((*builtin_func[i])(args));
		}
	}
	return (launch(args));
}
