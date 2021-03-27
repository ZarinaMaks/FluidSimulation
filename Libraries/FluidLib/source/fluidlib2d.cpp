////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "fluidlib2d.h"

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
    tools2D_->poisson().solve(fluid2D_->pressure2D, tempSF2D_, -DX * DX, 4);
    
    // Нахождение поля скоростей с нулевой дивергенцией
    tools2D_->operation().grad(fluid2D_->pressure2D, tempVF2D_);
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

////////// class WallBorderModeler2D /////////////////////////////////////////
// Описание : fluidlib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (1) Конструктор
WallBorderModeler2D::WallBorderModeler2D()
{
    borrowX_    = 0;
    borrowY_    = 0;
    pressure2D_ = nullptr;
    speed2D_    = nullptr;
    wall2D_     = nullptr;
    interp2D_   = nullptr;
}

// (4) Инициализация всех полей
void WallBorderModeler2D::initialize(BasicTools2D& tools2D, BasicFluid2D& 
                                     fluid2D, WallBorder2D& border2D)
{
    pressure2D_ = &fluid2D.pressure2D;
    speed2D_    = &fluid2D.speed2D;
    wall2D_     = &border2D;
    interp2D_   = &tools2D.interp();
}

// (5) Производит переход в новое состояние, базируясь на текущем
void WallBorderModeler2D::compute()
{
    // Проходим по всем точкам рабочей зоны
    for (int i = 0; i < wall2D_->wall2D.getSizeX(); ++i)
    {
        for (int j = 0; j < wall2D_->wall2D.getSizeY(); ++j)
        {
            if (wall2D_->wall2D.x().area(i, j))
            {
                findBorrowDot(i, j);
                computeSpeed(i, j);
                computePressure(i, j);
            }
        }
    }
}

// (6) Установка значений по умолчанию
void WallBorderModeler2D::clear()
{
    borrowX_    = 0;
    borrowY_    = 0;
    pressure2D_ = nullptr;
    speed2D_    = nullptr;
    wall2D_     = nullptr;
    interp2D_   = nullptr;
}

////////// private ///////////////////////////////////////////////////////////

// (1) Находит координаты точки заимствования для (i, j) элемента
void WallBorderModeler2D::findBorrowDot(int i, int j)
{
    // Смещаемся на "DS" в направлении вектора нормали к поверхности
    borrowX_ = DX * i + wall2D_->wall2D.x().field(i, j) * DS;
    borrowY_ = DY * j + wall2D_->wall2D.y().field(i, j) * DS;
}

// (2) Рассчитывает скорость в (i, j) элементе
void WallBorderModeler2D::computeSpeed(int i, int j)
{
    // Проекции векторов нормали и скорости на разные направления
    Real speedX  = interp2D_->compute(speed2D_->x(), borrowX_, borrowY_);
    Real speedY  = interp2D_->compute(speed2D_->y(), borrowX_, borrowY_);
    Real normX   = wall2D_->wall2D.x().field(i, j);
    Real normY   = wall2D_->wall2D.y().field(i, j);
    Real speedPr = normX * speedX + normY * speedY;
    
    // Находим значение скорости на границе, соотв-е усл-ю прилипания
    speed2D_->x().field(i, j) = - normX * speedPr;
    speed2D_->y().field(i, j) = - normY * speedPr;
}

// (3) Рассчитывает давление в (i, j) элементе
void WallBorderModeler2D::computePressure(int i, int j)
{
    // Используя билинейную интерполяцию находим давление на границе
    pressure2D_->field(i, j) = interp2D_->compute(*(pressure2D_), 
                               borrowX_, borrowY_);
}

////////// class CavityBorderModeler2D ///////////////////////////////////////
// Описание : fluidlib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
CavityBorderModeler2D::CavityBorderModeler2D()
{
    pressure2D_ = nullptr;
    speed2D_    = nullptr;
    cavity2D_   = nullptr;
}

// (4) Инициализация всех полей
void CavityBorderModeler2D::initialize(BasicFluid2D& fluid2D, 
                                       CavityBorder2D& border2D)
{
    pressure2D_ = &fluid2D.pressure2D;
    speed2D_    = &fluid2D.speed2D;
    cavity2D_   = &border2D;
}

// (5) Производит переход в новое состояние, базируясь на текущем
void CavityBorderModeler2D::compute()
{
    // Проходим по всем точкам рабочей зоны
    for (int i = 0; i < cavity2D_->cavity2D.getSizeX(); ++i)
    {
        for (int j = 0; j < cavity2D_->cavity2D.getSizeY(); ++j)
        {
            if (cavity2D_->cavity2D.area(i, j))
            {
                // Обнуление скорости
                speed2D_->x().field(i, j) = 0;
                speed2D_->y().field(i, j) = 0;
                
                // Обновление значения давления
                pressure2D_->field(i, j) = cavity2D_->cavity2D.field(i, j);
            }
        }
    }
}

// (6) Установка значений по умолчанию
void CavityBorderModeler2D::clear()
{
    pressure2D_ = nullptr;
    speed2D_    = nullptr;
    cavity2D_   = nullptr;
}

////////// struct GravityBorder2D ////////////////////////////////////////////
// Описание : fluidlib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
GravityBorder2D::GravityBorder2D()
{
    gX = 0;
    gY = 0;
}

////////// class GravityBorderModeler2D //////////////////////////////////////
// Описание : fluidlib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
GravityBorderModeler2D::GravityBorderModeler2D()
{
    force2D_   = nullptr;
    gravity2D_ = nullptr;
}

// (4) Инициализация всех полей
void GravityBorderModeler2D::initialize(BasicFluid2D& fluid2D, 
                                        GravityBorder2D& border2D)
{
    force2D_   = &fluid2D.force2D;
    gravity2D_ = &border2D;
}

// (5) Производит переход в новое состояние, базируясь на текущем
void GravityBorderModeler2D::compute()
{
    // Проходим по всем точкам рабочей зоны
    for (int i = 0; i < force2D_->getSizeX(); ++i)
    {
        for (int j = 0; j < force2D_->getSizeY(); ++j)
        {
            if (force2D_->x().area(i, j))
            {
                // Обновляем значение внешней силы в точке (i, j)
                force2D_->x().field(i, j) = gravity2D_->gX;
                force2D_->y().field(i, j) = gravity2D_->gY;
            }
        }
    }
}

// (6) Установка значений по умолчанию
void GravityBorderModeler2D::clear()
{
    force2D_   = nullptr;
    gravity2D_ = nullptr;
}

////////// class SpeedBorderModeler2D //////////////////////////////////////
// Описание : fluidlib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
SpeedBorderModeler2D::SpeedBorderModeler2D()
{
    speed2D_     = nullptr;
    wallSpeed2D_ = nullptr;
}

// (4) Инициализация всех полей
void SpeedBorderModeler2D::initialize(BasicFluid2D& fluid2D, 
                                      SpeedBorder2D& border2D)
{
    speed2D_     = &fluid2D.speed2D;
    wallSpeed2D_ = &border2D;
}

// (5) Производит переход в новое состояние, базируясь на текущем
void SpeedBorderModeler2D::compute()
{
    // Ссылаемся на поле скоростей стенки
    VField2D& wS2D = wallSpeed2D_->wallSpeed2D;
    
    // Проходим по всем точкам рабочей зоны
    for (int i = 0; i < wS2D.getSizeX(); ++i)
    {
        for (int j = 0; j < wS2D.getSizeY(); ++j)
        {
            if (wS2D.x().area(i, j))
            {
                // Обновляем значение скорости жидкости в точке (i, j)
                speed2D_->x().field(i, j) += wS2D.x().field(i, j);
                speed2D_->y().field(i, j) += wS2D.y().field(i, j);
            }
        }
    }
}

// (6) Установка значений по умолчанию
void SpeedBorderModeler2D::clear()
{
    speed2D_     = nullptr;
    wallSpeed2D_ = nullptr;
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

////////// class BorderModeler2D /////////////////////////////////////////////
// Описание : fluidlib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

// (4) Инициализация всех полей
void BorderModeler2D::initialize(BasicTools2D& tools2D, Fluid2D& fluid2D, 
                                 Border2D& border2D)
{
    wall2D_.initialize(tools2D, fluid2D.basic2D, border2D.wall2D);
    speed2D_.initialize(fluid2D.basic2D, border2D.speed2D);
    cavity2D_.initialize(fluid2D.basic2D, border2D.cavity2D);
    gravity2D_.initialize(fluid2D.basic2D, border2D.gravity2D);
}

// (5) Производит переход в новое состояние, базируясь на текущем
void BorderModeler2D::compute()
{
    // Порядок имеет значение
    wall2D_.compute();
    cavity2D_.compute();
    speed2D_.compute();
    gravity2D_.compute();
}

// (6) Установка значений по умолчанию
void BorderModeler2D::clear()
{
    wall2D_.clear();
    cavity2D_.clear();
    speed2D_.clear();
    gravity2D_.clear();
}

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