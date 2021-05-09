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
    field(1, 1) = 3;
    field(1, 2) = 4;
    field(1, 3) = 5;
    field(2, 0) = 3;
    field(2, 1) = 4;
    field(2, 2) = 5;
    field(2, 3) = 6;
    field(3, 0) = 4;
    field(3, 1) = 5;
    field(3, 2) = 6;
    field(3, 3) = 7;
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
        initBaseField(vectorField.x());
        initBaseField(vectorField.y());
        testOperator.resize2D(sizeX, sizeY);
        
        std::cout << "Vector field 'X' :\n";
        printScalarField2D(vectorField.x());
        std::cout << "Vector field 'Y' :\n";
        printScalarField2D(vectorField.y());
        testOperator.div(vectorField, scalarField);
        std::cout << "Finish field :\n";
        printScalarField2D(scalarField);
    }
    catch (const err::FluidException& ex)
    {
        std::cout << ex.error();
    }
    
    return 0;
}