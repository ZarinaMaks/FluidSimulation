////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "toolslib2d.h"

using namespace fluid;

////////// class Operator2D //////////////////////////////////////////////////
// Описание : toolslib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (1) Конструктор
Operator2D::Operator2D()
{
    area2D_ = nullptr;
}

// (4) Инициализация вспомогательных 2D полей
void Operator2D::initialize(const WorkZone2D& area2D)
{
    try
    {
        tempSF2D_.resize(area2D.getSizeX(), area2D.getSizeY());
        area2D_ = &area2D;
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (5) Градиент (Возвращает по ссылке векторное поле)
void Operator2D::grad(const ScalarField2D& inField, VectorField2D& outField)
{
    derX(inField, outField.x());
    derY(inField, outField.y());
}

// (6) Дивергенция (Возвращает по ссылке скалярное поле)
void Operator2D::div(const VectorField2D& inField, ScalarField2D& outField)
{
    derX(inField.x(), outField);
    derY(inField.y(), tempSF2D_);
    add(outField, tempSF2D_);
}

// (7) Частная производная функции по "x" всюду
void Operator2D::derX(const ScalarField2D& inField, ScalarField2D& outField)
{
    for (int i = 0; i < outField.getSizeX(); ++i)
    {
        for (int j = 0; j < outField.getSizeY(); ++j)
        {
            if ((*area2D_)(i, j))
            {
                outField(i, j) = derX(inField, i, j);
            }
        }
    }
}

// (8) Частная производная функции по "y" всюду
void Operator2D::derY(const ScalarField2D& inField, ScalarField2D& outField)
{
    for (int i = 0; i < outField.getSizeX(); ++i)
    {
        for (int j = 0; j < outField.getSizeY(); ++j)
        {
            if ((*area2D_)(i, j))
            {
                outField(i, j) = derY(inField, i, j);
            }
        }
    }
}

// (9) Добавляет поэлементно поле "field2" к полю "field1"
void Operator2D::add(ScalarField2D& field1, const ScalarField2D& field2)
{
    for (int i = 0; i < field1.getSizeX(); ++i)
    {
        for (int j = 0; j < field1.getSizeY(); ++j)
        {
            if ((*area2D_)(i, j))
            {
                field1(i, j) += field2(i, j);
            }
        }
    }
}

// (10) Добавляет поэлементно поле "field2" к полю "field1"
void Operator2D::add(VectorField2D& field1, const VectorField2D& field2)
{
    add(field1.x(), field2.x());
    add(field1.y(), field2.y());
}

// (11) Вычитает поэлементно поле "field2" из поля "field1"
void Operator2D::sub(ScalarField2D& field1, const ScalarField2D& field2)
{
    for (int i = 0; i < field1.getSizeX(); ++i)
    {
        for (int j = 0; j < field1.getSizeY(); ++j)
        {
            if ((*area2D_)(i, j))
            {
                field1(i, j) -= field2(i, j);
            }
        }
    }
}

// (12) Вычитает поэлементно поле "field2" из поля "field1"
void Operator2D::sub(VectorField2D& field1, const VectorField2D& field2)
{
    sub(field1.x(), field2.x());
    sub(field1.y(), field2.y());
}

// (13) Присваивает поэлементно поле "field2" полю "field1"
void Operator2D::assign(ScalarField2D& field1, const ScalarField2D& field2)
{
    for (int i = 0; i < field1.getSizeX(); ++i)
    {
        for (int j = 0; j < field1.getSizeY(); ++j)
        {
            if ((*area2D_)(i, j))
            {
                field1(i, j) = field2(i, j);
            }
        }
    }
}

// (14) Присваивает поэлементно поле "field2" полю "field1"
void Operator2D::assign(VectorField2D& field1, const VectorField2D& field2)
{
    assign(field1.x(), field2.x());
    assign(field1.y(), field2.y());
}

// (15) Освобождает выделенную память
void Operator2D::clear()
{
    tempSF2D_.clear();
    area2D_ = nullptr;
}

////////// private ///////////////////////////////////////////////////////////

// (1) Частная производная функции по "x" в (x, y)
Real Operator2D::derX(const ScalarField2D& inField, int x, int y)
{
    return (inField(x + 1, y) - inField(x - 1, y)) / (2 * DX);
}

// (2) Частная производная функции по "y" в (x, y)
Real Operator2D::derY(const ScalarField2D& inField, int x, int y)
{
    return (inField(x, y + 1) - inField(x, y - 1)) / (2 * DY);
}

////////// class Poisson2D ///////////////////////////////////////////////////
// Описание : toolslib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (1) Конструктор
Poisson2D::Poisson2D()
{
    operator2D_ = nullptr;
    area2D_     = nullptr;
}

// (4) Инициализация вспомогательных 2D полей
void Poisson2D::initialize(const WorkZone2D& area2D, 
                           Operator2D& operator2D)
{
    try
    {
        tempSF2D_.resize(area2D.getSizeX(), area2D.getSizeY());
        area2D_     = &area2D;
        operator2D_ = &operator2D;
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (5) Решает уравнение Пуассона
void Poisson2D::solve(ScalarField2D& field, const ScalarField2D& free, 
                      Real alpha, Real betta)
{
    for (int i = 0; i < JACOBI_STEP_NUMBER; ++i)
    {
        step(field, free, alpha, betta);
    }
}

// (6) Решает уравнение Пуассона
void Poisson2D::solve(VectorField2D& field, const VectorField2D& free,
                      Real alpha, Real betta)
{
    solve(field.x(), free.x(), alpha, betta);
    solve(field.y(), free.y(), alpha, betta);
}

// (7) Освобождает выделенную память
void Poisson2D::clear()
{
    tempSF2D_.clear();
    operator2D_ = nullptr;
    area2D_     = nullptr;
}

////////// private ///////////////////////////////////////////////////////////

// (1) Возвращает очередное приближение в точке (i, j)
Real Poisson2D::step(const ScalarField2D& field, const ScalarField2D& free, 
                     Real alpha, Real betta, int i, int j)
{
    // Вспомогательные переменные
    Real cI = field(i + 1, j) + field(i - 1, j);
    Real cJ = field(i, j + 1) + field(i, j - 1);
    
    // Вычисляем очередное приближение в точке (i, j)
    return (cI + cJ + alpha * free(i, j)) / betta;
}

// (2) Возвращает очередное приближение на всем поле
void Poisson2D::step(ScalarField2D& field, const ScalarField2D& free, 
                     Real alpha, Real betta)
{
    // Проходим по всем точкам рабочей зоны
    for (int i = 0; i < field.getSizeX(); ++i)
    {
        for (int j = 0; j < field.getSizeY(); ++j)
        {
            if ((*area2D_)(i, j))
            {
                tempSF2D_(i, j) = step(field, free, alpha, betta, i, j);
            }
        }
    }
    
    // Обновляем значения в точках рабочей зоны
    operator2D_->assign(field, tempSF2D_);
}

////////// class Interpolation2D /////////////////////////////////////////////
// Описание : toolslib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (1) Конструктор
Interpolation2D::Interpolation2D()
{
    a0_ = 0;
    a1_ = 0;
    a2_ = 0;
    a3_ = 0;
}

// (4) Вычисляет приближенное значение в (x, y) на поле
Real Interpolation2D::compute(const ScalarField2D& field, Real x, Real y)
{
    // Координаты угла отсчета прямоугольника
    int startX = 0;
    int startY = 0;
    
    // Поиск координат угла отсчета прямоугольника
    startX = intPart(x, DX);
    startY = intPart(y, DY);
    
    // Перевести координаты (x, y) в систему отсчета прямоугольника
    x = x - startX * DX;
    y = y - startY * DY;
    
    // Записываем значения "ф-ции" в вершины прямоугольника
    values2D_.fx0y0 = field(startX, startY);
    values2D_.fx0y1 = field(startX, startY + 1);
    values2D_.fx1y0 = field(startX + 1, startY);
    values2D_.fx1y1 = field(startX + 1, startY + 1);
    
    // Вычислить приближенное значение внутри прямоугольника
    return compute(x, y);
}

// (5) Обнуляет поля
void Interpolation2D::clear()
{
    a0_ = 0;
    a1_ = 0;
    a2_ = 0;
    a3_ = 0;
    values2D_.clear();
}

////////// private ///////////////////////////////////////////////////////////

// (1) Вычисляет значение в (x, y) используя "Values2D"
Real Interpolation2D::compute(Real x, Real y)
{
    // Общий знаменатель
    Real denominator = DX * DY;
    
    // Вычисляем все коэффициенты (Билинейная интерполяция)
    a0_ = (values2D_.fx0y0 / denominator) * (DX - x) * (DY - y);
    a1_ = (values2D_.fx0y1 / denominator) * (DX - x) * (y);
    a2_ = (values2D_.fx1y1 / denominator) * (x) * (DY - y);
    a3_ = (values2D_.fx1y1 / denominator) * (x) * (y);
    
    // Возвращаем приближеннное значение
    return a0_ + a1_ + a2_ + a3_;
}

////////// class ModelTools2D ////////////////////////////////////////////////
// Описание : toolslib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (1) Конструктор
ModelTools2D::ModelTools2D()
{
    operator2D_ = nullptr;
    poisson2D_  = nullptr;
    interp2D_   = nullptr;
    area2D_     = nullptr;
}

// (4) Устанавливается размер вспомогательных 2D полей
void ModelTools2D::initialize(const WorkZone2D& area2D, 
                              Operator2D& operator2D, 
                              Poisson2D& poisson2D, 
                              Interpolation2D& interp2D)
{
    try
    {
        tempSF2D_.resize(area2D.getSizeX(), area2D.getSizeY());
        tempVF2D_.resize(area2D.getSizeX(), area2D.getSizeY());
        operator2D_ = &operator2D;
        poisson2D_  = &poisson2D;
        interp2D_   = &interp2D;
        area2D_     = &area2D;
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (6) Вычисляет, как поле "basic" переносит значения "field"
void ModelTools2D::advection(ScalarField2D& field, const VectorField2D& basic)
{
    // Координаты точки, откуда приходит новое значение
    Real x = 0;
    Real y = 0;
    
    // Проходим по всему полю скоростей
    for (int i = 0; i < basic.getSizeX(); ++i)
    {
        for (int j = 0; j < basic.getSizeY(); ++j)
        {
            if ((*area2D_)(i, j))
            {
                // Находим точку, откуда приходит значение
                x = DX * i - basic.x()(i, j) * DT;
                y = DY * j - basic.y()(i, j) * DT;
                
                // Интерполируем "ф-ию"
                tempSF2D_(i, j) = interp2D_->compute(field, x, y);
            }
        }
    }
    
    // Обновляем значения в точках рабочей зоны
    operator2D_->assign(field, tempSF2D_);
}

// (8) Вычисляет, как поле "basic" переносит значения "field"
void ModelTools2D::advection(VectorField2D& field, const VectorField2D& basic)
{
    advection(field.x(), basic);
    advection(field.y(), basic);
}

// (10) Рассчет вязкой диффузии для скалярного поля
void ModelTools2D::diffusion(ScalarField2D& field, Real viscosity)
{
    // Коэффициенты для вязкой диффузии в 2D
    Real alpha = DX * DX / (viscosity * DT);
    Real betta = alpha + 4;
    
    // Инициализация поля свободных членов
    operator2D_->assign(tempSF2D_, field);
    
    // Решает уравнение Пуассона для "field"
    poisson2D_->solve(field, tempSF2D_, alpha, betta);
}

// (12) Рассчет вязкой диффузии для векторного поля
void ModelTools2D::diffusion(VectorField2D& field, Real viscosity)
{
    // Коэффициенты для вязкой диффузии в 2D
    Real alpha = DX * DX / (viscosity * DT);
    Real betta = alpha + 4;
    
    // Инициализация поля свободных членов
    operator2D_->assign(tempVF2D_, field);
    
    // Решает уравнение Пуассона для "field"
    poisson2D_->solve(field, tempVF2D_, alpha, betta);
}

// (10) Освобождает выделенную память
void ModelTools2D::clear()
{
    tempSF2D_.clear();
    tempVF2D_.clear();
    operator2D_ = nullptr;
    poisson2D_  = nullptr;
    interp2D_   = nullptr;
    area2D_     = nullptr;
}

////////// private ///////////////////////////////////////////////////////////

//...

////////// class BasicTools2D ////////////////////////////////////////////////
// Описание : toolslib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

// (4) Инициализация всех инструментов
void BasicTools2D::initialize(const WorkZone2D& area2D)
{
    try
    {
        operator2D_.initialize(area2D);
        poisson2D_.initialize(area2D, operator2D_);
        tools2D_.initialize(area2D, operator2D_, poisson2D_, interp2D_);
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (5) Доступ к всевозможным операторам
Operator2D& BasicTools2D::operation()
{
    return operator2D_;
}

// (6) Доступ к методам решения уравнения Пуассона
Poisson2D& BasicTools2D::poisson()
{
    return poisson2D_;
}

// (7) Доступ к методам билинейной интерполяции
Interpolation2D& BasicTools2D::interpolation()
{
    return interp2D_;
}

// (8) Доступ к инструментам моделирования
ModelTools2D& BasicTools2D::modeling()
{
    return tools2D_;
}

// (9) Освобождает выделенную память
void BasicTools2D::clear()
{
    operator2D_.clear();
    poisson2D_.clear();
    interp2D_.clear();
    tools2D_.clear();
}