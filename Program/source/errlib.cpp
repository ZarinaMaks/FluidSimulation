////////// errlib ////////////////////////////////////////////////////////////
// Автор    : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
// Описание : Здесь представлены инструменты для обработки исключительных   //
//            ситуаций в модулях моделирования течения жидкости.            //
//////////////////////////////////////////////////////////////////////////////

#include "errlib.h"

using namespace err;

////////// class FluidException //////////////////////////////////////////////
// Описание : errlib.h                                                      //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор (обнуляет поле)
FluidException::FluidException()
{
    errCode_ = 0;
}

// (2) Конструктор (инициализирует поле)
FluidException::FluidException(const int& newErrCode)
{
    errCode_ = newErrCode;
}

// (3) Конструктор копирования
FluidException::FluidException(const FluidException& exception)
{
    *this = exception;
}

// (4) Перегрузка оператора присваивания
FluidException& FluidException::operator=(const FluidException& exception)
{
    if (&exception != this)
    {
        errCode_ = exception.errCode_;
    }
    return *this;
}

// (5) Возвращает код ошибки
int FluidException::error() const
{
    return errCode_;
}