#include "shell.h"

/**
 * main - my own getline function
 *
 * Return: Always 0.
 */

// Custom getline function
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream) {
    static char buffer[BUFFER_SIZE];
    static size_t buffer_index = 0;
    static ssize_t bytes_in_buffer = 0;
    ssize_t bytes_read = 0;
    ssize_t total_bytes_read = 0;
    int eof_flag = 0;

    if (lineptr == NULL || n == NULL) {
        errno = EINVAL; // Invalid arguments
        return -1;
    }

    if (*lineptr == NULL || *n == 0) {
        // Allocate a new buffer if lineptr is NULL or n is 0
        *n = BUFFER_SIZE;
        *lineptr = (char *)malloc(*n);
        if (*lineptr == NULL) {
            errno = ENOMEM; // Memory allocation error
            return -1;
        }
    }

    while (1) {
        if (buffer_index >= bytes_in_buffer) {
            // Buffer is empty, read more data from the stream
            bytes_read = read(fileno(stream), buffer, BUFFER_SIZE);

            if (bytes_read == 0) {
                // End of file
                eof_flag = 1;
                break;
            } else if (bytes_read < 0) {
                // Read error
                return -1;
            }

            buffer_index = 0;
            bytes_in_buffer = bytes_read;
        }

        if (total_bytes_read + buffer_index >= *n - 1) {
            // Resize the line buffer if needed
            *n *= 2;
            char *new_lineptr = (char *)realloc(*lineptr, *n);
            if (new_lineptr == NULL) {
                free(*lineptr);
                errno = ENOMEM; // Memory allocation error
                return -1;
            }
            *lineptr = new_lineptr;
        }

        if (buffer[buffer_index] == '\n') {
            // Found a newline character
            (*lineptr)[total_bytes_read] = '\0';
            buffer_index++;
            total_bytes_read++;
            return total_bytes_read;
        }

        (*lineptr)[total_bytes_read] = buffer[buffer_index];
        buffer_index++;
        total_bytes_read++;
    }

    if (eof_flag && total_bytes_read == 0) {
        // End of file and no data read
        return -1;
    }

    (*lineptr)[total_bytes_read] = '\0';

    return total_bytes_read;
}

int main() {
    char *line = NULL;
    size_t len = 0;

    while (1) {
        ssize_t bytes_read = my_getline(&line, &len, stdin);

        if (bytes_read == -1) {
            printf("Error reading input.\n");
            break;
        } else if (bytes_read == 0) {
            printf("End of file reached.\n");
            break;
        } else {
            printf("Read %zd bytes: %s", bytes_read, line);
        }
    }

    free(line);
    return 0;
}
