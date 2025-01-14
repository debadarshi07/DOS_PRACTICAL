#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5  // Size of the buffer

// The shared buffer
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
sem_t empty, full, mutex;

// Producer function
void *producer(void *param) {
    int item;
    while (1) {
        // Produce an item (for simplicity, we use an integer)
        item = rand() % 100;

        // Wait for an empty slot
        sem_wait(&empty);

        // Lock the buffer for writing
        sem_wait(&mutex);

        // Produce item into the buffer
        buffer[in] = item;
        printf("Produced: %d at position %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        // Unlock the buffer
        sem_post(&mutex);

        // Signal that a new item is in the buffer
        sem_post(&full);

        // Sleep for a while to simulate production time
        sleep(rand() % 3);
    }
}

// Consumer function
void *consumer(void *param) {
    int item;
    while (1) {
        // Wait for a filled slot
        sem_wait(&full);

        // Lock the buffer for reading
        sem_wait(&mutex);

        // Consume the item from the buffer
        item = buffer[out];
        printf("Consumed: %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        // Unlock the buffer
        sem_post(&mutex);

        // Signal that there is an empty slot in the buffer
        sem_post(&empty);

        // Sleep for a while to simulate consumption time
        sleep(rand() % 3);
    }
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // Buffer starts empty
    sem_init(&full, 0, 0);             // Buffer starts full = 0
    sem_init(&mutex, 0, 1);            // Mutex for mutual exclusion, initially unlocked

    // Create the producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for the threads to finish (they never will in this case)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Clean up semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}