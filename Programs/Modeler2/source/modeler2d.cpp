////////// modeler2d /////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "modeler2d.h"

using namespace model;

////////// struct DrawingSet /////////////////////////////////////////////////
// Описание : modeler2d.h                                                   //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
DrawingSet::DrawingSet()
{
    pPressureColor  = sf::Color(255, 255, 0, 255);
    nPressureColor  = sf::Color(0, 0, 0, 255);
    pSpeedColor     = sf::Color(0, 0, 255, 255);
    nSpeedColor     = sf::Color(0, 255, 0, 255);
    backGroundColor = sf::Color(255, 255, 255, 255);
    wallColor       = sf::Color(0, 0, 0, 255);
    cavityColor     = sf::Color(211, 211, 211, 255);
    shift           = 5;
    maxPressure     = 100000;
    maxSpeed        = 10;
}

////////// class Painter /////////////////////////////////////////////////////
// Описание : modeler2d.h                                                   //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (1) Конструктор
Painter::Painter()
{
    model_ = nullptr;
    settings_ = nullptr;
}

// (4) Первичная инициализация модели, установление связей
void Painter::initialize(int sizeX, int sizeY, fluid::Model2D& model, 
                         DrawingSet& settings)
{
    model_ = &model;
    settings_ = &settings;
    image_.create(sizeX + 2 * settings.shift, sizeY + 2 * settings.shift);
}

// (5) Подготовка фона системы
void Painter::drawBorders()
{
    drawBackGround();
    drawWall();
    drawCavity();
}

// (6) Выводит давление
void Painter::drawPressure()
{
    // Переобозначения
    fluid::Real maxPressure = settings_->maxPressure;
    fluid::SField2D& pressure = model_->fluid2D.basic2D.pressure2D;
    sf::Color& pColor = settings_->pPressureColor;
    sf::Color& nColor = settings_->nPressureColor;
    
    // Выводим распределение давления на картинку
    drawSField(pressure, maxPressure, pColor, nColor);
}

// (7) Выводит компоненту скорости "x"
void Painter::drawSpeedX()
{
    // Переобозначения
    fluid::Real maxSpeed = settings_->maxSpeed;
    fluid::SField2D& speedX = model_->fluid2D.basic2D.speed2D.x();
    sf::Color& pColor = settings_->pSpeedColor;
    sf::Color& nColor = settings_->nSpeedColor;
    
    // Выводим распределение компоненты скорости "x"
    drawSField(speedX, maxSpeed, pColor, nColor);
}

// (8) Выводит компоненту скорости "y"
void Painter::drawSpeedY()
{
    // Переобозначения
    fluid::Real maxSpeed = settings_->maxSpeed;
    fluid::SField2D& speedY = model_->fluid2D.basic2D.speed2D.y();
    sf::Color& pColor = settings_->pSpeedColor;
    sf::Color& nColor = settings_->nSpeedColor;
    
    // Выводим распределение компоненты скорости "y"
    drawSField(speedY, maxSpeed, pColor, nColor);
}

// (9) Сохраняет картинку в файл
void Painter::saveToFile(const std::string& filename)
{
    image_.saveToFile(filename);
}

////////// private ///////////////////////////////////////////////////////////

// (1) Заливает фон цветом фона
void Painter::drawBackGround()
{
    for (int i = 0; i < image_.getSize().x; ++i)
    {
        for (int j = 0; j < image_.getSize().y; ++j)
        {
            image_.setPixel(i, j, settings_->backGroundColor);
        }
    }
}

// (2) Чертит границу стенки
void Painter::drawWall()
{
    // Упрощаем имя
    fluid::VField2D& wall = model_->border2D.wall2D.wall2D;
    int shift = settings_->shift;
    
    // Проходим по всем элементам стенки
    for (int i = 0; i < wall.getSizeX(); ++i)
    {
        for (int j = 0; j < wall.getSizeY(); ++j)
        {
            if (wall.x().area(i, j))
            {
                image_.setPixel(i + shift, j + shift, settings_->wallColor);
            }
        }
    }
}

// (3) Чертит зоны постоянства давления
void Painter::drawCavity()
{
    // Упрощаем имя
    fluid::SField2D& cavity = model_->border2D.cavity2D.pressure2D;
    int shift = settings_->shift;
    
    // Проходим по всем элементам стенки
    for (int i = 0; i < cavity.getSizeX(); ++i)
    {
        for (int j = 0; j < cavity.getSizeY(); ++j)
        {
            if (cavity.area(i, j))
            {
                image_.setPixel(i + shift, j + shift, settings_->cavityColor);
            }
        }
    }
}

// (4) Выводит скалярное поле
void Painter::drawSField(fluid::SField2D& field, fluid::Real max, 
                         sf::Color pColor, sf::Color nColor)
{
    // Цвет пикселя, зависящий от знака величины
    sf::Color color;
    int shift = settings_->shift;
    
    // Проходим по всем точкам 
    for (int i = 0; i < field.getSizeX(); ++i)
    {
        for (int j = 0; j < field.getSizeY(); ++j)
        {
            if (field.area(i, j))
            {
                // Выбираем цвет пикселя и его прозрачность
                if (field.field(i, j) > 0.000001)
                {
                    color = pColor;
                    color.a *= field.field(i, j) / max;
                }
                else
                if (field.field(i, j) < -0.000001)
                {
                    color = nColor;
                    color.a *= -field.field(i, j) / max;
                }
                else
                {
                    color = settings_->backGroundColor;
                }
                
                // Меняем цвет пикселя на картинке
                image_.setPixel(i + shift, j + shift, color);
            }
        }
    }
}

////////// class ModelCreator1 ///////////////////////////////////////////////
// Описание : modeler2d.h                                                   //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (4) Первичная инициализация модели, установление связей
void ModelCreator1::create(int sizeX, int sizeY, fluid::Model2D& model)
{
    resize(sizeX, sizeY, model);
    initSpeed(model);
    initPressure(model);
    initForce(model);
    initConst(model);
    initWallBorder(model);
    initGravityBorder(model);
}

////////// private ///////////////////////////////////////////////////////////

// (1) Задает всем полям нужный размер
void ModelCreator1::resize(int sizeX, int sizeY, fluid::Model2D& model)
{
    // Задаем размер полям жидкости
    model.fluid2D.basic2D.force2D.resize(sizeX, sizeY);
    model.fluid2D.basic2D.speed2D.resize(sizeX, sizeY);
    model.fluid2D.basic2D.pressure2D.resize(sizeX, sizeY);
    
    // Задаем размер полям граничных условий
    model.border2D.wall2D.wall2D.resize(sizeX, sizeY);
    model.border2D.cavity2D.border2D.resize(sizeX, sizeY);
    model.border2D.cavity2D.pressure2D.resize(sizeX, sizeY);
    model.border2D.speed2D.wallSpeed2D.resize(sizeX, sizeY);
}

// (2) Инициализирует поле скоростей
void ModelCreator1::initSpeed(fluid::Model2D& model)
{
    // Переобозначение
    fluid::VField2D& speed = model.fluid2D.basic2D.speed2D;
    
    // Обновляем рабочую область
    speed.x().resetArea(true);
    speed.y().resetArea(true);
    
    // Удаляем крайние горизонтальные линии области
    for (int i = 0; i < speed.getSizeX(); ++i)
    {
        speed.x().area(i, 0) = false;
        speed.y().area(i, 0) = false;
        speed.x().area(i, speed.getSizeY() - 1) = false;
        speed.y().area(i, speed.getSizeY() - 1) = false;
    }
    
    // Удаляем крайние вертикальные линии области
    for (int j = 0; j < speed.getSizeY(); ++j)
    {
        speed.x().area(0, j) = false;
        speed.y().area(0, j) = false;
        speed.x().area(speed.getSizeX() - 1, j) = false;
        speed.y().area(speed.getSizeX() - 1, j) = false;
    }
    
    // Проходим по всем точкам поля 
    for (int i = 0; i < speed.x().getSizeX(); ++i)
    {
        for (int j = 0; j < speed.x().getSizeY(); ++j)
        {
            if (speed.x().area(i, j))
            {
                speed.x().field(i, j) = INIT_SPEED_X;
                speed.y().field(i, j) = INIT_SPEED_Y;
            }
        }
    }
}

// (3) Инициализирует поле давления
void ModelCreator1::initPressure(fluid::Model2D& model)
{
    // Переобозначение
    fluid::SField2D& pressure = model.fluid2D.basic2D.pressure2D;
    
    // Обновляем рабочую область
    pressure.resetArea(true);
    
    // Удаляем крайние горизонтальные линии области
    for (int i = 0; i < pressure.getSizeX(); ++i)
    {
        pressure.area(i, 0) = false;
        pressure.area(i, pressure.getSizeY() - 1) = false;
    }
    
    // Удаляем крайние вертикальные линии области
    for (int j = 0; j < pressure.getSizeY(); ++j)
    {
        pressure.area(0, j) = false;
        pressure.area(pressure.getSizeX() - 1, j) = false;
    }
    
    // Проходим по всем точкам поля 
    for (int i = 0; i < pressure.getSizeX(); ++i)
    {
        for (int j = 0; j < pressure.getSizeY(); ++j)
        {
            pressure.field(i, j) = INIT_PRESSURE;
        }
    }
    
    //pressure.field(30, 30) = 10;
    //pressure.field(70, 70) = 10;
    //pressure.field(49, 50) = 10;
    //pressure.field(50, 51) = 10;
    //pressure.field(50, 49) = 10;
    //pressure.field(50, 51) = 10;
}

// (4) Инициализирует поле массовых сил
void ModelCreator1::initForce(fluid::Model2D& model)
{
    // Переобозначение
    fluid::VField2D& force = model.fluid2D.basic2D.force2D;
    
    // Обновляем рабочую область
    force.x().resetArea(false);
    force.y().resetArea(false);
    
    // Удаляем крайние горизонтальные линии области
    for (int i = 0; i < force.getSizeX(); ++i)
    {
        force.x().area(i, 0) = false;
        force.y().area(i, 0) = false;
        force.x().area(i, force.getSizeY() - 1) = false;
        force.y().area(i, force.getSizeY() - 1) = false;
    }
    
    // Удаляем крайние вертикальные линии области
    for (int j = 0; j < force.getSizeY(); ++j)
    {
        force.x().area(0, j) = false;
        force.y().area(0, j) = false;
        force.x().area(force.getSizeX() - 1, j) = false;
        force.y().area(force.getSizeX() - 1, j) = false;
    }
}

// (5) Вязкая диффузия и плотность
void ModelCreator1::initConst(fluid::Model2D& model)
{
    model.fluid2D.basic2D.viscosity = INIT_VISCOSITY;
    model.fluid2D.basic2D.density = INIT_DENSITY;
}

// (6) Формирует граничное условие - твердая стенка
void ModelCreator1::initWallBorder(fluid::Model2D& model)
{
    // Переобозначение
    fluid::VField2D& wall = model.border2D.wall2D.wall2D;
    
    // Создаем крайние горизонтальные линии области
    for (int i = 1; i < wall.getSizeX() - 1; ++i)
    {
        // Обновляем рабочую область для границы
        wall.x().area(i, 0) = true;
        wall.y().area(i, 0) = true;
        wall.x().area(i, wall.getSizeY() - 1) = true;
        wall.y().area(i, wall.getSizeY() - 1) = true;
        
        // Обновляем векторы нормали
        wall.x().field(i, 0) = 0.0;
        wall.y().field(i, 0) = 1.0;
        wall.x().field(i, wall.getSizeY() - 1) = 0.0;
        wall.y().field(i, wall.getSizeY() - 1) = -1.0;
    }
    
    // Создаем крайние вертикальные линии области
    for (int j = 1; j < wall.getSizeY() - 1; ++j)
    {
        // Обновляем рабочую область для границы
        wall.x().area(0, j) = true;
        wall.y().area(0, j) = true;
        wall.x().area(wall.getSizeX() - 1, j) = true;
        wall.y().area(wall.getSizeX() - 1, j) = true;
        
        // Обновляем векторы нормали
        wall.x().field(0, j) = 1.0;
        wall.y().field(0, j) = 0.0;
        wall.x().field(wall.getSizeX() - 1, j) = -1.0;
        wall.y().field(wall.getSizeX() - 1, j) = 0.0;
    }
}

// (7) Формирует граничное условие - сила тяжести
void ModelCreator1::initGravityBorder(fluid::Model2D& model)
{
    model.border2D.gravity2D.gX = INIT_GX;
    model.border2D.gravity2D.gY = INIT_GY;
}

////////// class ModelCreator2 ///////////////////////////////////////////////
// Описание : modeler2d.h                                                   //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (4) Первичная инициализация модели, установление связей
void ModelCreator2::create(int sizeX, int sizeY, fluid::Model2D& model)
{
    resize(sizeX, sizeY, model);
    initSpeed(model);
    initPressure(model);
    initForce(model);
    initConst(model);
    initWallBorder(model);
    initGravityBorder(model);
    initCavityBorder(model);
}

////////// private ///////////////////////////////////////////////////////////

// (1) Задает всем полям нужный размер
void ModelCreator2::resize(int sizeX, int sizeY, fluid::Model2D& model)
{
    // Задаем размер полям жидкости
    model.fluid2D.basic2D.force2D.resize(sizeX, sizeY);
    model.fluid2D.basic2D.speed2D.resize(sizeX, sizeY);
    model.fluid2D.basic2D.pressure2D.resize(sizeX, sizeY);
    
    // Задаем размер полям граничных условий
    model.border2D.wall2D.wall2D.resize(sizeX, sizeY);
    model.border2D.cavity2D.border2D.resize(sizeX, sizeY);
    model.border2D.cavity2D.pressure2D.resize(sizeX, sizeY);
    model.border2D.speed2D.wallSpeed2D.resize(sizeX, sizeY);
}

// (2) Инициализирует поле скоростей
void ModelCreator2::initSpeed(fluid::Model2D& model)
{
    // Переобозначение
    fluid::VField2D& speed = model.fluid2D.basic2D.speed2D;
    
    // Обновляем рабочую область
    speed.x().resetArea(true);
    speed.y().resetArea(true);
    
    // Удаляем крайние горизонтальные линии области
    for (int i = 0; i < speed.getSizeX(); ++i)
    {
        speed.x().area(i, 0) = false;
        speed.y().area(i, 0) = false;
        speed.x().area(i, speed.getSizeY() - 1) = false;
        speed.y().area(i, speed.getSizeY() - 1) = false;
    }
    
    // Удаляем крайние вертикальные линии области
    for (int j = 0; j < speed.getSizeY(); ++j)
    {
        speed.x().area(0, j) = false;
        speed.y().area(0, j) = false;
        speed.x().area(speed.getSizeX() - 1, j) = false;
        speed.y().area(speed.getSizeX() - 1, j) = false;
    }
    
    // Проходим по всем точкам поля 
    for (int i = 0; i < speed.x().getSizeX(); ++i)
    {
        for (int j = 0; j < speed.x().getSizeY(); ++j)
        {
            if (speed.x().area(i, j))
            {
                speed.x().field(i, j) = INIT_SPEED_X;
                speed.y().field(i, j) = INIT_SPEED_Y;
            }
        }
    }
}

// (3) Инициализирует поле давления
void ModelCreator2::initPressure(fluid::Model2D& model)
{
    // Переобозначение
    fluid::SField2D& pressure = model.fluid2D.basic2D.pressure2D;
    
    // Обновляем рабочую область
    pressure.resetArea(true);
    
    // Удаляем крайние горизонтальные линии области
    for (int i = 0; i < pressure.getSizeX(); ++i)
    {
        pressure.area(i, 0) = false;
        pressure.area(i, pressure.getSizeY() - 1) = false;
    }
    
    // Удаляем крайние вертикальные линии области
    for (int j = 0; j < pressure.getSizeY(); ++j)
    {
        pressure.area(0, j) = false;
        pressure.area(pressure.getSizeX() - 1, j) = false;
    }
    
    // Проходим по всем точкам поля 
    for (int i = 0; i < pressure.getSizeX(); ++i)
    {
        for (int j = 0; j < pressure.getSizeY(); ++j)
        {
            pressure.field(i, j) = INIT_PRESSURE;
        }
    }
}

// (4) Инициализирует поле массовых сил
void ModelCreator2::initForce(fluid::Model2D& model)
{
    // Переобозначение
    fluid::VField2D& force = model.fluid2D.basic2D.force2D;
    
    // Обновляем рабочую область
    force.x().resetArea(false);
    force.y().resetArea(false);
    
    // Удаляем крайние горизонтальные линии области
    for (int i = 0; i < force.getSizeX(); ++i)
    {
        force.x().area(i, 0) = false;
        force.y().area(i, 0) = false;
        force.x().area(i, force.getSizeY() - 1) = false;
        force.y().area(i, force.getSizeY() - 1) = false;
    }
    
    // Удаляем крайние вертикальные линии области
    for (int j = 0; j < force.getSizeY(); ++j)
    {
        force.x().area(0, j) = false;
        force.y().area(0, j) = false;
        force.x().area(force.getSizeX() - 1, j) = false;
        force.y().area(force.getSizeX() - 1, j) = false;
    }
}

// (5) Вязкая диффузия и плотность
void ModelCreator2::initConst(fluid::Model2D& model)
{
    model.fluid2D.basic2D.viscosity = INIT_VISCOSITY;
    model.fluid2D.basic2D.density = INIT_DENSITY;
}

// (6) Формирует граничное условие - твердая стенка
void ModelCreator2::initWallBorder(fluid::Model2D& model)
{
    // Переобозначение
    fluid::VField2D& wall = model.border2D.wall2D.wall2D;
    
    // Создаем крайние горизонтальные линии области
    for (int i = 1; i < wall.getSizeX() - 1; ++i)
    {
        // Обновляем рабочую область для границы
        wall.x().area(i, 0) = true;
        wall.y().area(i, 0) = true;
        wall.x().area(i, wall.getSizeY() - 1) = true;
        wall.y().area(i, wall.getSizeY() - 1) = true;
        
        // Обновляем векторы нормали
        wall.x().field(i, 0) = 0.0;
        wall.y().field(i, 0) = 1.0;
        wall.x().field(i, wall.getSizeY() - 1) = 0.0;
        wall.y().field(i, wall.getSizeY() - 1) = -1.0;
    }
}

// (7) Формирует граничное условие - сила тяжести
void ModelCreator2::initGravityBorder(fluid::Model2D& model)
{
    model.border2D.gravity2D.gX = INIT_GX;
    model.border2D.gravity2D.gY = INIT_GY;
}

// (8) Формирует граничное условие - открытая грань
void ModelCreator2::initCavityBorder(fluid::Model2D& model)
{
    // Переобозначение
    fluid::VField2D& border = model.border2D.cavity2D.border2D;
    fluid::SField2D& pressure = model.border2D.cavity2D.pressure2D;
    
    // Создаем крайние вертикальные линии области
    for (int j = 1; j < pressure.getSizeY() - 1; ++j)
    {
        // Обновляем рабочую область для границы
        pressure.area(0, j) = true;
        pressure.area(pressure.getSizeX() - 1, j) = true;
        border.x().area(0, j) = true;
        border.x().area(border.getSizeX() - 1, j) = true;
        border.y().area(0, j) = true;
        border.y().area(border.getSizeX() - 1, j) = true;
        
        // Обновляем векторы нормали на границе
        border.x().field(0, j) = 1.0;
        border.y().field(0, j) = 0.0;
        border.x().field(border.getSizeX() - 1, j) = -1.0;
        border.y().field(border.getSizeX() - 1, j) = 0.0;
        
        // Обновляем давление на границе
        pressure.field(0, j) = INIT_L_PRESSURE;
        pressure.field(pressure.getSizeX() - 1, j) = INIT_R_PRESSURE;
    }
}

////////// class ModelCreator3 ///////////////////////////////////////////////
// Описание : modeler2d.h                                                   //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (4) Первичная инициализация модели, установление связей
void ModelCreator3::create(int sizeX, int sizeY, fluid::Model2D& model)
{
    resize(sizeX, sizeY, model);
    initSpeed(model);
    initPressure(model);
    initForce(model);
    initConst(model);
    initWallBorder(model);
    initGravityBorder(model);
    initCavityBorder(model);
    initSpeedBorder(model);
}

////////// private ///////////////////////////////////////////////////////////

// (1) Задает всем полям нужный размер
void ModelCreator3::resize(int sizeX, int sizeY, fluid::Model2D& model)
{
    // Задаем размер полям жидкости
    model.fluid2D.basic2D.force2D.resize(sizeX, sizeY);
    model.fluid2D.basic2D.speed2D.resize(sizeX, sizeY);
    model.fluid2D.basic2D.pressure2D.resize(sizeX, sizeY);
    
    // Задаем размер полям граничных условий
    model.border2D.wall2D.wall2D.resize(sizeX, sizeY);
    model.border2D.cavity2D.border2D.resize(sizeX, sizeY);
    model.border2D.cavity2D.pressure2D.resize(sizeX, sizeY);
    model.border2D.speed2D.wallSpeed2D.resize(sizeX, sizeY);
}

// (2) Инициализирует поле скоростей
void ModelCreator3::initSpeed(fluid::Model2D& model)
{
    // Переобозначение
    fluid::VField2D& speed = model.fluid2D.basic2D.speed2D;
    
    // Обновляем рабочую область
    speed.x().resetArea(true);
    speed.y().resetArea(true);
    
    // Удаляем крайние горизонтальные линии области
    for (int i = 0; i < speed.getSizeX(); ++i)
    {
        speed.x().area(i, 0) = false;
        speed.y().area(i, 0) = false;
        speed.x().area(i, speed.getSizeY() - 1) = false;
        speed.y().area(i, speed.getSizeY() - 1) = false;
    }
    
    // Удаляем крайние вертикальные линии области
    for (int j = 0; j < speed.getSizeY(); ++j)
    {
        speed.x().area(0, j) = false;
        speed.y().area(0, j) = false;
        speed.x().area(speed.getSizeX() - 1, j) = false;
        speed.y().area(speed.getSizeX() - 1, j) = false;
    }
    
    // Проходим по всем точкам поля 
    for (int i = 0; i < speed.x().getSizeX(); ++i)
    {
        for (int j = 0; j < speed.x().getSizeY(); ++j)
        {
            if (speed.x().area(i, j))
            {
                speed.x().field(i, j) = INIT_SPEED_X;
                speed.y().field(i, j) = INIT_SPEED_Y;
            }
        }
    }
}

// (3) Инициализирует поле давления
void ModelCreator3::initPressure(fluid::Model2D& model)
{
    // Переобозначение
    fluid::SField2D& pressure = model.fluid2D.basic2D.pressure2D;
    
    // Обновляем рабочую область
    pressure.resetArea(true);
    
    // Удаляем крайние горизонтальные линии области
    for (int i = 0; i < pressure.getSizeX(); ++i)
    {
        pressure.area(i, 0) = false;
        pressure.area(i, pressure.getSizeY() - 1) = false;
    }
    
    // Удаляем крайние вертикальные линии области
    for (int j = 0; j < pressure.getSizeY(); ++j)
    {
        pressure.area(0, j) = false;
        pressure.area(pressure.getSizeX() - 1, j) = false;
    }
    
    // Проходим по всем точкам поля 
    for (int i = 0; i < pressure.getSizeX(); ++i)
    {
        for (int j = 0; j < pressure.getSizeY(); ++j)
        {
            pressure.field(i, j) = INIT_PRESSURE;
        }
    }
}

// (4) Инициализирует поле массовых сил
void ModelCreator3::initForce(fluid::Model2D& model)
{
    // Переобозначение
    fluid::VField2D& force = model.fluid2D.basic2D.force2D;
    
    // Обновляем рабочую область
    force.x().resetArea(false);
    force.y().resetArea(false);
    
    // Удаляем крайние горизонтальные линии области
    for (int i = 0; i < force.getSizeX(); ++i)
    {
        force.x().area(i, 0) = false;
        force.y().area(i, 0) = false;
        force.x().area(i, force.getSizeY() - 1) = false;
        force.y().area(i, force.getSizeY() - 1) = false;
    }
    
    // Удаляем крайние вертикальные линии области
    for (int j = 0; j < force.getSizeY(); ++j)
    {
        force.x().area(0, j) = false;
        force.y().area(0, j) = false;
        force.x().area(force.getSizeX() - 1, j) = false;
        force.y().area(force.getSizeX() - 1, j) = false;
    }
}

// (5) Вязкая диффузия и плотность
void ModelCreator3::initConst(fluid::Model2D& model)
{
    model.fluid2D.basic2D.viscosity = INIT_VISCOSITY;
    model.fluid2D.basic2D.density = INIT_DENSITY;
}

// (6) Формирует граничное условие - твердая стенка
void ModelCreator3::initWallBorder(fluid::Model2D& model)
{
    // Переобозначение
    fluid::VField2D& wall = model.border2D.wall2D.wall2D;
    
    // Создаем крайние горизонтальные линии области
    for (int i = 1; i < wall.getSizeX() - 1; ++i)
    {
        // Обновляем рабочую область для границы
        wall.x().area(i, 0) = true;
        wall.y().area(i, 0) = true;
        wall.x().area(i, wall.getSizeY() - 1) = true;
        wall.y().area(i, wall.getSizeY() - 1) = true;
        
        // Обновляем векторы нормали
        wall.x().field(i, 0) = 0.0;
        wall.y().field(i, 0) = 1.0;
        wall.x().field(i, wall.getSizeY() - 1) = 0.0;
        wall.y().field(i, wall.getSizeY() - 1) = -1.0;
    }
}

// (7) Формирует граничное условие - сила тяжести
void ModelCreator3::initGravityBorder(fluid::Model2D& model)
{
    model.border2D.gravity2D.gX = INIT_GX;
    model.border2D.gravity2D.gY = INIT_GY;
}

// (8) Формирует граничное условие - открытая грань
void ModelCreator3::initCavityBorder(fluid::Model2D& model)
{
    // Переобозначение
    fluid::VField2D& border = model.border2D.cavity2D.border2D;
    fluid::SField2D& pressure = model.border2D.cavity2D.pressure2D;
    
    // Создаем крайние вертикальные линии области
    for (int j = 1; j < pressure.getSizeY() - 1; ++j)
    {
        // Обновляем рабочую область для границы
        pressure.area(0, j) = true;
        pressure.area(pressure.getSizeX() - 1, j) = true;
        border.x().area(0, j) = true;
        border.x().area(border.getSizeX() - 1, j) = true;
        border.y().area(0, j) = true;
        border.y().area(border.getSizeX() - 1, j) = true;
        
        // Обновляем векторы нормали на границе
        border.x().field(0, j) = 1.0;
        border.y().field(0, j) = 0.0;
        border.x().field(border.getSizeX() - 1, j) = -1.0;
        border.y().field(border.getSizeX() - 1, j) = 0.0;
        
        // Обновляем давление на границе
        pressure.field(0, j) = INIT_L_PRESSURE;
        pressure.field(pressure.getSizeX() - 1, j) = INIT_R_PRESSURE;
    }
}

// (9) Формирует граничное условие - движущаяся стенка
void ModelCreator3::initSpeedBorder(fluid::Model2D& model)
{
    // Переобозначение
    fluid::VField2D& wallSpeed = model.border2D.speed2D.wallSpeed2D;
    
    // Создаем крайние горизонтальные линии области
    for (int i = 1; i < wallSpeed.getSizeX() - 1; ++i)
    {
        // Обновляем рабочую область для границы
        wallSpeed.x().area(i, 0) = true;
        wallSpeed.y().area(i, 0) = true;
        wallSpeed.x().area(i, wallSpeed.getSizeY() - 1) = true;
        wallSpeed.y().area(i, wallSpeed.getSizeY() - 1) = true;
        
        // Обновляем скорости
        wallSpeed.x().field(i, 0) = INIT_U_WALL_SPEED;
        wallSpeed.x().field(i, wallSpeed.getSizeY() - 1) = INIT_D_WALL_SPEED;
    }
}

////////// class MainModeler2D ///////////////////////////////////////////////
// Описание : modeler2d.h                                                   //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (4) Первичная инициализация модели, установление связей
void MainModeler2D::initialize(int sizeX, int sizeY)
{
    creator_.create(sizeX, sizeY, model_);
    painter_.initialize(sizeX, sizeY, model_, drawingSet_);
    modeler_.initialize(sizeX, sizeY, model_);
}

// (5) Обработка событий, моделирование течения
void MainModeler2D::run(int cycleNum)
{
    // Переобозначение
    fluid::VField2D& speed = model_.fluid2D.basic2D.speed2D;
    fluid::SField2D& pressure = model_.fluid2D.basic2D.pressure2D;
    
    // Моделирует течение (cycleNum итераций)
    for (int i = 0; i < cycleNum; ++i)
    {
        modeler_.compute();
        
        if (i % 10 == 0)
        {
            std::cout << "\n Time : " << i << " ms; ";
        }
        
        if (i % 500 == 0)
        {
            std::cout << "\n";
            // Записываем поперечный срез
            for (int j = 0; j < speed.getSizeY(); ++j)
            {
                std::cout << "(" << fluid::DY / 2 + j * fluid::DY << "; ";
                std::cout << speed.x().field(100, j) << ") ";
            }
            
            std::cout << "\n\n";
            // Записываем поперечный срез
            for (int j = 0; j < speed.getSizeY(); ++j)
            {
                std::cout << "(" << fluid::DY / 2 + j * fluid::DY << "; ";
                std::cout << speed.y().field(100, j) << ") ";
            }
            
            std::cout << "\n\n";
            // Записываем поперечный срез
            for (int j = 0; j < pressure.getSizeY(); ++j)
            {
                std::cout << "(" << fluid::DY / 2 + j * fluid::DY << "; ";
                std::cout << pressure.field(100, j) << ") ";
            }
        }
    }
    
    std::cout << "\n";
    // Записываем поперечный срез
    for (int j = 0; j < speed.getSizeY(); ++j)
    {
        std::cout << "(" << fluid::DY / 2 + j * fluid::DY << "; ";
        std::cout << speed.x().field(100, j) << ") ";
    }
    
    std::cout << "\n\n";
    // Записываем поперечный срез
    for (int j = 0; j < speed.getSizeY(); ++j)
    {
        std::cout << "(" << fluid::DY / 2 + j * fluid::DY << "; ";
        std::cout << speed.y().field(100, j) << ") ";
    }
    
    std::cout << "\n\n";
    // Записываем поперечный срез
    for (int j = 0; j < pressure.getSizeY(); ++j)
    {
        std::cout << "(" << fluid::DY / 2 + j * fluid::DY << "; ";
        std::cout << pressure.field(100, j) << ") ";
    }
    
    std::cout << "\n\n";
    // Записываем поперечный срез
    for (int i = 0; i < pressure.getSizeX(); ++i)
    {
        std::cout << "(" << fluid::DX / 2 + i * fluid::DX << "; ";
        std::cout << pressure.field(i, 20) << ") ";
    }
    
    // Проводит запись среза состояния системы
    printStatus();
}

////////// private ///////////////////////////////////////////////////////////

// (1) Записывает состояние системы в файл ".png"
void MainModeler2D::printStatus()
{
    // Граница - твердая стенка
    painter_.drawBorders();
    painter_.saveToFile("model_border_wall.png");
    
    // Поле давления
    painter_.drawPressure();
    painter_.saveToFile("model_fluid_pressure.png");
    
    // Компоненты поля скорости
    painter_.drawSpeedX();
    painter_.saveToFile("model_fluid_speed_x.png");
    painter_.drawSpeedY();
    painter_.saveToFile("model_fluid_speed_y.png");
}
