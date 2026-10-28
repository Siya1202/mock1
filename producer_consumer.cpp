#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define BUF 5
#define ITEMS 10

int buffer[BUF], in = 0, out = 0;
sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = i;
        std::cout << "Produced item " << i << " at slot " << in << std::endl;
        in = (in + 1) % BUF;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        usleep(50000);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        std::cout << " Consumed item " << item << " from slot " << out << std::endl;
        out = (out + 1) % BUF;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        usleep(90000);
    }
    return NULL;
}

int main() {
    pthread_t pt, ct;
    sem_init(&empty, 0, BUF);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&pt, NULL, producer, NULL);
    pthread_create(&ct, NULL, consumer, NULL);
    pthread_join(pt, NULL);
    pthread_join(ct, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    std::cout << "Producer-Consumer finished without overflow/underflow." << std::endl;                                                          
    return 0;
}
