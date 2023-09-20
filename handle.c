#include "shell.h"

/**
 * reading_input - program read the string from user
 *
 * Return: input string by user
 */
char *read_input(void)
{
	char *input_line = NULL;
	size_t buffer_size = 0;

	if (getline(&input_line, &buffer_size, stdin) == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("shell: getline");
			exit(EXIT_FAILURE);
		}
	}
	return (input_line);
}

/**
 * tokenize_input - Tokenizes a line into command arguments.
 * @input: The user input as a string.
 *
 * Return: NULL-terminated array of command arguments.
 */
char **tokenize_input(char *input)
{
	int token_buffer_size = TOKEN_BUFFER_SIZE;
	int token_position = 0;
	char **tokens = malloc(token_buffer_size * sizeof(char *));
	char *token, **tokens_backup;

	if (!tokens)
	{
		fprintf(stderr, "shell: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, TOKEN_DELIMITERS);
	while (token != NULL)
	{
		tokens[token_position] = token;
		token_position++;

		if (token_position >= token_buffer_size)
		{
			token_buffer_size += TOKEN_BUFFER_SIZE;
			tokens_backup = tokens;
			tokens = realloc(tokens, token_buffer_size * sizeof(char *));
			if (!tokens)
			{
				free(tokens_backup);
				fprintf(stderr, "shell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIMITERS);
	}

	tokens[token_position] = NULL;
	return (tokens);
}

/**
 * shell_running - loop of shell.
 */
void run_shell(void)
{
	char *user_input;
	char **command_args;
	int execution_status;

	do {
		printf("simple_shell$ ");
		user_input = read_input();
		command_args = tokenize_input(user_input);
		execution_status = execute_command(command_args);
		free(user_input);
		free(command_args);
	}

	while (execution_status);
}
