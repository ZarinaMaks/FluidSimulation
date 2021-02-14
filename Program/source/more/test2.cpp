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
    field(1, 0) = 2;
    field(1, 1) = 4;
    field(1, 2) = 6;
    field(1, 3) = 8;
    field(2, 0) = 3;
    field(2, 1) = 4;
    field(2, 2) = 8;
    field(2, 3) = 12;
    field(3, 0) = 16;
    field(3, 1) = 16;
    field(3, 2) = 24;
    field(3, 3) = 32;
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
    ScalarField2D scalarField(sizeX, sizeY);
    VectorField2D vectorField(sizeX, sizeY);
    Operator      testOperator;
    
    try
    {
        initBaseField(scalarField);
        testOperator.resize2D(sizeX, sizeY);
        
        std::cout << "Scalar field :\n";
        printScalarField2D(scalarField);
        std::cout << "Vector field :\n";
        testOperator.grad(scalarField, vectorField);
        std::cout << "Finish field 'X' :\n";
        printScalarField2D(vectorField.x());
        std::cout << "Finish field 'Y' :\n";
        printScalarField2D(vectorField.y());
    }
    catch (const err::FluidException& ex)
    {
        std::cout << ex.error();
    }
    
    return 0;
}