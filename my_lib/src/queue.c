#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "queue.h"

typedef struct node_typeDef
{
    queue_obj_t obj;
    struct node_typeDef *next;
} node_typeDef;

typedef struct queue_typeDef
{
    pthread_mutex_t mutex;
    sem_t sem;
    node_typeDef *head;
    node_typeDef *tail;
} queue_typeDef;

static inline node_typeDef *helper_createNode(queue_obj_t *const obj);

queue_handle_t queue_create(void)
{
    queue_handle_t handle = (queue_handle_t)malloc(sizeof(queue_typeDef));

    if (handle != NULL)
    {
        handle->head = NULL;
        handle->tail = NULL;
        pthread_mutex_init(&handle->mutex, NULL);
        const int SHARE_BETWEEN_THREAD = 0;
        const int INIT_VALUE = 0;
        sem_init(&handle->sem, SHARE_BETWEEN_THREAD, INIT_VALUE);
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

int queue_getItemCount(queue_handle_t handle)
{
    if (handle == NULL)
        return 0;

    pthread_mutex_lock(&handle->mutex);
    int itemCount = 0;
    int rc = sem_getvalue(&handle->sem, &itemCount);
    pthread_mutex_unlock(&handle->mutex);

    const int SUCCESS = 0;

    return rc == SUCCESS ? itemCount : 0;
}

int queue_wait(queue_handle_t handle)
{
    if (handle == NULL)
        return -1;

    return sem_wait(&handle->sem);
}

bool queue_pushBack(queue_handle_t const handle, queue_obj_t *const obj)
{
    if ((handle == NULL) || (obj == NULL))
        return false;

    node_typeDef *newNode = helper_createNode(obj);

    pthread_mutex_lock(&handle->mutex);

    if (handle->head == NULL)
    {
        handle->head = newNode;
        handle->tail = newNode;
    }
    else
    {
        handle->tail->next = newNode;
        handle->tail = newNode;
    }

    sem_post(&handle->sem);

    pthread_mutex_unlock(&handle->mutex);

    return true;
}

queue_obj_t queue_peek(queue_handle_t const handle)
{
    queue_obj_t obj = {
        .ptrData = NULL,
        .len = 0};

    if (handle == NULL)
        return obj;

    pthread_mutex_lock(&handle->mutex);
    obj = handle->head->obj;
    pthread_mutex_unlock(&handle->mutex);
}

queue_obj_t queue_pop(queue_handle_t const handle)
{
    queue_obj_t obj = {
        .ptrData = NULL,
        .len = 0};

    if (handle == NULL)
        return obj;

    pthread_mutex_lock(&handle->mutex);

    // store the head node and move the head
    // to next node
    node_typeDef *temp = handle->head;
    handle->head = handle->head->next;

    // if head is NULL, change tail into NULL
    if (handle->head == NULL)
        handle->tail = NULL;

    // make a copy of the queue object
    obj = temp->obj;

    free(temp);

    pthread_mutex_unlock(&handle->mutex);

    return obj;
}

bool queue_helper_isObjValid(queue_obj_t *const obj)
{
    if (obj == NULL)
        return false;

    if (obj->len == 0)
        return false;

    if (obj->ptrData == NULL)
        return false;

    return true;
}

static inline node_typeDef *helper_createNode(queue_obj_t *const obj)
{
    node_typeDef *node = (node_typeDef *)malloc(sizeof(node_typeDef));
    node->obj = *obj;
    node->next = NULL;
    return node;
}