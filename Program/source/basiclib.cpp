////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "basiclib.h"

////////// bool inRangeSizeX/Y/Z /////////////////////////////////////////////
// Описание : basiclib.h.                                                   //
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