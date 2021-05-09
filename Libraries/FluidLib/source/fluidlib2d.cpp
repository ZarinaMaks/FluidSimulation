////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "fluidlib2d.h"

using namespace fluid;

////////// class Modeler2D ///////////////////////////////////////////////////
// Описание : fluidlib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

// (4) Инициализация всех полей
void Modeler2D::initialize(int sizeX, int sizeY, Model2D& model2D)
{
    tools2D_.initialize(sizeX, sizeY);
    fluid2D_.initialize(sizeX, sizeY, tools2D_, model2D.fluid2D);
    border2D_.initialize(tools2D_, model2D.fluid2D, model2D.border2D);
}

// (5) Производит переход в новое состояние, базируясь на текущем
void Modeler2D::compute()
{
    border2D_.compute();
    fluid2D_.compute();
}

// (6) Установка значений по умолчанию
void Modeler2D::clear()
{
    tools2D_.clear();
    fluid2D_.clear();
    border2D_.clear();
}