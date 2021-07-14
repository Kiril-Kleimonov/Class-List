#include "Class_List.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    List<int> A(2, 4);
    std::cout << A.length() << '\n';
    A.DEBUGprint();
    
    List<int> B(6, 3);
    std::cout << B.length() << '\n';
    B.DEBUGprint();

    A = A + B;
    std::cout << A.length() << '\n';
    A.DEBUGprint();
    std::cout << B.length() << '\n';
    B.DEBUGprint();

    return 0;
}