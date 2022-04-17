#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "queue.h"

int main(int argc, char **argv)
{
    // Dummy code to get rid of unused parameter warning
    (void)argv;
    (void)argc;

    std::printf("hello world!\n");

    // Test create and destroy. There should be no significant
    // memory userage after this. If there is significant memory
    // userage, there is a memory leak.
    for (size_t i = 0; i < 1024UL * 1024UL * 512UL; i++)
    {
        queue_handle_t handle = queue_create();
        queue_destroy(handle);
    }

    return EXIT_SUCCESS;
}