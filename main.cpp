#include "Class_List.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    List<int> A(3,2);
    List<List<int>> AA(A, 2);
    std::cout << A.length() << '\n';
    // A.DEBUGprint();
    
    // List<int> B(6, 3);
    // std::cout << B.length() << '\n';
    // B.DEBUGprint();

    std::cout << A.pop_end() << '\n';
    std::cout << A.length() << '\n';
    std::cout << A.pop_begin() << '\n';
    // A.DEBUGprint();
    // std::cout << B.length() << '\n';
    // B.DEBUGprint();

    return 0;
}