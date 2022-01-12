#include <iostream>

#include "LibraryCode.hpp"

int main(int argc, const char** argv)
{
    int s = sum(2, 3);
    std::cout << "Actual aplication\n"
              << "sum = " << s << '\n';
    return 0;
}