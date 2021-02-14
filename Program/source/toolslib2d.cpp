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

// (4) Инициализация вспомогательных 2D полей
void Operator2D::initialize(int sizeX, int sizeY)
{
    try
    {
        // Меняем размер поля на требуемый
        tempSF2D_.resize(sizeX, sizeY);
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (5) Градиент поля "field1" (результат : "field2")
void Operator2D::grad(const SField2D& field1, VField2D& field2)
{
    derX(field1, field2.x());
    derY(field1, field2.y());
}

// (6) Дивергенция поля "field1" (результат : "field2")
void Operator2D::div(const VField2D& field1, SField2D& field2)
{
    derX(field1.x(), field2);
    derY(field1.y(), tempSF2D_);
    add(field2, tempSF2D_);
}

// (7) Частная пр-ая "field1" по "x" всюду (результат : "field2")
void Operator2D::derX(const SField2D& field1, SField2D& field2)
{
    for (int i = 0; i < field1.getSizeX(); ++i)
    {
        for (int j = 0; j < field1.getSizeY(); ++j)
        {
            if (field1.area(i, j))
            {
                field2.field(i, j) = derX(field1, i, j);
                field2.area(i, j)  = true;
            }
            else
            {
                field2.area(i, j) = false;
            }
        }
    }
}

// (8) Частная пр-ая "field1" по "y" всюду (результат : "field2")
void Operator2D::derY(const SField2D& field1, SField2D& field2)
{
    for (int i = 0; i < field1.getSizeX(); ++i)
    {
        for (int j = 0; j < field1.getSizeY(); ++j)
        {
            if (field1.area(i, j))
            {
                field2.field(i, j) = derY(field1, i, j);
                field2.area(i, j)  = true;
            }
            else
            {
                field2.area(i, j) = false;
            }
        }
    }
}

// (9) Добавляет поэлементно поле "field2" к полю "field1"
void Operator2D::add(SField2D& field1, const SField2D& field2)
{
    for (int i = 0; i < field1.getSizeX(); ++i)
    {
        for (int j = 0; j < field1.getSizeY(); ++j)
        {
            if (field1.area(i, j) && field2.area(i, j))
            {
                field1.field(i, j) += field2.field(i, j);
            }
        }
    }
}

// (10) Добавляет поэлементно поле "field2" к полю "field1"
void Operator2D::add(VField2D& field1, const VField2D& field2)
{
    add(field1.x(), field2.x());
    add(field1.y(), field2.y());
}

// (11) Вычитает поэлементно поле "field2" из поля "field1"
void Operator2D::sub(SField2D& field1, const SField2D& field2)
{
    for (int i = 0; i < field1.getSizeX(); ++i)
    {
        for (int j = 0; j < field1.getSizeY(); ++j)
        {
            if (field1.area(i, j) && field2.area(i, j))
            {
                field1.field(i, j) -= field2.field(i, j);
            }
        }
    }
}

// (12) Вычитает поэлементно поле "field2" из поля "field1"
void Operator2D::sub(VField2D& field1, const VField2D& field2)
{
    sub(field1.x(), field2.x());
    sub(field1.y(), field2.y());
}

// (13) Присваивает поэлементно поле "field2" полю "field1"
void Operator2D::assign(SField2D& field1, const SField2D& field2)
{
    for (int i = 0; i < field1.getSizeX(); ++i)
    {
        for (int j = 0; j < field1.getSizeY(); ++j)
        {
            if (field1.area(i, j) && field2.area(i, j))
            {
                field1.field(i, j) = field2.field(i, j);
            }
        }
    }
}

// (14) Присваивает поэлементно поле "field2" полю "field1"
void Operator2D::assign(VField2D& field1, const VField2D& field2)
{
    assign(field1.x(), field2.x());
    assign(field1.y(), field2.y());
}

// (15) Освобождает выделенную память
void Operator2D::clear()
{
    tempSF2D_.clear();
}

////////// private ///////////////////////////////////////////////////////////

// (1) Частная пр-ая "field" по "x" в (x, y)
Real Operator2D::derX(const SField2D& field, int x, int y)
{
    return (field.field(x + 1, y) - field.field(x - 1, y)) / (2 * DX);
}

// (2) Частная пр-ая "field" по "y" в (x, y)
Real Operator2D::derY(const SField2D& field, int x, int y)
{
    return (field.field(x, y + 1) - field.field(x, y - 1)) / (2 * DY);
}

////////// class Poisson2D ///////////////////////////////////////////////////
// Описание : toolslib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (1) Конструктор
Poisson2D::Poisson2D()
{
    operator2D_ = nullptr;
}

// (4) Инициализация вспомогательных 2D полей
void Poisson2D::initialize(int sizeX, int sizeY, Operator2D& operator2D)
{
    try
    {
        // Меняем размер поля на требуемый
        tempSF2D_.resize(sizeX, sizeY);
        
        // Подключаем вспомогательные инструменты
        operator2D_ = &operator2D;
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (5) Решает уравнение Пуассона
void Poisson2D::solve(SField2D& field, const SField2D& free, Real alpha, 
                      Real betta)
{
    // Метод итераций Якоби
    for (int i = 0; i < JACOBI_STEP_NUMBER; ++i)
    {
        step(field, free, alpha, betta);
    }
}

// (6) Решает уравнение Пуассона
void Poisson2D::solve(VField2D& field, const VField2D& free, Real alpha, 
                      Real betta)
{
    solve(field.x(), free.x(), alpha, betta);
    solve(field.y(), free.y(), alpha, betta);
}

// (7) Освобождает выделенную память
void Poisson2D::clear()
{
    tempSF2D_.clear();
    operator2D_ = nullptr;
}

////////// private ///////////////////////////////////////////////////////////

// (1) Возвращает очередное приближение в точке (i, j)
Real Poisson2D::step(const SField2D& field, const SField2D& free, Real alpha, 
                     Real betta, int i, int j)
{
    // Вспомогательные переменные
    Real cI = field.field(i + 1, j) + field.field(i - 1, j);
    Real cJ = field.field(i, j + 1) + field.field(i, j - 1);
    
    // Вычисляем очередное приближение в точке (i, j)
    return (cI + cJ + alpha * free.field(i, j)) / betta;
}

// (2) Возвращает очередное приближение на всем поле
void Poisson2D::step(SField2D& field, const SField2D& free, Real alpha, 
                     Real betta)
{
    // Проходим по всем точкам рабочей зоны
    for (int i = 0; i < field.getSizeX(); ++i)
    {
        for (int j = 0; j < field.getSizeY(); ++j)
        {
            if (field.area(i, j) && free.area(i, j))
            {
                tempSF2D_.field(i, j) = step(field, free, alpha, betta, i, j);
                tempSF2D_.area(i, j)  = true;
            }
            else
            {
                tempSF2D_.area(i, j) = false;
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
Real Interpolation2D::compute(const SField2D& field, Real x, Real y)
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
    values2D_.fx0y0 = field.field(startX, startY);
    values2D_.fx0y1 = field.field(startX, startY + 1);
    values2D_.fx1y0 = field.field(startX + 1, startY);
    values2D_.fx1y1 = field.field(startX + 1, startY + 1);
    
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
}

// (4) Устанавливается размер вспомогательных 2D полей
void ModelTools2D::initialize(int sizeX, int sizeY,  Operator2D& operator2D, 
                              Poisson2D& poisson2D, Interpolation2D& interp2D)
{
    try
    {
        // Меняем размер полей на требуемый
        tempSF2D_.resize(sizeX, sizeY);
        tempVF2D_.resize(sizeX, sizeY);
        
        // Подключаем вспомогательные инструменты
        operator2D_ = &operator2D;
        poisson2D_  = &poisson2D;
        interp2D_   = &interp2D;
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (5) Вычисляет, как поле "basic" переносит значения "field"
void ModelTools2D::advection(SField2D& field, const VField2D& basic)
{
    // Координаты точки, откуда приходит новое значение
    Real x = 0;
    Real y = 0;
    
    // Проходим по всему полю скоростей
    for (int i = 0; i < field.getSizeX(); ++i)
    {
        for (int j = 0; j < field.getSizeY(); ++j)
        {
            if (field.area(i, j) && basic.x().area(i, j))
            {
                // Находим точку, откуда приходит значение
                x = DX * i - basic.x().field(i, j) * DT;
                y = DY * j - basic.y().field(i, j) * DT;
                
                // Интерполируем "ф-ию"
                tempSF2D_.field(i, j) = interp2D_->compute(field, x, y);
                tempSF2D_.area(i, j)  = true;
            }
            else
            {
                tempSF2D_.area(i, j) = false;
            }
        }
    }
    
    // Обновляем значения в точках рабочей зоны
    operator2D_->assign(field, tempSF2D_);
}

// (6) Вычисляет, как поле "basic" переносит значения "field"
void ModelTools2D::advection(VField2D& field, const VField2D& basic)
{
    advection(field.x(), basic);
    advection(field.y(), basic);
}

// (7) Рассчет вязкой диффузии для скалярного поля
void ModelTools2D::diffusion(SField2D& field, Real viscosity)
{
    // Коэффициенты для вязкой диффузии в 2D
    Real alpha = DX * DX / (viscosity * DT);
    Real betta = alpha + 4;
    
    // Инициализация поля свободных членов
    tempSF2D_.resetArea(true);
    operator2D_->assign(tempSF2D_, field);
    
    // Решает уравнение Пуассона для "field"
    poisson2D_->solve(field, tempSF2D_, alpha, betta);
}

// (8) Рассчет вязкой диффузии для векторного поля
void ModelTools2D::diffusion(VField2D& field, Real viscosity)
{
    // Коэффициенты для вязкой диффузии в 2D
    Real alpha = DX * DX / (viscosity * DT);
    Real betta = alpha + 4;
    
    // Инициализация поля свободных членов
    tempVF2D_.x().resetArea(true);
    tempVF2D_.y().resetArea(true);
    operator2D_->assign(tempVF2D_, field);
    
    // Решает уравнение Пуассона для "field"
    poisson2D_->solve(field, tempVF2D_, alpha, betta);
}

// (9) Рассчет действия поля сил "field2" на поле "field1"
void ModelTools2D::force(VField2D& field1, const VField2D& field2, 
                         Real density)
{
    force(field1.x(), field2.x(), density);
    force(field1.y(), field2.y(), density);
}

// (10) Освобождает выделенную память
void ModelTools2D::clear()
{
    tempSF2D_.clear();
    tempVF2D_.clear();
    operator2D_ = nullptr;
    poisson2D_  = nullptr;
    interp2D_   = nullptr;
}

////////// private ///////////////////////////////////////////////////////////

// (1) Рассчет действия компоненты поля сил
void ModelTools2D::force(SField2D& field1, const SField2D& field2, 
                         Real density)
{
    // Приращение времени, деленное на массу
    Real dtDivM = DT / (DX * DY * density);
    
    // Проходим по всему полю "field1"
    for (int i = 0; i < field1.getSizeX(); ++i)
    {
        for (int j = 0; j < field1.getSizeY(); ++j)
        {
            if (field1.area(i, j) && field2.area(i, j))
            {
                // Добавляем приращение скорости
                field1.field(i, j) += field2.field(i, j) * dtDivM;
            }
        }
    }
}

////////// class BasicTools2D ////////////////////////////////////////////////
// Описание : toolslib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

// (4) Инициализация всех инструментов
void BasicTools2D::initialize(int sizeX, int sizeY)
{
    try
    {
        operator2D_.initialize(sizeX, sizeY);
        poisson2D_.initialize(sizeX, sizeY, operator2D_);
        tools2D_.initialize(sizeX, sizeY, operator2D_, poisson2D_, interp2D_);
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
Interpolation2D& BasicTools2D::interp()
{
    return interp2D_;
}

// (8) Доступ к инструментам моделирования
ModelTools2D& BasicTools2D::model()
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