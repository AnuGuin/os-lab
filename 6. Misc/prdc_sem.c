#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5   // Size of buffer

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty;  // Semaphore to count empty slots
sem_t full;   // Semaphore to count filled slots
pthread_mutex_t mutex;

// Function for producer thread
void* producer(void* arg) {
    int item;
    for (int i = 1; i <= 10; i++) {
        item = i;  // Produce an item

        sem_wait(&empty);            // Wait if no empty slots
        pthread_mutex_lock(&mutex);  // Lock the buffer

        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&full);               // Increase full slot count

        sleep(1); // Simulate delay
    }
    return NULL;
}

// Function for consumer thread
void* consumer(void* arg) {
    int item;
    for (int i = 1; i <= 10; i++) {
        sem_wait(&full);             // Wait if buffer is empty
        pthread_mutex_lock(&mutex);  // Lock the buffer

        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty);             // Increase empty slot count

        sleep(2); // Simulate delay
    }
    return NULL;
}

// Main function
int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, BUFFER_SIZE);  // Initially, buffer is empty
    sem_init(&full, 0, 0);             // Initially, no full slots
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
