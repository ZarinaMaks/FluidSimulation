#include "modeler2d.h"

// Размеры рабочего поля
const int SIZE_X = 200;
const int SIZE_Y = 40;

// Количество итераций в цикле моделирования
const int CYCLE_NUM = 500;

int main()
{
    // Класс для моделирования течения жидкости
    model::MainModeler2D modeler;
    
    try
    {
        // Инициализация и "CYCLE_NUM" итераций моделирования
        modeler.initialize(SIZE_X, SIZE_Y);
        modeler.run(CYCLE_NUM);
    }
    catch (fluid::FluidException& ex)
    {
        std::cout << "\n" << ex.what() << " (" << ex.error() << ")";
    }
    catch (...)
    {
        std::cout << "\nUnknown error!";
    }
    
    return 0;
}