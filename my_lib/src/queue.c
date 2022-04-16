#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "queue.h"

typedef struct node_typeDef
{
    void *ptrData;
    size_t len;
    struct node_typeDef *next;
} node_typeDef;

typedef struct queue_typeDef
{
    pthread_mutex_t mutex;
    sem_t sem;
    node_typeDef *head;
    node_typeDef *tail;
} queue_typeDef;

queue_handle_t queue_create(void)
{
    queue_handle_t handle = (queue_handle_t)malloc(sizeof(queue_typeDef));

    if (handle != NULL)
    {
        handle->head = NULL;
        handle->tail = NULL;
        pthread_mutex_init(&handle->mutex, NULL);
        sem_init(&handle->sem, 0, 0);
    }

    return handle;
}

void queue_destroy(queue_handle_t handle)
{
    if (handle == NULL)
        return;

    pthread_mutex_destroy(&handle->mutex);
    sem_destroy(&handle->sem);
    free(handle);
}
