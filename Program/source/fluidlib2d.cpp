////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "fluidlib2d.h"

using namespace fluid;

////////// struct BasicFields2D //////////////////////////////////////////////
// Описание : fluidlib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
BasicFields2D::BasicFields2D()
{
    viscosity = 0;
    density   = 0;
}

////////// class BasicFieldsModeler2D ////////////////////////////////////////
// Описание : fluidlib2d.h.                                                 //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
BasicFieldsModeler2D::BasicFieldsModeler2D()
{
    tools2D_  = nullptr;
    fields2D_ = nullptr;
}

// (4) Инициализация всех полей
void BasicFieldsModeler2D::initialize(int sizeX, int sizeY, BasicTools2D& 
                                      tools2D, BasicFields2D& fields2D)
{
    try
    {
        // Меняем размер полей на требуемый
        tempSF2D_.resize(sizeX, sizeY);
        tempVF2D_.resize(sizeX, sizeY);
        
        // Подключаем вспомогательные инструменты
        tools2D_  = &tools2D;
        fields2D_ = &fields2D;
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (5) Производит переход в новое состояние, базируясь на текущем
void BasicFieldsModeler2D::compute()
{
    // Адвекция скорости
    tools2D_->model().advection(fields2D_->speed2D, fields2D_->speed2D);
    
    // Диффузия скорости
    tools2D_->model().diffusion(fields2D_->speed2D, fields2D_->viscosity);
    
    // Изменение скорости под действием внешних сил
    tools2D_->model().force(fields2D_->speed2D, fields2D_->force2D, 
                          fields2D_->density);
    
    // Изменение поля давлений
    tools2D_->operation().div(fields2D_->speed2D, tempSF2D_);
    tools2D_->poisson().solve(fields2D_->pressure2D, tempSF2D_, -DX * DX, 4);
    
    // Нахождение поля скоростей с нулевой дивергенцией
    tools2D_->operation().grad(fields2D_->pressure2D, tempVF2D_);
    tools2D_->operation().sub(fields2D_->speed2D, tempVF2D_);
}

// (6) Установка значений по умолчанию
void BasicFieldsModeler2D::clear()
{
    tempSF2D_.clear();
    tempVF2D_.clear();
    tools2D_  = nullptr;
    fields2D_ = nullptr;
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
void WallBorderModeler2D::initialize(BasicTools2D& tools2D, BasicFields2D& 
                                     fields2D, WallBorder2D& border2D)
{
    pressure2D_ = &fields2D.pressure2D;
    speed2D_    = &fields2D.speed2D;
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
void CavityBorderModeler2D::initialize(BasicFields2D& fields2D, 
                                       CavityBorder2D& border2D)
{
    pressure2D_ = &fields2D.pressure2D;
    speed2D_    = &fields2D.speed2D;
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
    density_   = 0;
    force2D_   = nullptr;
    gravity2D_ = nullptr;
}

// (4) Инициализация всех полей
void GravityBorderModeler2D::initialize(BasicFields2D& fields2D, 
                                        GravityBorder2D& border2D)
{
    density_   = fields2D.density;
    force2D_   = &fields2D.force2D;
    gravity2D_ = &border2D;
}

// (5) Производит переход в новое состояние, базируясь на текущем
void GravityBorderModeler2D::compute()
{
    // Проекции силы тяж., действующей на элементарный объем
    Real fX = DX * DY * density_ * gravity2D_->gX;
    Real fY = DX * DY * density_ * gravity2D_->gY;
    
    // Проходим по всем точкам рабочей зоны
    for (int i = 0; i < force2D_->getSizeX(); ++i)
    {
        for (int j = 0; j < force2D_->getSizeY(); ++j)
        {
            if (force2D_->x().area(i, j))
            {
                // Обновляем значение внешней силы в точке (i, j)
                force2D_->x().field(i, j) = fX;
                force2D_->y().field(i, j) = fY;
            }
        }
    }
}

// (6) Установка значений по умолчанию
void GravityBorderModeler2D::clear()
{
    density_   = 0;
    force2D_   = nullptr;
    gravity2D_ = nullptr;
}
