#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "queue.h"

void runTest_queueCreateAndDestroy(void);
void runTest_queuePushAndPop(void);

int main(int argc, char **argv)
{
    // Dummy code to get rid of unused parameter warning
    (void)argv;
    (void)argc;

    runTest_queueCreateAndDestroy();
    runTest_queuePushAndPop();

    return EXIT_SUCCESS;
}

void runTest_queueCreateAndDestroy(void)
{
    queue_handle_t handle = NULL;
    std::printf("Testing queue create and destroy...\n");

    // Test create and destroy. There should be no significant
    // memory userage after this. If there is significant memory
    // userage, there is a memory leak.

    for (size_t i = 0; i < 1024UL * 1024UL * 256UL; i++)
    {
        handle = queue_create();
        queue_destroy(handle);
    }
}

void runTest_queuePushAndPop(void)
{
    std::printf("Testing queue push and pop...\n");

    queue_handle_t handle = queue_create();
    const int buf_size = 32;
    char *buffer = (char *)malloc(buf_size);
    queue_obj_t push_obj = {
        .ptrData = buffer,
        .len = buf_size};

    // Test push and pop. There should be no significant
    // memory userage after this. If there is significant memory
    // userage, there is a memory leak.

    for (size_t i = 0; i < 1024UL * 1024UL * 256UL; i++)
    {
        queue_pushBack(handle, &push_obj);
        queue_obj_t pop_obj = queue_pop(handle);
    }

    free(buffer);
    queue_destroy(handle);
}