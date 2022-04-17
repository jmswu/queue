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

    typedef struct queue_typeDef *queue_handle_t;

    typedef struct
    {
        void *ptrData;
        size_t len;
    } queue_obj_t;

    queue_handle_t queue_create(void);
    void queue_destroy(queue_handle_t const handle);
    int queue_getItemCount(queue_handle_t const handle);
    int queue_wait(queue_handle_t const handle);
    bool queue_pushBack(queue_handle_t const handle, queue_obj_t *const obj);
    bool queue_pushFront(queue_handle_t const handle, queue_obj_t *const obj);
    queue_obj_t queue_peek(queue_handle_t const handle);
    queue_obj_t queue_pop(queue_handle_t const handle);

    void queue_helper_popAndFreeMemory(queue_handle_t const handle, void (*const cbProcessData)(queue_obj_t *const obj));
    bool queue_helper_pushBackCopy(queue_handle_t const handle, queue_obj_t *const obj);
    bool queue_helper_pushFrontCopy(queue_handle_t const handle, queue_obj_t *const obj);
    bool queue_helper_isObjValid(queue_obj_t *const obj);

#ifdef __cplusplus
}
#endif