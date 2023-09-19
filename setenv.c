#include "shell.h"

/**
 * main - setenv funciton adn unsetenv function
 *
 * Return: Always 0.
 */

// Function to parse a command line into arguments
void parseCommandLine(char *line, char **args) {
    char *token = strtok(line, " ");
    int i = 0;

    while (token != NULL && i < MAX_ARGUMENTS - 1) {
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }

    args[i] = NULL; // Null-terminate the argument array
}

// Function to handle the setenv built-in command
void handleSetenv(char **args) {
    if (args[1] != NULL && args[2] != NULL) {
        if (setenv(args[1], args[2], 1) == -1) {
            perror("setenv");
        }
    } else {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
    }
}

// Function to handle the unsetenv built-in command
void handleUnsetenv(char **args) {
    if (args[1] != NULL) {
        if (unsetenv(args[1]) == -1) {
            perror("unsetenv");
        }
    } else {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *arguments[MAX_ARGUMENTS];

    while (1) {
        printf(":) ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove the trailing newline character
        size_t input_length = strlen(input);
        if (input_length > 0 && input[input_length - 1] == '\n') {
            input[input_length - 1] = '\0';
        }

        // Parse the command line into arguments
        parseCommandLine(input, arguments);

        if (arguments[0] != NULL) {
            if (strcmp(arguments[0], "setenv") == 0) {
                // Handle the setenv built-in command
                handleSetenv(arguments);
            } else if (strcmp(arguments[0], "unsetenv") == 0) {
                // Handle the unsetenv built-in command
                handleUnsetenv(arguments);
            } else if (strcmp(arguments[0], "exit") == 0) {
                // Handle the exit built-in command with arguments
                if (arguments[1] != NULL) {
                    int exit_status = atoi(arguments[1]);
                    exit(exit_status);
                } else {
                    exit(0);
                }
            } else if (strcmp(arguments[0], "env") == 0) {
                // Handle the env built-in command
                handleEnv();
            } else if (commandExists(arguments[0])) {
                pid_t child_pid = fork();

                if (child_pid == -1) {
                    perror("fork");
                    exit(1);
                } else if (child_pid == 0) {
                    // Child process: execute the command with arguments
                    execvp(arguments[0], arguments);
                    perror("execvp"); // Execvp only returns if there's an error
                    exit(1);
                } else {
                    // Parent process: wait for the child to complete
                    int status;
                    if (waitpid(child_pid, &status, 0) == -1) {
                        perror("waitpid");
                        exit(1);
                    }
                }
            } else {
                printf("Command not found: %s\n", arguments[0]);
            }
        }
    }

    return 0;
}
