#include "queue.h"

int add_c_code(int a, int b)
{
    return a + b;
}

int add_with_cb(int a, int b, int (*cb)(int, int))
{
    return cb(a, b);
}