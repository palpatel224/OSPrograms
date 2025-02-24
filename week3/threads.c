#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 4

void *counter(void *arg)
{
    int *count = (int *)arg;
    for (int i = 0; i < 1000000; i++)
    {
        mutext
        (*count)++;
    }
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int shared_count = 0;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, counter, &shared_count);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Final count: %d (Expected 4000000)\n", shared_count);
    return 0;
}
