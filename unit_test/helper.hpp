#pragma onece

#include <iostream>
#include <cassert>
#include "../my_lib/include/queue.h"

struct TestQueueObj
{
    TestQueueObj(std::string str, const size_t buffer_size)
    {
        assert(str.length() < buffer_size);

        buffer = (char *)malloc(buffer_size);
        std::sprintf(buffer, "%s", str.c_str());
        obj = {
            .ptrData = (void *)buffer,
            .len = buffer_size};
    }

    queue_obj_t getTestQueueObj()
    {
        return obj;
    }

    ~TestQueueObj()
    {
        free(buffer);
    }

private:
    char *buffer;
    queue_obj_t obj;
};