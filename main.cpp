#include "Class_List.h"
#include <cstddef>
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    List<int> A(4, 6); A.DEBUGprint();
    A.add_by(6, 3); A.DEBUGprint();


    return 0;
}