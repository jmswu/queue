#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include "queue.h"

typedef struct __attribute__((aligned(32)))
node_typeDef
{
    queue_obj_t obj;
    struct node_typeDef *next;
} node_typeDef;

typedef struct __attribute__((aligned(128)))
queue_typeDef
{
    pthread_mutex_t mutex;
    sem_t sem;
    node_typeDef *head;
    node_typeDef *tail;
    int itemCount;
} queue_typeDef;

static inline node_typeDef *helper_createNode(queue_obj_t *obj);

queue_handle_t queue_create(void)
{
    queue_handle_t handle = (queue_handle_t)malloc(sizeof(queue_typeDef));
    assert(handle != NULL);

    handle->head = NULL;
    handle->tail = NULL;
    handle->itemCount = 0;
    pthread_mutex_init(&handle->mutex, NULL);
    const int SHARE_BETWEEN_THREAD = 0;
    const int INIT_VALUE = 0;
    sem_init(&handle->sem, SHARE_BETWEEN_THREAD, INIT_VALUE);

    return handle;
}

void queue_destroy(queue_handle_t handle)
{
    assert(handle != NULL);
    pthread_mutex_destroy(&handle->mutex);
    sem_destroy(&handle->sem);
    free(handle);

    handle = NULL;
}

int queue_getItemCount(const queue_handle_t handle)
{
    assert(handle != NULL);
    pthread_mutex_lock(&handle->mutex);
    int itemCount = handle->itemCount;
    pthread_mutex_unlock(&handle->mutex);

    // muti thead invariant value check
    assert(itemCount >= 0);

    return itemCount;
}

int queue_wait(const queue_handle_t handle)
{
    assert(handle != NULL);
    return sem_wait(&handle->sem);
}

bool queue_pushBack(const queue_handle_t handle, queue_obj_t *const obj)
{
    assert(handle != NULL);
    assert(obj != NULL);

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

    handle->itemCount++;

    // muti thead invariant value check
    assert(handle->itemCount >= 0);

    sem_post(&handle->sem);

    pthread_mutex_unlock(&handle->mutex);

    return true;
}

queue_obj_t queue_peek(const queue_handle_t handle)
{
    queue_obj_t obj = {
        .ptrData = NULL,
        .len = 0};

    if (handle == NULL)
    {
        return obj;
    }

    pthread_mutex_lock(&handle->mutex);
    obj = handle->head->obj;
    pthread_mutex_unlock(&handle->mutex);

    return obj;
}

queue_obj_t queue_pop(const queue_handle_t handle)
{
    queue_obj_t obj = {
        .ptrData = NULL,
        .len = 0};

    if (handle == NULL)
    {
        return obj;
    }

    // handle queue is empty
    if (queue_getItemCount(handle) <= 0)
    {
        return obj;
    }

    pthread_mutex_lock(&handle->mutex);

    // store the head node and move the head
    // to next node
    node_typeDef *temp = handle->head;
    handle->head = handle->head->next;

    // if head is NULL, change tail into NULL
    if (handle->head == NULL)
    {
        handle->tail = NULL;
    }

    // make a copy of the queue object
    obj = temp->obj;

    free(temp);

    if (handle->itemCount > 0) 
    {
        handle->itemCount--;
    }

    pthread_mutex_unlock(&handle->mutex);

    return obj;
}

bool queue_helper_isObjValid(queue_obj_t *const obj)
{
    if (obj == NULL)
    {
        return false;
    }

    if (obj->len == 0)
    {
        return false;
    }

    if (obj->ptrData == NULL)
    {
        return false;
    }

    return true;
}

static inline node_typeDef *helper_createNode(queue_obj_t *const obj)
{
    node_typeDef *node = (node_typeDef *)malloc(sizeof(node_typeDef));
    node->obj = *obj;
    node->next = NULL;
    return node;
}