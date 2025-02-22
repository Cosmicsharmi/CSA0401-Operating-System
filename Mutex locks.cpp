#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>  
pthread_mutex_t mutex;
int shared_resource = 0;
void *process(void *arg) 
{
    intptr_t id = (intptr_t)arg; 
    pthread_mutex_lock(&mutex);
    printf("Process %ld entered critical section.\n", id);
    shared_resource++;
    printf("Process %ld updated shared resource: %d\n", id, shared_resource);
    sleep(1);
    printf("Process %ld exiting critical section.\n", id);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
int main() 
{
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&t1, NULL, process, (void *)(intptr_t)1);
    pthread_create(&t2, NULL, process, (void *)(intptr_t)2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}