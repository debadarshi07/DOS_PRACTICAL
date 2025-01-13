#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Semaphores for each fork (we need one semaphore per fork)
sem_t forks[NUM_PHILOSOPHERS];

// Mutex for output synchronization
pthread_mutex_t print_lock;

// Philosopher function
void* philosopher(void* num) {
    int id = *((int*) num);
    
    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", id);
        usleep(rand() % 1000); // Simulate thinking time

        // Pick up left fork
        sem_wait(&forks[id]);  // Wait for the left fork (id)
        printf("Philosopher %d picked up left fork.\n", id);

        // Pick up right fork
        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);  // Wait for the right fork (id + 1 % NUM_PHILOSOPHERS)
        printf("Philosopher %d picked up right fork.\n", id);

        // Eating
        pthread_mutex_lock(&print_lock);
        printf("Philosopher %d is eating.\n", id);
        pthread_mutex_unlock(&print_lock);
        usleep(rand() % 1000); // Simulate eating time

        // Put down right fork
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d put down right fork.\n", id);

        // Put down left fork
        sem_post(&forks[id]);
        printf("Philosopher %d put down left fork.\n", id);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize semaphores and mutex
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1); // Each fork starts as available (semaphore value = 1)
    }
    pthread_mutex_init(&print_lock, NULL);

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, (void*)&philosopher_ids[i]);
    }

    // Join philosopher threads (this will run indefinitely, so we don't actually join them here)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up semaphores and mutex (never reached in this infinite loop)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&print_lock);

    return 0;
}