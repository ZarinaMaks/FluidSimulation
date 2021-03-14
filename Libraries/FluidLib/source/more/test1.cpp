#include "toolslib.h"
#include <iostream>

using namespace fluid;

const int sizeX = 4;
const int sizeY = 4;

void initBaseField(ScalarField2D& field)
{
    field(0, 0) = 1;
    field(0, 1) = 2;
    field(0, 2) = 3;
    field(0, 3) = 4;
    field(1, 0) = 0;
    field(1, 1) = 1;
    field(1, 2) = 1;
    field(1, 3) = 1;
    field(2, 0) = 2;
    field(2, 1) = 1;
    field(2, 2) = 1;
    field(2, 3) = 6;
    field(3, 0) = 7;
    field(3, 1) = 1;
    field(3, 2) = 0;
    field(3, 3) = 5;
}

void initFreeField(ScalarField2D& field)
{
    field(0, 0) = 1;
    field(0, 1) = 1;
    field(0, 2) = 1;
    field(0, 3) = 1;
    field(1, 0) = 1;
    field(1, 1) = 3;
    field(1, 2) = 17;
    field(1, 3) = 1;
    field(2, 0) = 1;
    field(2, 1) = 0.5;
    field(2, 2) = -15.4;
    field(2, 3) = 1;
    field(3, 0) = 1;
    field(3, 1) = 1;
    field(3, 2) = 1;
    field(3, 3) = 1;
}

void printScalarField2D(const ScalarField2D& field)
{
    for (int j = 0; j < field.getSizeY(); ++j)
    {
        for (int i = 0; i < field.getSizeX(); ++i)
        {
            std::cout << field(i, j) << ", ";
        }
        std::cout << "\n";
    }
}

int main()
{
    ScalarField2D baseField(sizeX, sizeY);
    ScalarField2D freeField(sizeX, sizeY);
    Real          alpha = -1;
    Real          betta = 4;
    Poisson       testPoisson;
    
    initBaseField(baseField);
    initFreeField(freeField);
    testPoisson.resize2D(sizeX, sizeY);
    
    std::cout << "Free field :\n";
    printScalarField2D(freeField);
    std::cout << "Base field :\n";
    printScalarField2D(baseField);
    testPoisson.solve(baseField, freeField, alpha, betta);
    std::cout << "Finish field :\n";
    printScalarField2D(baseField);
    
    return 0;
}