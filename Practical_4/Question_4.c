#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(int num) {
	if (num < 2) return false;
	for (int i = 2; i < (int)sqrt(num); i++) {
		if (num % i == 0) return false;
	}
	return true;
}

void generate_fib(int fibonacci[], int n) {
	fibonacci[0] = 0;
	if (n >= 2) fibonacci[1] = 1;
	for (int i = 2; i < n; i++) {
		fibonacci[i] = fibonacci[i - 2] + fibonacci[i - 1];
	}
}

int main() {
	pid_t id;
	int n;
	
	printf("Enter n: ");
	scanf("%d", &n);
	
	int fibonacci[n];
	int fd[2];
	
	if (pipe(fd) == -1) {
		printf("Pipe failed.\n");
		return 1;
	}
	
	id = fork();
	if (id == -1) {
		perror("Fork failed.\n");
		return 1;
	}
	else if (id == 0) {
		close(fd[0]);
		generate_fib(fibonacci, n);
		write(fd[1], fibonacci, sizeof(fibonacci));
		close(fd[1]);
		printf("Child ID: %d completed execution.\n", getpid());
		return 0;
	}
	else {
		wait(NULL);
		close(fd[1]);
		read(fd[0], fibonacci, sizeof(fibonacci));
		close(fd[0]);
		
		printf("Fibonacci Series: ");
		for (int i = 0; i < n; i++) {
			printf("%d ", fibonacci[i]);
		}
		printf("\n");
		
		printf("Prime fibonacci elements: ");
		for (int i = 0; i < n; i++) {
			if (is_prime(fibonacci[i]))
				printf("%d(Pos: %d) ", fibonacci[i], i + 1);
		}
	}
	printf("\n");
	return 0;
}