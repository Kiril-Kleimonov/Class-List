#include "Class_List.h"
#include <cstddef>
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    List<int> A(4, 6);          A.DEBUGprint();
    List<int> B(8, 6);          B.DEBUGprint();

    A.add_list(B, 6);           A.DEBUGprint();


    return 0;
}