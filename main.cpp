#include "Class_List.h"
#include <cstddef>
#include <iostream>
#include <string>

int dec(int a)
{
    return a+1;
}

int main(int argc, char const *argv[])
{
    List<int> A {0, 1, 2, 3, 4, 5, 6};
    A.DEBUGprint(); std::cout << A.length() << '\n';

    List<int> B = A.map(dec);
    B.DEBUGprint(); std::cout << B.length() << '\n';

    return 0;
}