#include "shell.h"

/**
 * main - handle ecit built-in, that exits the shell.
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

// Function to check if a command exists in the PATH
int commandExists(const char *command) {
    char *path = getenv("PATH");
    char *pathCopy = strdup(path);

    char *token = strtok(pathCopy, ":");
    while (token != NULL) {
        char pathBuffer[MAX_INPUT_LENGTH];
        snprintf(pathBuffer, sizeof(pathBuffer), "%s/%s", token, command);

        if (access(pathBuffer, F_OK) == 0) {
            free(pathCopy);
            return 1; // Command exists
        }

        token = strtok(NULL, ":");
    }

    free(pathCopy);
    return 0; // Command not found
}

// Function to handle the exit built-in command
void handleExit() {
    printf("Exiting the shell.\n");
    exit(0);
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
            if (strcmp(arguments[0], "exit") == 0) {
                // Handle the exit built-in command
                handleExit();
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
