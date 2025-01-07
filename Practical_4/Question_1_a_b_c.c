#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	pid_t id = fork();

	if (id == -1) {
		perror("Fork fails.");
		return 1;
	}
	else if (id == 0) {
		while (1) {
			printf("Child Process ID: %d\n", getpid());
			sleep(2);
		}
	}
	else {
		while(1) {
			printf("Parent Process ID: %d\n", getpid());
			sleep(2);
		}
	}

	return 0;
}