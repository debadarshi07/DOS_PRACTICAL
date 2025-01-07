#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void copy_file(const char *src, const char *dest) {
	FILE *src_file = fopen(src, "r"), *dest_file = fopen(dest, "w");
	if (!src_file || !dest_file) {
		perror("Error opening file.\n");
		return;
	}
	
	char buffer[1000];
	while (fgets(buffer, 1000, src_file) != NULL) {
		fputs(buffer, dest_file);
	}
	
	fclose(src_file);
	fclose(dest_file);
}

void display_file(const char *file_name) {
	FILE *file = fopen(file_name, "r");
	if (!file) {
		perror("Error opening file.\n");
		return;
	}

	printf("File content: \n");
	char buffer[1000];
	while (fgets(buffer, 1000, file) != NULL) {
		printf("%s", buffer);
	}

	fclose(file);
}

void sort_file_reverse(const char* file_name) {
	FILE *file = fopen(file_name, "r");
	if (!file) {
		perror("Error opening file.\n");
		return;
	}
	
	char lines[1000][1000];
	int line_count = 0;
	
	while (fgets(lines[line_count], 1000, file) != NULL) {
		line_count++;
	}
	fclose(file);
	
	for (int i = 0; i < line_count; i++) {
		for (int j = i + 1; j < line_count; j++) {
			if (strcmp(lines[i], lines[j]) < 0) {
				char temp[1000];
				strcpy(temp, lines[i]);
				strcpy(lines[i], lines[j]);
				strcpy(lines[j], temp);
			}
		}
	}

	printf("Reverse Sorted Order: \n");
	for (int i = 0; i < line_count; i++) {
		printf("%s", lines[i]);
	}
}

int main() {
	pid_t id1, id2, id3;
	
	id1 = fork();
	if (id1 == -1) {
		perror("Fork failed.\n");
		return 1;
	}
	else if (id1 == 0) {
		printf("First Child ID: %d, Parent ID: %d\n", getpid(), getppid());
		copy_file("file1.txt", "file2.txt");
		printf("File copied successfully.\n\n");
		return 0;
	}
	else {
		sleep(1);
	}
	
	id2 = fork();
	if (id2 == -1) {
		perror("Fork failed.\n");
		return 1;
	}
	else if (id2 == 0) {
		printf("Second Child ID: %d, Parent ID: %d\n", getpid(), getppid());
		display_file("file1.txt");
		printf("\n");
		return 0;
	}
	else {
		sleep(1);
	}
	
	id3 = fork();
	if (id3 == -1) {
		perror("Fork failed.\n");
		return 1;
	}
	else if (id3 == 0) {
		printf("Third Child ID: %d, Parent ID: %d\n", getpid(), getppid());
		sort_file_reverse("file1.txt");
		printf("\n");
		return 0;
	}
	else {
		sleep(1);
	}
	
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
	waitpid(id3, NULL, 0);
	
	printf("Parent Process ID: %d\n", getpid());
	return 0;
}