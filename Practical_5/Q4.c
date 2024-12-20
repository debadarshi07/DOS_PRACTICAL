#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
sem_t sem_down, sem_up;

void *countdown(void *arg){
	for(int i=10; i>=1; i--){
		sem_wait(&sem_down);
		printf("%d ", i);
		sem_post(&sem_up);
	}
	return NULL;
}

void *countup(void *arg){
	for(int i=1; i<=10; i++){
		sem_wait(&sem_up);
		printf("%d ", i);
		sem_post(&sem_down);
	}
	return NULL;
}
int main(){
	pthread_t down, up;
	sem_init(&sem_down, 0, 1);
	sem_init(&sem_up, 0, 0);
	pthread_create(&down, NULL, countdown, NULL);
	pthread_create(&up, NULL, countup, NULL);
	pthread_join(down, NULL);
	pthread_join(up, NULL);
	printf("\n");
	return 0;
}
