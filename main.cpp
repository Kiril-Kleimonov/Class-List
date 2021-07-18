#include "Class_List.h"
#include <cstddef>
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    List<int> A = {1, 4, 6}; A.DEBUGprint();
    List<int> B {2, 0, 0};   B.DEBUGprint();

    A = B;
    A.DEBUGprint();

    B.clear();
    B.DEBUGprint();

    B = {1, 3, 5};
    B.DEBUGprint();    


    return 0;
}