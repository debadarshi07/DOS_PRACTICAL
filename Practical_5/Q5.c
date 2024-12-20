#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
sem_t sem_A, sem_B, sem_C;
void *print_A_seq(void *arg){
	for(int i=1; i<=20; i+=3){
		sem_wait(&sem_A);
		printf("A%d ", i);
		sem_post(&sem_B);
	} return NULL;
}
void *print_B_seq(void *arg){
	for(int i=2; i<=20; i+=3){
		sem_wait(&sem_B);
		printf("B%d ", i);
		sem_post(&sem_C);
	} return NULL;
}
void *print_C_seq(void *arg){
	for(int i=3; i<=20; i+=3){
		sem_wait(&sem_C);
		printf("C%d ", i);
		sem_post(&sem_A);
	} return NULL;
}
int main(){
	pthread_t A_seq, B_seq,C_seq;
	sem_init(&sem_A, 0, 1);
	sem_init(&sem_B, 0, 0);
	sem_init(&sem_C, 0, 0);
	pthread_create(&A_seq, NULL, print_A_seq, NULL);
	pthread_create(&B_seq, NULL, print_B_seq, NULL);
	pthread_create(&C_seq, NULL, print_C_seq, NULL);
	pthread_join(A_seq, NULL);
	pthread_join(B_seq, NULL);
	pthread_join(C_seq, NULL); printf("\n");
	return 0;
}
