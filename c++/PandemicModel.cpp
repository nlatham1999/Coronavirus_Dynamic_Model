//PandemicModel.cpp
//Nick Latham 3/26/2020


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

#include <iostream>
#include <string> 
#include "Population.h"

using namespace std;

int main()
{
    Population pop(100, 24, 37, 27); //100,000 people, 24% < 18, 37% 19-44, 27% 44-65

    pop.printPop();
}


