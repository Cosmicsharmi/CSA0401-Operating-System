#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define SIZE 5
int buffer[SIZE], count = 0;
sem_t empty, full;
pthread_mutex_t mutex;
void *producer(void *arg) 
{
    int item = 1;
    while (1) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[count++] = item;
        printf("Producer Produced: %d\n", item++);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
}
void *consumer(void *arg) 
{
    while (1) 
	{
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        printf("Producer Consumed: %d\n", buffer[--count]);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
}
int main() 
{
    pthread_t prod, cons;
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
