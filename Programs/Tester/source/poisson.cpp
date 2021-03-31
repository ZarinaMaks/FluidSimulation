////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "fluidlib2d.h"
#include "poisson_tester.h"
#include <iostream>
#include <ctime>

namespace fluid
{
    void printFieldArea(const SField2D& field)
    {
        for (int i = 0; i < field.getSizeX(); ++i)
        {
            for (int j = 0; j < field.getSizeY(); ++j)
            {
                std::cout << field.area(i, j);
            }
            std::cout << "\n";
        }
    }
}

int main()
{
    int sizeX = 101;
    int sizeY = 101;
    
    fluid::Real       level = 0;
    fluid::Real  constValue = 0;
    fluid::Real borderValue = 0;
    fluid::Real       alpha = 2;
    fluid::Real       betta = 4;
    
    fluid::SField2D field1;
    fluid::SField2D field2;
    
    fluid::AreaCreator2D areaCreator;
    fluid::PoissonChecker2D checker;
    fluid::Poisson2D solver;
    fluid::Operator2D oper;
    
    // Инициализация генератора случайных чисел
    srand(time(0));
    oper.initialize(sizeX, sizeY);
    solver.initialize(sizeX, sizeY, oper);
    
    // Инициализация размеров
    field1.resize(sizeX, sizeY);
    field1.resetArea(true);
    field2.resize(sizeX, sizeY);
    field2.resetArea(true);
    areaCreator.randomConfig(sizeX, sizeY, 10, 10);
    
    // Чтение параметров инициализации
    std::cout << "\nInput value : ";
    std::cin >> level >> borderValue >> constValue;
    
    // Инициализация значений полей
    field1.resetField(borderValue);
    field2.resetField(constValue);
    
    // Генерация рабочих областей
    areaCreator.createPerlinNoiseArea(field1, level);
    areaCreator.createPerlinNoiseArea(field2, level);
    
    std::cout << "\nError (without solving) : ";
    std::cout << checker.getError(field1, field2, alpha, betta);
    
    solver.solve(field1, field2, alpha, betta);
    
    std::cout << "\nError (with solving)    : ";
    std::cout << checker.getError(field1, field2, alpha, betta);
    
    return 0;
}