#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t wrt;
pthread_mutex_t mutex;
int read_count = 0;
int data = 0;
void *reader(void *arg) 
{
    int id = *(int *)arg;
    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1) 
	{
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    printf("Reader %d: Read data = %d\n", id, data);
    sleep(1);
    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) 
	{
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void *writer(void *arg) 
{
    int id = *(int *)arg;
    sem_wait(&wrt);
    data++;
    printf("Writer %d: Wrote data = %d\n", id, data);
    sleep(1);
    sem_post(&wrt);
    return NULL;
}
int main() 
{
    pthread_t r[5], w[2];
    int id[5] = {1, 2, 3, 4, 5};
    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 5; i++) 
	{
        pthread_create(&r[i], NULL, reader, &id[i]);
    }
    for (int i = 0; i < 2; i++) 
	{
        pthread_create(&w[i], NULL, writer, &id[i]);
    }
    for (int i = 0; i < 5; i++) 
	{
        pthread_join(r[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(w[i], NULL);
    }
    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);
    return 0;
}
