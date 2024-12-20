#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
sem_t sem_A, sem_B;

void *print_A(void *arg){
	for(int i=0; i<10; i++){
		sem_wait(&sem_A);
		printf("A ");
		sem_post(&sem_B);
	}
	return NULL;
}

void *print_B(void *arg){
	for(int i=0; i<10; i++){
		sem_wait(&sem_B);
		printf("B ");
		sem_post(&sem_A);
	}
	return NULL;
}
int main(){
	pthread_t A, B;
	sem_init(&sem_A, 0, 1);
	sem_init(&sem_B, 0, 0);
	pthread_create(&A, NULL, print_A, NULL);
	pthread_create(&B, NULL, print_B, NULL);
	pthread_join(A, NULL);
	pthread_join(B, NULL);
	printf("\n");
	return 0;
}
