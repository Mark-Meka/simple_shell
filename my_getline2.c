#include "shell.h"

/**
 * main - my getline functin without strtok.
 *
 * Return: Always 0.
 */

// Custom getline function without using strtok
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream, char delimiter) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t bytes_read;
    ssize_t total_bytes_read = 0;
    int c;

    if (lineptr == NULL || n == NULL) {
        errno = EINVAL; // Invalid arguments
        return -1;
    }

    if (*lineptr == NULL || *n == 0) {
        // Allocate a new buffer if lineptr is NULL or n is 0
        bufsize = BUFFER_SIZE;
        buffer = (char *)malloc(bufsize);
        if (buffer == NULL) {
            errno = ENOMEM; // Memory allocation error
            return -1;
        }
        *n = bufsize;
    } else {
        buffer = *lineptr;
        bufsize = *n;
    }

    while ((c = fgetc(stream)) != EOF) {
        if (total_bytes_read >= bufsize - 1) {
            // Resize the line buffer if needed
            bufsize *= 2;
            char *new_buffer = (char *)realloc(buffer, bufsize);
            if (new_buffer == NULL) {
                free(buffer);
                errno = ENOMEM; // Memory allocation error
                return -1;
            }
            buffer = new_buffer;
        }

        buffer[total_bytes_read] = (char)c;
        total_bytes_read++;

        if (c == delimiter) {
            buffer[total_bytes_read] = '\0';
            *lineptr = buffer;
            return total_bytes_read;
        }
    }

    if (total_bytes_read == 0) {
        // End of file and no data read
        free(buffer);
        return -1;
    }

    buffer[total_bytes_read] = '\0';
    *lineptr = buffer;

    return total_bytes_read;
}

int main() {
    char *line = NULL;
    size_t len = 0;

    while (1) {
        ssize_t bytes_read = my_getline(&line, &len, stdin, '\n');

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
