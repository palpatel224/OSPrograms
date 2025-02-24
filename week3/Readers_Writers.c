#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <windows.h>

typedef struct
{
    sem_t write_mutex;
    pthread_mutex_t read_mutex;
    int reader_count;
} rw_lock;

void rw_init(rw_lock *lock)
{ 
    sem_init(&lock->write_mutex, 0, 1);
    pthread_mutex_init(&lock->read_mutex, NULL);
    lock->reader_count = 0;
}

void reader_lock(rw_lock *lock)
{
    pthread_mutex_lock(&lock->read_mutex);
    lock->reader_count++;
    if (lock->reader_count == 1)
    {
        sem_wait(&lock->write_mutex);
    }
    pthread_mutex_unlock(&lock->read_mutex);
}

void reader_unlock(rw_lock *lock)
{
    pthread_mutex_lock(&lock->read_mutex);
    lock->reader_count--;
    if (lock->reader_count == 0)
    {
        sem_post(&lock->write_mutex);
    }
    pthread_mutex_unlock(&lock->read_mutex);
}

void writer_lock(rw_lock *lock)
{
    sem_wait(&lock->write_mutex);
}

void writer_unlock(rw_lock *lock)
{
    sem_post(&lock->write_mutex);
}

rw_lock lock;
int shared_data = 0;

void *reader(void *arg)
{
    int id = *((int *)arg);
    for (int i = 0; i < 3; i++)
    {
        reader_lock(&lock);
        printf("Reader %d reading: %d\n", id, shared_data);
        Sleep(1000);
        reader_unlock(&lock);
        Sleep(500);
    }
    return NULL;
}

void *writer(void *arg)
{
    int id = *((int *)arg);
    for (int i = 0; i < 2; i++)
    {
        writer_lock(&lock);
        shared_data++;
        printf("Writer %d modified data to: %d\n", id, shared_data);
        Sleep(1500);
        writer_unlock(&lock);
        Sleep(1000);
    }
    return NULL;
}

int main()
{
    pthread_t readers[3], writers[2];
    int reader_ids[3] = {1, 2, 3};
    int writer_ids[2] = {1, 2};

    rw_init(&lock);

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&lock.read_mutex);
    sem_destroy(&lock.write_mutex);

    return 0;
}
