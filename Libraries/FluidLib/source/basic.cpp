////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "basic.h"

using namespace fluid;

////////// bool inRangeSizeX/Y/Z /////////////////////////////////////////////
// Описание : basic.h.                                                      //
//////////////////////////////////////////////////////////////////////////////

bool fluid::inRangeSizeX(int sizeX)
{
    return sizeX >= MIN_SIZE_X && sizeX <= MAX_SIZE_X;
}

bool fluid::inRangeSizeY(int sizeY)
{
    return sizeY >= MIN_SIZE_Y && sizeY <= MAX_SIZE_Y;
}

bool fluid::inRangeSizeZ(int sizeZ)
{
    return sizeZ >= MIN_SIZE_Z && sizeZ <= MAX_SIZE_Z;
}

////////// int intPart ///////////////////////////////////////////////////////
// Описание : basic.h.                                                      //
//////////////////////////////////////////////////////////////////////////////

int fluid::intPart(Real number, Real increment)
{
    int step = 0;
    
    // Проверяем корректность входных данных
    if (number < 0 || increment <= 0)
    {
        throw FluidException(1);
    }
    
    // Добавляем приращения
    while (step * increment < number)
    {
        ++step;
    }
    return step - 1;
}

////////// struct SPoint /////////////////////////////////////////////////////
// Описание : basic.h.                                                      //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор (обнуляет поля)
Point::Point()
{
    value    = 0;
    isInArea = false;
}