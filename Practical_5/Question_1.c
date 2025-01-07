#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#define capacity 10

int buffer[capacity];
int in = 0, out = 0;

sem_t full, empty;
pthread_mutex_t mutex;

void* producer(void* arg) {
	for (int i = 0; i < 20; i++) {
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		buffer[in] = i;
		printf("Entered to buffer: %d\n", i);
		in = (in + 1) % capacity;
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	} return NULL;
}

void* consumer(void* arg) {
	for (int i = 0; i < 20; i++) {
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		int i = buffer[out];
		printf("Element read: %d\n", i);
		out = (out + 1) % capacity;
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	} return NULL;
}

int main() {
	pthread_t produce, consume;

	sem_init(&full, 0, 0);
	sem_init(&empty, 0, capacity);

	pthread_mutex_init(&mutex, NULL);

	pthread_create(&produce, NULL, producer, NULL);
	pthread_create(&consume, NULL, consumer, NULL);

	pthread_join(produce, NULL);
	pthread_join(consume, NULL);
	
	sem_destroy(&full);
	sem_destroy(&empty);
	printf("\n");

	return 0;
}