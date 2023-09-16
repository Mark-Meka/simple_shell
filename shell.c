#include "shell.h"
  
void sigintHandler(int signo)
{
    printf("\n"); // Print a newline to format the output
}

int main(int argc, char **argv)
{
    char *command = NULL;
    size_t len = 0;
    char *stkn;
    pid_t my_pid;
    int status;

    // Set up a signal handler for Ctrl+C (SIGINT)
    signal(SIGINT, sigintHandler);

    while (1)
    {
        printf("$ ");
        getline(&command, &len, stdin);

        // Remove newline character
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0)
        {
            free(command);
            exit(0);
        }

        char *arr[MAX_ARGUMENTS];
        int i = 0;
        stkn = strtok(command, " ");
        while (stkn != NULL && i < MAX_ARGUMENTS - 1)
        {
            arr[i] = stkn;
            stkn = strtok(NULL, " ");
            i++;
        }
        arr[i] = NULL; // Null-terminate the array

        my_pid = fork();
        if (my_pid == -1)
        {
            perror("Error");
            free(command);
            exit(1);
        }
        else if (my_pid == 0)
        {
            // Handle input and output redirection
            // Example: cmd < input.txt > output.txt 2>&1
            // ...

            if (execvp(arr[0], arr) == -1)
            {
                perror("execvp");
                free(command);
                exit(1);
            }
        }
        else
        {
            // Check if the command runs in the background
            if (i > 0 && strcmp(arr[i - 1], "&") == 0)
            {
                // Handle background process
                printf("Running in the background: %s\n", arr[0]);
                // Optionally, you can add this process to a list and manage background jobs
            }
            else
            {
                // Wait for the child process to finish
                wait(&status);
            }
        }
    }
    free(command);
    return 0;
}
