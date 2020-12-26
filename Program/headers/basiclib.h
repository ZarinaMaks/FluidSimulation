#ifndef BASICLIB_H
#define BASICLIB_H

////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

namespace fluid
{
    // Универсальный вещественный тип
    typedef double Real;
    
    // Максимальный и минимальный размеры поля "Field" по "X"
    const int MAX_SIZE_X = 1000;
    const int MIN_SIZE_X = 3;
    
    // Максимальный и минимальный размеры поля "Field" по "Y"
    const int MAX_SIZE_Y = 1000;
    const int MIN_SIZE_Y = 3;
    
    // Максимальный и минимальный размеры поля "Field" по "Z"
    const int MAX_SIZE_Z = 1000;
    const int MIN_SIZE_Z = 3;
    
    // Количество шагов для метода итераций Якоби
    const int JACOBI_STEP_NUMBER = 100;
    
    // Приращения аргументов
    const Real DT = 1.0;
    const Real DS = 1.0;
    const Real DX = DS;
    const Real DY = DS;
    const Real DZ = DS;
    
    ////////// bool inRangeSizeX/Y/Z /////////////////////////////////////////
    // Возвращают "true", если значение аргумента не выходит за границы.    //
    //////////////////////////////////////////////////////////////////////////
    
    bool inRangeSizeX(int sizeX);
    
    bool inRangeSizeY(int sizeY);
    
    bool inRangeSizeZ(int sizeZ);
}

#endif