#include "foo.h"
#include "foover.h"
#include <iostream>

int AddInt( int a, int b )
{
    return a + b;
}


void print_versions()
{
    std::cout << "Foo Version " << Foo_VERSION_MAJOR << "."
              << Foo_VERSION_MINOR << std::endl;
}

