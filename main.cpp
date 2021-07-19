#include "Class_List.h"
#include <cstddef>
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    List<int> A {0, 1, 2, 3, 4, 5, 6};
    A.DEBUGprint(); std::cout << A.length() << '\n';

    List<int> B = A.pop_slice(3, 3);
    A.DEBUGprint(); std::cout << A.length() << '\n';
    B.DEBUGprint(); std::cout << B.length() << '\n';

    return 0;
}