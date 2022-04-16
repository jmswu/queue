/**
 * @file queue.h
 * @author James Wu(jameswu62@yahoo.co.nz)
 * @brief C code example
 * @version 0.1
 * @date 2022-02-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct queue_typeDef* queue_handle_t;

    queue_handle_t queue_create(void);
    void queue_destroy(queue_handle_t handle);
    int queue_getItemCount(queue_handle_t handle);
    void queue_wait(queue_handle_t handle);
    void *queue_peek(queue_handle_t handle);
    bool queue_enqueue(queue_handle_t handle, void *const obj, const size_t len);
    bool queue_enqueueCopy(queue_handle_t handle, void *const obj, const size_t len);
    void *queue_dequeue(queue_handle_t handle);
    void queue_dequeueAndFreeMemory(queue_handle_t handle, void (*cbProcessData)(void *const obj, const size_t len));

#ifdef __cplusplus
}
#endif