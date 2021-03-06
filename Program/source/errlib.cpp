////////// errlib ////////////////////////////////////////////////////////////
// Автор    : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
// Описание : Здесь представлены инструменты для обработки исключительных   //
//            ситуаций в модулях моделирования течения жидкости.            //
//////////////////////////////////////////////////////////////////////////////

#include "errlib.h"

using namespace err;

////////// class Exception ///////////////////////////////////////////////////
// Описание : errlib.h                                                      //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор (обнуляет поле)
Exception::Exception()
{
    errCode_ = 0;
}

// (2) Конструктор (инициализирует поле)
Exception::Exception(int newErrCode)
{
    errCode_ = newErrCode;
}

// (5) Возвращает код ошибки
int Exception::error() const
{
    return errCode_;
}

////////// class FluidException //////////////////////////////////////////////
// Описание : errlib.h                                                      //
//////////////////////////////////////////////////////////////////////////////

// (5) Виртуальный метод возврата сообщения об ошибке
const char* FluidException::what() const noexcept
{
    return "err::FluidException";
}

////////// class FioException ////////////////////////////////////////////////
// Описание : errlib.h                                                      //
//////////////////////////////////////////////////////////////////////////////

// (5) Виртуальный метод возврата сообщения об ошибке
const char* FioException::what() const noexcept
{
    return "err::FioException";
}