////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "fluidlib.h"

////////// class FluidException //////////////////////////////////////////////
// Описание : fluidlib.h                                                    //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор (обнуляет поле)
fluid::FluidException::FluidException()
{
    errCode_ = 0;
}

// (2) Конструктор (инициализирует поле)
fluid::FluidException::FluidException(const int& newErrCode)
{
    errCode_ = newErrCode;
}

// (3) Конструктор копирования
fluid::FluidException::FluidException(const FluidException& exception)
{
    *this = exception;
}

// (4) Перегрузка оператора присваивания
fluid::FluidException& fluid::FluidException::operator=(const FluidException& 
                                                        exception)
{
    if (&exception != this)
    {
        errCode_ = exception.errCode_;
    }
    return *this;
}

// (5) Возвращает код ошибки
int fluid::FluidException::error() const
{
    return errCode_;
}

// (6) Установить значение ошибки
void fluid::FluidException::setErrCode(const int& code)
{
    if (code >= 0)
    {
        errCode_ = code;
    }
}

////////// struct Vector /////////////////////////////////////////////////////
// Описание : fluidlib.h.                                                   //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор (обнуляет поля)
fluid::Vector::Vector()
{
    x = 0;
    y = 0;
    z = 0;
}

// (2) Конструктор копирования
fluid::Vector::Vector(const fluid::Vector& vector)
{
    *this = vector;
}

// (3) Перегрузка оператора присваивания
fluid::Vector& fluid::Vector::operator=(const fluid::Vector& vector)
{
    if (this != &vector)
    {
        x = vector.x;
        y = vector.y;
        z = vector.z;
    }
    return *this;
}

// (4) Обнуляет поля
void fluid::Vector::clear()
{
    x = 0;
    y = 0;
    z = 0;
}

// (5) Деструктор
fluid::Vector::~Vector()
{
    clear();
}

////////// class Functions ///////////////////////////////////////////////////
// Описание : fluidlib.h.                                                   //
//////////////////////////////////////////////////////////////////////////////

// (1) Градиент
fluid::Vector fluid::Operator::grad(const fluid::ScalarField& field, 
                                    const int& x, const int& y, const int& z)
{
    //...
    return Vector();
}

// (2) Дивергенция
fluid::real fluid::Operator::div(const fluid::VectorField& field, 
                                 const int& x, const int& y, const int& z)
{
    //...
    return 0;
}

// (3) Оператор Лапласа
fluid::real fluid::Operator::divGrad(const fluid::ScalarField& field, 
                                     const int& x, const int& y, const int& z)
{
    //...
    return 0;
}