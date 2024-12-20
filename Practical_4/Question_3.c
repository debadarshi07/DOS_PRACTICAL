#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_SIZE 1024

// Function to copy the content of one file to another
void copy_file(const char *src, const char *dest) {
    FILE *src_file = fopen(src, "r");
    FILE *dest_file = fopen(dest, "w");
    if (!src_file || !dest_file) {
        perror("Error opening file");
        exit(1);
    }

    char buffer[MAX_SIZE];
    while (fgets(buffer, MAX_SIZE, src_file) != NULL) {
        fputs(buffer, dest_file);
    }

    fclose(src_file);
    fclose(dest_file);
}

// Function to display the content of a file
void display_file(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    char buffer[MAX_SIZE];
    while (fgets(buffer, MAX_SIZE, file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
}

// Function to display the sorted content of a file in reverse order
void sort_reverse_file(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    char lines[MAX_SIZE][MAX_SIZE];
    int line_count = 0;

    // Read lines from the file
    while (fgets(lines[line_count], MAX_SIZE, file) != NULL) {
        line_count++;
    }

    fclose(file);

    // Sort the lines in reverse order
    for (int i = 0; i < line_count - 1; i++) {
        for (int j = i + 1; j < line_count; j++) {
            if (strcmp(lines[i], lines[j]) < 0) {
                // Swap the lines
                char temp[MAX_SIZE];
                strcpy(temp, lines[i]);
                strcpy(lines[i], lines[j]);
                strcpy(lines[j], temp);
            }
        }
    }

    // Print the sorted lines in reverse order
    for (int i = 0; i < line_count; i++) {
        printf("%s", lines[i]);
    }
}

int main() {
    pid_t pid1, pid2, pid3;

    // Create the first child process to copy file1 to file2
    pid1 = fork();
    if (pid1 == -1) {
        perror("Error creating first child");
        exit(1);
    }

    if (pid1 == 0) {
        // First child process
        printf("First Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        copy_file("file1.txt", "file2.txt");
        exit(0);  // Exit after task is done
    } else {
        sleep(1);  // Parent waits for 1 second
    }

    // Create the second child process to display the content of file2
    pid2 = fork();
    if (pid2 == -1) {
        perror("Error creating second child");
        exit(1);
    }

    if (pid2 == 0) {
        // Second child process
        printf("Second Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        display_file("file2.txt");
        exit(0);  // Exit after task is done
    } else {
        sleep(1);  // Parent waits for 1 second
    }

    // Create the third child process to display sorted content of file2 in reverse order
    pid3 = fork();
    if (pid3 == -1) {
        perror("Error creating third child");
        exit(1);
    }

    if (pid3 == 0) {
        // Third child process
        printf("Third Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        sort_reverse_file("file2.txt");
        exit(0);  // Exit after task is done
    } else {
        sleep(1);  // Parent waits for 1 second
    }

    // Parent process waits for all child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    // Parent process displays its message after all children are done
    printf("Parent Process: PID = %d, All children have completed their tasks.\n", getpid());

    return 0;
}