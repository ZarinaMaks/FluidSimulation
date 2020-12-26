////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "toolslib.h"

using namespace fluid;

////////// class Operator ////////////////////////////////////////////////////
// Описание : toolslib.h.                                                   //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (3) Конструктор копирования
Operator::Operator(const Operator& newOperator)
{
    *this = newOperator;
}

// (4) Устанавливается размер вспомогательного 2D поля
void Operator::resize2D(int sizeX, int sizeY)
{
    try
    {
        tempSF2D_.resize(sizeX, sizeY);
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (5) Устанавливается размер вспомогательного 3D поля
void Operator::resize3D(int sizeX, int sizeY, int sizeZ)
{
    try
    {
        tempSF3D_.resize(sizeX, sizeY, sizeZ);
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (6) 2D Градиент (Возвращает по ссылке векторное поле)
void Operator::grad(const ScalarField2D& inField, VectorField2D& outField)
{
    derX(inField, outField.x());
    derY(inField, outField.y());
}

// (7) 2D Дивергенция (Возвращает по ссылке скалярное поле)
void Operator::div(const VectorField2D& inField, ScalarField2D& outField)
{
    derX(inField.x(), outField);
    derY(inField.y(), tempSF2D_);
    outField += tempSF2D_;
}

// (8) 3D Градиент (Возвращает по ссылке векторное поле)
void Operator::grad(const ScalarField3D& inField, VectorField3D& outField)
{
    derX(inField, outField.x());
    derY(inField, outField.y());
    derZ(inField, outField.z());
}

// (9) 3D Дивергенция (Возвращает по ссылке скалярное поле)
void Operator::div(const VectorField3D& inField, ScalarField3D& outField)
{
    derX(inField.x(), outField);
    derY(inField.y(), tempSF3D_);
    outField += tempSF3D_;
    derZ(inField.z(), tempSF3D_);
    outField += tempSF3D_;
}

// (10) 2D Частная производная функции по "x" всюду
void Operator::derX(const ScalarField2D& inField, ScalarField2D& outField)
{
    for (int i = 0; i < outField.getSizeX(); ++i)
    {
        for (int j = 0; j < outField.getSizeY(); ++j)
        {
            outField(i, j) = derX(inField, i, j);
        }
    }
}

// (11) 2D Частная производная функции по "y" всюду
void Operator::derY(const ScalarField2D& inField, ScalarField2D& outField)
{
    for (int i = 0; i < outField.getSizeX(); ++i)
    {
        for (int j = 0; j < outField.getSizeY(); ++j)
        {
            outField(i, j) = derY(inField, i, j);
        }
    }
}

// (12) 3D Частная производная функции по "x" всюду
void Operator::derX(const ScalarField3D& inField, ScalarField3D& outField)
{
    for (int i = 0; i < outField.getSizeX(); ++i)
    {
        for (int j = 0; j < outField.getSizeY(); ++j)
        {
            for (int k = 0; k < outField.getSizeZ(); ++k)
            {
                outField(i, j, k) = derX(inField, i, j, k);
            }
        }
    }
}

// (13) 3D Частная производная функции по "y" всюду
void Operator::derY(const ScalarField3D& inField, ScalarField3D& outField)
{
    for (int i = 0; i < outField.getSizeX(); ++i)
    {
        for (int j = 0; j < outField.getSizeY(); ++j)
        {
            for (int k = 0; k < outField.getSizeZ(); ++k)
            {
                outField(i, j, k) = derY(inField, i, j, k);
            }
        }
    }
}

// (14) 3D Частная производная функции по "z" всюду (3D)
void Operator::derZ(const ScalarField3D& inField, ScalarField3D& outField)
{
    for (int i = 0; i < outField.getSizeX(); ++i)
    {
        for (int j = 0; j < outField.getSizeY(); ++j)
        {
            for (int k = 0; k < outField.getSizeZ(); ++k)
            {
                outField(i, j, k) = derZ(inField, i, j, k);
            }
        }
    }
}

// (11) Освобождает выделенную память
void Operator::clear()
{
    tempSF2D_.clear();
    tempSF3D_.clear();
}

////////// private ///////////////////////////////////////////////////////////

// (1) 2D Частная производная функции по "x" в точке
Real Operator::derX(const ScalarField2D& inField, int x, int y)
{
    if (x == 0)
    {
        return (inField(x + 1, y) - inField(x, y)) / DX;
    }
    else
    if (x == inField.getSizeX() - 1)
    {
        return (inField(x, y) - inField(x - 1, y)) / DX;
    }
    else
    {
        return (inField(x + 1, y) - inField(x - 1, y)) / (2 * DX);
    }
}

// (2) 2D Частная производная функции по "y"  в точке
Real Operator::derY(const ScalarField2D& inField, int x, int y)
{
    if (y == 0)
    {
        return (inField(x, y + 1) - inField(x, y)) / DY;
    }
    else
    if (y == inField.getSizeY() - 1)
    {
        return (inField(x, y) - inField(x, y - 1)) / DY;
    }
    else
    {
        return (inField(x, y + 1) - inField(x, y - 1)) / (2 * DY);
    }
}

// (3) 3D Частная производная функции по "x" в точке
Real Operator::derX(const ScalarField3D& inField, int x, int y, int z)
{
    if (x == 0)
    {
        return (inField(x + 1, y, z) - inField(x, y, z)) / DX;
    }
    else
    if (x == inField.getSizeX() - 1)
    {
        return (inField(x, y, z) - inField(x - 1, y, z)) / DX;
    }
    else
    {
        return (inField(x + 1, y, z) - inField(x - 1, y, z)) / (2 * DX);
    }
}

// (4) 3D Частная производная функции по "y"  в точке
Real Operator::derY(const ScalarField3D& inField, int x, int y, int z)
{
    if (y == 0)
    {
        return (inField(x, y + 1, z) - inField(x, y, z)) / DY;
    }
    else
    if (y == inField.getSizeY() - 1)
    {
        return (inField(x, y, z) - inField(x, y - 1, z)) / DY;
    }
    else
    {
        return (inField(x, y + 1, z) - inField(x, y - 1, z)) / (2 * DY);
    }
}

// (5) 3D Частная производная функции по "z"  в точке
Real Operator::derZ(const ScalarField3D& inField, int x, int y, int z)
{
    if (z == 0)
    {
        return (inField(x, y, z + 1) - inField(x, y, z)) / DZ;
    }
    else
    if (z == inField.getSizeZ() - 1)
    {
        return (inField(x, y, z) - inField(x, y, z - 1)) / DZ;
    }
    else
    {
        return (inField(x, y, z + 1) - inField(x, y, z - 1)) / (2 * DZ);
    }
}

////////// class Poisson /////////////////////////////////////////////////////
// Описание : toolslib.h.                                                   //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (3) Конструктор копирования
Poisson::Poisson(const Poisson& newPoisson)
{
    *this = newPoisson;
}

// (4) Устанавливается размер вспомогательного 2D поля
void Poisson::resize2D(int sizeX, int sizeY)
{
    try
    {
        tempSF2D_.resize(sizeX, sizeY);
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (5) Устанавливается размер вспомогательного 3D поля
void Poisson::resize3D(int sizeX, int sizeY, int sizeZ)
{
    try
    {
        tempSF3D_.resize(sizeX, sizeY, sizeZ);
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (6) 2D Решает уравнение Пуассона
void Poisson::solve(ScalarField2D& field, const ScalarField2D& free, 
                    Real alpha, Real betta)
{
    for (int i = 0; i < JACOBI_STEP_NUMBER; ++i)
    {
        step(field, free, alpha, betta);
    }
}

// (7) 2D Решает уравнение Пуассона
void Poisson::solve(VectorField2D& field, const VectorField2D& free,
                    Real alpha, Real betta)
{
    solve(field.x(), free.x(), alpha, betta);
    solve(field.y(), free.y(), alpha, betta);
}

// (8) 3D Решает уравнение Пуассона
void Poisson::solve(ScalarField3D& field, const ScalarField3D& free, 
                    Real alpha, Real betta)
{
    for (int i = 0; i < JACOBI_STEP_NUMBER; ++i)
    {
        step(field, free, alpha, betta);
    }
}

// (9) 3D Решает уравнение Пуассона
void Poisson::solve(VectorField3D& field, const VectorField3D& free,
                    Real alpha, Real betta)
{
    solve(field.x(), free.x(), alpha, betta);
    solve(field.y(), free.y(), alpha, betta);
    solve(field.z(), free.z(), alpha, betta);
}

// (8) Освобождает выделенную память
void Poisson::clear()
{
    tempSF2D_.clear();
    tempSF3D_.clear();
}

////////// private ///////////////////////////////////////////////////////////

// (1) 2D Возвращает очередное приближение в точке (i, j)
Real Poisson::step(const ScalarField2D& field, const ScalarField2D& free, 
                   Real alpha, Real betta, int i, int j)
{
    // Вспомогательные переменные
    Real cI = 0;
    Real cJ = 0;
    
    // Подбираем значения по "X"
    cI = field(i + 1, j) + field(i - 1, j);
    
    // Подбираем значения по "Y"
    cJ = field(i, j + 1) + field(i, j - 1);
    
    // Вычисляем очередное приближение в точке (i, j)
    return (cI + cJ + alpha * free(i, j)) / betta;
}

// (2) 2D Возвращает очередное приближение на всем поле
void Poisson::step(ScalarField2D& field, const ScalarField2D& free, 
                   Real alpha, Real betta)
{
    tempSF2D_ = field;
    for (int i = 1; i < field.getSizeX() - 1; ++i)
    {
        for (int j = 1; j < field.getSizeY() - 1; ++j)
        {
            tempSF2D_(i, j) = step(field, free, alpha, betta, i, j);
        }
    }
    field = tempSF2D_;
}

// (3) 3D Возвращает очередное приближение в точке (i, j, k)
Real Poisson::step(const ScalarField3D& field, const ScalarField3D& free, 
                   Real alpha, Real betta, int i, int j, int k)
{
    // Вспомогательные переменные
    Real cI = 0;
    Real cJ = 0;
    Real cK = 0;
    
    // Подбираем значения по "X"
    cI = field(i + 1, j, k) + field(i - 1, j, k);
    
    // Подбираем значения по "Y"
    cJ = field(i, j + 1, k) + field(i, j - 1, k);
    
    // Подбираем значения по "Z"
    cK = field(i, j, k + 1) + field(i, j, k - 1);
    
    // Вычисляем очередное приближение в точке (i, j, k)
    return (cI + cJ + cK + alpha * free(i, j, k)) / betta;
}

// (4) 3D Возвращает очередное приближение на всем поле
void Poisson::step(ScalarField3D& field, const ScalarField3D& free, 
                   Real alpha, Real betta)
{
    tempSF3D_ = field;
    for (int i = 1; i < field.getSizeX() - 1; ++i)
    {
        for (int j = 1; j < field.getSizeY() - 1; ++j)
        {
            for (int k = 1; k < field.getSizeZ() - 1; ++k)
            {
                tempSF3D_(i, j, k) = step(field, free, alpha, betta, i, j, k);
            }
        }
    }
    field = tempSF3D_;
}

////////// class Interpolation ///////////////////////////////////////////////
// Описание : toolslib.h.                                                   //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (1) Конструктор
Interpolation::Interpolation()
{
    a0_ = 0;
    a1_ = 0;
    a2_ = 0;
    a3_ = 0;
    a4_ = 0;
    a5_ = 0;
    a6_ = 0;
    a7_ = 0;
}

// (4) 2D Вычисляет приближенное значение  в (.) на поле "field"
Real Interpolation::compute(const ScalarField2D& field, Real x, Real y)
{
    // Проверка корректности аргументов
    bool isInRangeX = (x >= 0 && x <= (field.getSizeX() - 1) * DX);
    bool isInRangeY = (y >= 0 && y <= (field.getSizeY() - 1) * DY);
    bool haveExit   = false;
    
    // Границы, между которыми заключены координаты
    int  leftX  = 0;
    int  rightX = 0;
    int  leftY  = 0;
    int  rightY = 0;
    
    // Проверяем корректность входных данных
    if (!isInRangeX || !isInRangeY)
    {
        throw err::FluidException(1);
    }
    
    // Если корректны, то найти описывающий прямоугольник
    haveExit = false;
    for (int i = 0; i < field.getSizeX() && !haveExit; ++i)
    {
        if (i * DX <= x)
        {
            leftX = i;
        }
        if (i * DX >= x)
        {
            rightX   = i;
            haveExit = true;
        }
    }
    haveExit = false;
    for (int i = 0; i < field.getSizeY() && !haveExit; ++i)
    {
        if (i * DY <= y)
        {
            leftY = i;
        }
        if (i * DY >= y)
        {
            rightY   = i;
            haveExit = true;
        }
    }
    
    // Перевести координаты в систему отсчета прямоугольник
    x = x - leftX * DX;
    y = y - leftY * DY;
    
    // Записываем значения "ф-ции" в вершины прямоугольника
    values2D_.fx0y0 = field(leftX, leftY);
    values2D_.fx0y1 = field(leftX, rightY);
    values2D_.fx1y0 = field(rightX, leftY);
    values2D_.fx1y1 = field(rightX, rightY);
    
    return compute(x, y);
}

// (5) 3D Вычисляет приближенное значение  в (.) на поле "field"
Real Interpolation::compute(const ScalarField3D& field, Real x, Real y, Real z)
{
    // Проверка корректности аргументов
    bool isInRangeX = (x >= 0 && x <= (field.getSizeX() - 1) * DX);
    bool isInRangeY = (y >= 0 && y <= (field.getSizeY() - 1) * DY);
    bool isInRangeZ = (z >= 0 && z <= (field.getSizeZ() - 1) * DZ);
    bool haveExit   = false;
    
    // Границы, между которыми заключены координаты
    int  leftX  = 0;
    int  rightX = 0;
    int  leftY  = 0;
    int  rightY = 0;
    int  leftZ  = 0;
    int  rightZ = 0;
    
    // Проверяем корректность входных данных
    if (!isInRangeX || !isInRangeY || !isInRangeZ)
    {
        throw err::FluidException(1);
    }
    
    // Если корректны, то найти описывающий параллелепипед
    haveExit = false;
    for (int i = 0; i < field.getSizeX() && !haveExit; ++i)
    {
        if (i * DX <= x)
        {
            leftX = i;
        }
        if (i * DX >= x)
        {
            rightX   = i;
            haveExit = true;
        }
    }
    haveExit = false;
    for (int i = 0; i < field.getSizeY() && !haveExit; ++i)
    {
        if (i * DY <= y)
        {
            leftY = i;
        }
        if (i * DY >= y)
        {
            rightY   = i;
            haveExit = true;
        }
    }
    haveExit = false;
    for (int i = 0; i < field.getSizeZ() && !haveExit; ++i)
    {
        if (i * DZ <= z)
        {
            leftZ = i;
        }
        if (i * DZ >= z)
        {
            rightZ   = i;
            haveExit = true;
        }
    }
    
    // Перевести координаты в систему отсчета параллелепипеда
    x = x - leftX * DX;
    y = y - leftY * DY;
    z = z - leftZ * DZ;
    
    // Записываем значения "ф-ции" в вершины параллелепипеда
    values3D_.fx0y0z0 = field(leftX, leftY, leftZ);
    values3D_.fx0y0z1 = field(leftX, leftY, rightZ);
    values3D_.fx0y1z0 = field(leftX, rightY, leftZ);
    values3D_.fx0y1z1 = field(leftX, rightY, rightZ);
    values3D_.fx1y0z0 = field(rightX, leftY, leftZ);
    values3D_.fx1y0z1 = field(rightX, leftY, rightZ);
    values3D_.fx1y1z0 = field(rightX, rightY, leftZ);
    values3D_.fx1y1z1 = field(rightX, rightY, rightZ);
    
    return compute(x, y, z);
}

// (5) Обнуляет поля
void Interpolation::clear()
{
    a0_ = 0;
    a1_ = 0;
    a2_ = 0;
    a3_ = 0;
    a4_ = 0;
    a5_ = 0;
    a6_ = 0;
    a7_ = 0;
    values2D_.clear();
    values3D_.clear();
}

////////// private ///////////////////////////////////////////////////////////

// (1) 2D Вычисляет приближенное значение "ф-ции" в (.)
Real Interpolation::compute(Real x, Real y)
{
    // Проверяем корректность входных данных
    if (x < 0 || x > DX || y < 0 || y > DY)
    {
        throw err::FluidException(1);
    }
    
    // Общий знаменатель
    Real denominator = DX * DY;
    
    // Вычисляем все коэффициенты (Билинейная интерполяция)
    a0_ = (values2D_.fx0y0 / denominator) * (DX - x) * (DY - y);
    a1_ = (values2D_.fx0y1 / denominator) * (DX - x) * (y);
    a2_ = (values2D_.fx1y1 / denominator) * (x) * (DY - y);
    a3_ = (values2D_.fx1y1 / denominator) * (x) * (y);
    
    return a0_ + a1_ + a2_ + a3_;
}

// (2) 3D Вычисляет приближенное значение "ф-ции" в (.)
Real Interpolation::compute(Real x, Real y, Real z)
{
    // Проверяем корректность входных данных
    if (x < 0 || x > DX || y < 0 || y > DY || z < 0 || z > DZ)
    {
        throw err::FluidException(1);
    }
    
    // Общий знаменатель
    Real denominator = DX * DY * DZ;
    
    // Вычисляем все коэффициенты (Трилинейная интерполяция)
    a0_ = (values3D_.fx0y0z0 / denominator) * (DX - x) * (DY - y) * (DZ - z);
    a1_ = (values3D_.fx0y0z1 / denominator) * (DX - x) * (DY - y) * (z);
    a2_ = (values3D_.fx0y1z0 / denominator) * (DX - x) * (y) * (DZ - z);
    a3_ = (values3D_.fx1y0z0 / denominator) * (x) * (DY - y) * (DZ - z);
    a4_ = (values3D_.fx0y1z1 / denominator) * (DX - x) * (y) * (z);
    a5_ = (values3D_.fx1y1z0 / denominator) * (x) * (y) * (DZ - z);
    a6_ = (values3D_.fx1y0z1 / denominator) * (x) * (DY - y) * (z);
    a7_ = (values3D_.fx1y1z1 / denominator) * (x) * (y) * (z);
    
    return a0_ + a1_ + a2_ + a3_ + a4_ + a5_ + a6_ + a7_;
}

////////// class Tools ///////////////////////////////////////////////////////
// Описание : toolslib.h.                                                   //
//////////////////////////////////////////////////////////////////////////////

// (2) Конструктор копирования
Tools::Tools(const Tools& newTools)
{
    *this = newTools;
}

// (4) Устанавливается размер вспомогательных 2D полей
void Tools::resize2D(int sizeX, int sizeY)
{
    try
    {
        tempSF2D_.resize(sizeX, sizeY);
        tempVF2D_.resize(sizeX, sizeY);
        poisson_.resize2D(sizeX, sizeY);
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (5) Устанавливается размер вспомогательных 3D полей
void Tools::resize3D(int sizeX, int sizeY, int sizeZ)
{
    try
    {
        tempSF3D_.resize(sizeX, sizeY, sizeZ);
        tempVF3D_.resize(sizeX, sizeY, sizeZ);
        poisson_.resize3D(sizeX, sizeY, sizeZ);
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (6) 2D Вычисляет, как поле "basic" переносит значения "field"
void Tools::advection(ScalarField2D& field, const VectorField2D& basic)
{
    // Проверка координат точки на выход за границы
    bool isInRangeX = false;
    bool isInRangeY = false;
    
    // Координаты точки, откуда приходит новое значение
    Real x = 0;
    Real y = 0;
    
    // Проходим по всему полю скоростей, находим точки заимствования знач.
    for (int i = 0; i < basic.getSizeX(); ++i)
    {
        for (int j = 0; j < basic.getSizeY(); ++j)
        {
            // Находим точку, откуда приходит значение
            x = DX * i - basic.x()(i, j) * DT;
            y = DY * j - basic.y()(i, j) * DT;
            
            // Проверяем, что она внутри поля
            isInRangeX = (x >= 0 && x <= (basic.getSizeX() - 1) * DX);
            isInRangeY = (y >= 0 && y <= (basic.getSizeY() - 1) * DY);
            
            // Если внути поля, то интерполируем "ф-ию"
            if (isInRangeX && isInRangeY)
            {
                tempSF2D_(i, j) = intp_.compute(field, x, y);
            }
            else
            {
                tempSF2D_(i, j) = field(i, j);
            }
        }
    }
    
    // Возвращаем измененное поле
    field = tempSF2D_;
}

// (7) 3D Вычисляет, как поле "basic" переносит значения "field"
void Tools::advection(ScalarField3D& field, const VectorField3D& basic)
{
    // Проверка координат точки на выход за границы
    bool isInRangeX = false;
    bool isInRangeY = false;
    bool isInRangeZ = false;
    
    // Координаты точки, откуда приходит новое значение
    Real x = 0;
    Real y = 0;
    Real z = 0;
    
    // Проходим по всему полю скоростей, находим точки заимствования знач.
    for (int i = 0; i < basic.getSizeX(); ++i)
    {
        for (int j = 0; j < basic.getSizeY(); ++j)
        {
            for (int k = 0; k < basic.getSizeZ(); ++k)
            {
                // Находим точку, откуда приходит значение
                x = DX * i - basic.x()(i, j, k) * DT;
                y = DY * j - basic.y()(i, j, k) * DT;
                z = DZ * k - basic.z()(i, j, k) * DT;
                
                // Проверяем, что она внутри поля
                isInRangeX = (x >= 0 && x <= (basic.getSizeX() - 1) * DX);
                isInRangeY = (y >= 0 && y <= (basic.getSizeY() - 1) * DY);
                isInRangeZ = (z >= 0 && z <= (basic.getSizeZ() - 1) * DZ);
                
                // Если внути поля, то интерполируем "ф-ию"
                if (isInRangeX && isInRangeY && isInRangeZ)
                {
                    tempSF3D_(i, j, k) = intp_.compute(field, x, y, z);
                }
                else
                {
                    tempSF3D_(i, j, k) = field(i, j, k);
                }
            }
        }
    }
    
    // Возвращаем измененное поле
    field = tempSF3D_;
}

// (8) 2D Вычисляет, как поле "basic" переносит значения "field"
void Tools::advection(VectorField2D& field, const VectorField2D& basic)
{
    advection(field.x(), basic);
    advection(field.y(), basic);
}

// (9) 3D Вычисляет, как поле "basic" переносит значения "field"
void Tools::advection(VectorField3D& field, const VectorField3D& basic)
{
    advection(field.x(), basic);
    advection(field.y(), basic);
    advection(field.z(), basic);
}

// (10) 2D Рассчет вязкой диффузии для скалярного поля "field"
void Tools::diffusion(ScalarField2D& field, Real gamma)
{
    // Коэффициенты для вязкой диффузии в 2D
    Real alpha = DX * DX / (gamma * DT);
    Real betta = alpha + 4;
    
    // Решить уравнение Пуассона для "field"
    tempSF2D_ = field;
    poisson_.solve(field, tempSF2D_, alpha, betta);
}

// (11) 3D Рассчет вязкой диффузии для скалярного поля "field"
void Tools::diffusion(ScalarField3D& field, Real gamma)
{
    // Коэффициенты для вязкой диффузии в 3D
    Real alpha = DX * DX / (gamma * DT);
    Real betta = alpha + 6;
    
    // Решить уравнение Пуассона для "field"
    tempSF3D_ = field;
    poisson_.solve(field, tempSF3D_, alpha, betta);
}

// (12) 2D Рассчет вязкой диффузии для векторного поля "field"
void Tools::diffusion(VectorField2D& field, Real gamma)
{
    // Коэффициенты для вязкой диффузии в 2D
    Real alpha = DX * DX / (gamma * DT);
    Real betta = alpha + 4;
    
    // Решить уравнение Пуассона для "field"
    tempVF2D_ = field;
    poisson_.solve(field, tempVF2D_, alpha, betta);
}

// (13) 2D Рассчет вязкой диффузии для векторного поля "field"
void Tools::diffusion(VectorField3D& field, Real gamma)
{
    // Коэффициенты для вязкой диффузии в 3D
    Real alpha = DX * DX / (gamma * DT);
    Real betta = alpha + 6;
    
    // Решить уравнение Пуассона для "field"
    tempVF3D_ = field;
    poisson_.solve(field, tempVF3D_, alpha, betta);
}

// (10) Освобождает выделенную память
void Tools::clear()
{
    tempSF2D_.clear();
    tempVF2D_.clear();
    tempSF3D_.clear();
    tempVF3D_.clear();
    poisson_.clear();
    intp_.clear();
}