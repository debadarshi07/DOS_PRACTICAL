#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t id = fork();

	if (id == -1) {
		perror("Fork failed.\n");
		return 1;
	}
	else if (id == 0) {
		while (1) {
			printf("Child Process ID: %d\n", getpid());
			sleep(1);
		}
	}
	else {
		printf("Parent Process ID: %d\n", getpid());
		wait(NULL);
		printf("Child Process has completed execution.\n");
	}
	return 0;
}