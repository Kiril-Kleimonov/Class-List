#include "Class_List.h"
#include <cstddef>
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    List<int> A(3, 10);
    A.DEBUGprint();

    for (size_t i = 0; i < A.length(); ++i)
    {     
        A[i] = 6;
        A.DEBUGprint();
    }

    return 0;
}