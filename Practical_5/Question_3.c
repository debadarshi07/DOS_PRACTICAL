#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem_A, sem_B;

void* printA(void* arg) {
	for (int i = 0; i < 20; i++) {
		sem_wait(&sem_A);
		printf("A ");
		sem_post(&sem_B);
	} return NULL;
}

void* printB(void* arg) {
	for (int i = 0; i < 20; i++) {
		sem_wait(&sem_B);
		printf("B ");
		sem_post(&sem_A);
	} return NULL;
}

int main() {
	pthread_t printer_A, printer_B;

	sem_init(&sem_A, 0, 1);
	sem_init(&sem_B, 0, 0);

	pthread_create(&printer_A, NULL, printA, NULL);
	pthread_create(&printer_B, NULL, printB, NULL);
	
	pthread_join(printer_A, NULL);
	pthread_join(printer_B, NULL);
	
	sem_destroy(&sem_A);
	sem_destroy(&sem_B);

	printf("\n");
	
	return 0;
}