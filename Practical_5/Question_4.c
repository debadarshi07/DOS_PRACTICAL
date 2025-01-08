#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_ascend, sem_descend;

void* print_ascend(void* arg) {
	for (int i = 1; i < 11; i++) {
		sem_wait(&sem_ascend);
		printf("%d ", i);
		sem_post(&sem_descend);
	} return NULL;
}

void* print_descend(void* arg) {
	for (int i = 10; i > 0; i--) {
		sem_wait(&sem_descend);;
		printf("%d ", i);
		sem_post(&sem_ascend);
	}
}

int main() {
	pthread_t printer_ad, printer_dd;

	sem_init(&sem_ascend, 0, 1);
	sem_init(&sem_descend, 0, 0);

	pthread_create(&printer_ad, NULL, print_ascend, NULL);
	pthread_create(&printer_dd, NULL, print_descend, NULL);

	pthread_join(printer_ad, NULL);
	pthread_join(printer_dd, NULL);

	sem_destroy(&sem_ascend);
	sem_destroy(&sem_descend);
	printf("\n");

	return 0;
}