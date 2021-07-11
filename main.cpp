#include "Class_List.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    List<int> A(3, 5);
    std::cout << A.length() << '\n';
    A.DEBUGprint();
    
    List<int> B = A;
    std::cout << B.length() << '\n';
    B.DEBUGprint();

    return 0;
}