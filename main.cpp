#include "Class_List.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    List<int> A(3, 3);
    std::cout << A.length() << '\n';
    A.add_end(32);
    std::cout << A.length() << '\n';
    A.add_begin(-34);
    std::cout << A.length() << '\n';
    A.DEBUGprint();
    return 0;
}