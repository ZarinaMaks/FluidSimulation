////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "fluids2d.h"

using namespace fluid;

////////// struct BasicFluid2D ///////////////////////////////////////////////
// Описание : fluidlib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
BasicFluid2D::BasicFluid2D()
{
    viscosity = 0;
    density   = 0;
}

////////// class BasicFluidModeler2D /////////////////////////////////////////
// Описание : fluidlib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
BasicFluidModeler2D::BasicFluidModeler2D()
{
    tools2D_ = nullptr;
    fluid2D_ = nullptr;
}

// (4) Инициализация всех полей
void BasicFluidModeler2D::initialize(int sizeX, int sizeY, BasicTools2D& 
                                     tools2D, BasicFluid2D& fluid2D)
{
    try
    {
        // Меняем размер полей на требуемый
        tempSF2D_.resize(sizeX, sizeY);
        tempVF2D_.resize(sizeX, sizeY);
        
        // Подключаем вспомогательные инструменты
        tools2D_ = &tools2D;
        fluid2D_ = &fluid2D;
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (5) Производит переход в новое состояние, базируясь на текущем
void BasicFluidModeler2D::compute()
{
    // Адвекция скорости
    tools2D_->model().advection(fluid2D_->speed2D, fluid2D_->speed2D);
    
    // Диффузия скорости
    tools2D_->model().diffusion(fluid2D_->speed2D, fluid2D_->viscosity);
    
    // Изменение скорости под действием внешних сил
    tools2D_->model().force(fluid2D_->speed2D, fluid2D_->force2D);
    
    // Изменение поля давлений
    tools2D_->operation().div(fluid2D_->speed2D, tempSF2D_);
    tools2D_->operation().mul(tempSF2D_, fluid2D_->density / DT);
    tools2D_->poisson().solve(fluid2D_->pressure2D, tempSF2D_, -DX * DX, 4);
    
    // Нахождение поля скоростей с нулевой дивергенцией
    tools2D_->operation().grad(fluid2D_->pressure2D, tempVF2D_);
    tools2D_->operation().mul(tempVF2D_, DT / fluid2D_->density);
    tools2D_->operation().sub(fluid2D_->speed2D, tempVF2D_);
}

// (6) Установка значений по умолчанию
void BasicFluidModeler2D::clear()
{
    tempSF2D_.clear();
    tempVF2D_.clear();
    tools2D_ = nullptr;
    fluid2D_ = nullptr;
}

////////// class FluidModeler2D //////////////////////////////////////////////
// Описание : fluidlib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

// (4) Инициализация всех полей
void FluidModeler2D::initialize(int sizeX, int sizeY, BasicTools2D& tools2D,
                                Fluid2D& fluid2D)
{
    basic2D_.initialize(sizeX, sizeY, tools2D, fluid2D.basic2D);
}

// (5) Производит переход в новое состояние, базируясь на текущем
void FluidModeler2D::compute()
{
    basic2D_.compute();
}

// (6) Установка значений по умолчанию
void FluidModeler2D::clear()
{
    basic2D_.clear();
}