////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "fluidlib.h"

////////// class VectorField /////////////////////////////////////////////////
// Класс - векторное поле, содержит трехмерный массив векторов              //
// "Vector"...                                                              //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
VectorField()
{
    
}

// (2) Конструктор копирования
VectorField(const VectorField& field)
{
    
}

// (3) Перегрузка оператора присваивания
VectorField& operator=(const VectorField& field)
{
    
}

// (4) 
const Vector& get(const int& i, const int& j, const int& k)
{
    
}

// (5) 
Vector& get(const int& i, const int& j, const int& k)
{
    
}

// (6) Освобождает выделенную память
void clear()
{
    
}

// (7) Деструктор
~VectorField()
{
    
}

// TODO: add more methods

////////// class ScalarField /////////////////////////////////////////////////
// Класс - поле скаляров, содержит трехмерный массив скаляров типа          //
// "real"...                                                                //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
ScalarField()
{
    
}

// (3) Конструктор копирования
ScalarField(const ScalarField& field)
{
    
}

// (3) Перегрузка оператора присваивания
VectorField& operator=(const VectorField& field)
{
    
}
 
// (4)
const real& get(const int& i, const int& j, const int& k) const
{
    
}
 
// (5)
real& get(const int& i, const int& j, const int& k)
{
    
}
 
// (6) Освобождает выделенную память
void clear()
{
    
}
 
// (7) Деструктор
~ScalarField()
{
    
}
 
// TODO: add more methods