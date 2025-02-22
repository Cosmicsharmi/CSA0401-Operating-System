#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_PHILOSOPHERS 5
pthread_t philosophers[NUM_PHILOSOPHERS];
sem_t chopsticks[NUM_PHILOSOPHERS];
void *philosopher(void *arg) 
{
    int id = *(int *)arg;

    while (1) 
	{
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);
        sem_wait(&chopsticks[id]);
        sem_wait(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d is eating...\n", id);
        sleep(2);
        sem_post(&chopsticks[id]);
        sem_post(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d finished eating and is thinking again...\n", id);
        sleep(1);
    }
}
int main() 
{
    int i, ids[NUM_PHILOSOPHERS];
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
        sem_init(&chopsticks[i], 0, 1);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) 
	{
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(philosophers[i], NULL);
    return 0;
}
