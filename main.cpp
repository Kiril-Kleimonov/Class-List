#include "Class_List.h"
#include <cstddef>
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    List<int> A {0, 1, 2, 3, 4, 5, 6};    A.DEBUGprint();

    A.pop_by(4);                          A.DEBUGprint();
    A.pop_by(0);                          A.DEBUGprint();
    A.pop_by(4);                          A.DEBUGprint();

    return 0;
}