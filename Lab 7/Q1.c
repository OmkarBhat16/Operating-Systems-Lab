#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_SIZE 20

sem_t pmutex, cmutex, empty, full;
int buffer[MAX_SIZE] = {0};
int item = 0, in = 0, out = 0;

void* producer(void* arg) {
    for (int j = 0; j < 5; j++) {  // Produce 5 items
        sem_wait(&empty);
        sem_wait(&pmutex);
        
        item++;
        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % MAX_SIZE;

        sem_post(&pmutex);
        sem_post(&full);

        // Simulate time taken to produce an item
        usleep(rand() % 100000); // Sleep for up to 100ms
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int j = 0; j < 5; j++) {  // Consume 5 items
        sem_wait(&full);
        sem_wait(&cmutex);

        item = buffer[out];
        buffer[out] = 0;
        printf("Consumed: %d\n", item);
        out = (out + 1) % MAX_SIZE;

        sem_post(&cmutex);
        sem_post(&empty);

        // Simulate time taken to consume an item
        usleep(rand() % 100000); // Sleep for up to 100ms
    }
    return NULL;
}

void bufferOut() {
    printf("Buffer State: ");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    // Initialize semaphores
    sem_init(&pmutex, 0, 1);
    sem_init(&cmutex, 0, 1);
    sem_init(&empty, 0, MAX_SIZE);
    sem_init(&full, 0, 0);

    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    bufferOut();

    // Clean up semaphores
    sem_destroy(&pmutex);
    sem_destroy(&cmutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
