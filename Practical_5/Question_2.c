#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_odd, sem_even;

void* print_even(void* arg) {
	for (int i = 2; i <= 20; i += 2) {
		sem_wait(&sem_even);
		printf("%d ", i);
		sem_post(&sem_odd);
	} return NULL;
}

void* print_odd(void* arg) {
	for (int i = 1; i <= 20; i += 2) {
		sem_wait(&sem_odd);
		printf("%d ", i);
		sem_post(&sem_even);
	} return NULL;
}

int main() {
	pthread_t even, odd;

	sem_init(&sem_odd, 0, 1);
	sem_init(&sem_even, 0, 0);

	pthread_create(&even, NULL, print_even, NULL);
	pthread_create(&odd, NULL, print_odd, NULL);

	pthread_join(odd, NULL);
	pthread_join(even, NULL);

	sem_destroy(&sem_even);
	sem_destroy(&sem_odd);
	printf("\n");

	return 0;
}