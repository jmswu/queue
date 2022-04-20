#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "queue.h"
#include "unit_test/helper.hpp"

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
    TestQueueObj testQueue{"hello world.", 32};
    auto pushObj = testQueue.getTestQueueObj();
    
    // Test push and pop. There should be no significant
    // memory userage after this. If there is significant memory
    // userage, there is a memory leak.

    for (size_t i = 0; i < 1024UL * 1024UL * 256UL; i++)
    {
        queue_pushBack(handle, &pushObj);
        queue_obj_t pop_obj = queue_pop(handle);
    }

    queue_destroy(handle);
}