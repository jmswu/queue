#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "add.hpp"
#include "add.h"

int main(int argc, char **argv)
{
    // dummy code to get rid of unused parameter warning
    (void)argv;
    (void)argc;

    std::cout<< "CXX code: 1 + 2 is " << add(1, 2) << std::endl;        // CPP code
    std::cout<< "CXX code: 1 + 2 is " << add_c_code(1, 2) << std::endl; // C   code

    return EXIT_SUCCESS;
}