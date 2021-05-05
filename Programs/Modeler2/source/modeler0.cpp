#include "modeler2d.h"

// Размеры рабочего поля
const int SIZE_X = 100;
const int SIZE_Y = 100;

// Вспомогательное приращение
const fluid::Real DS = 0.04;

// Инициализирует скалярное поле
void prepareScalar(fluid::SField2D& pressure)
{
    pressure.resize(SIZE_X, SIZE_Y);
    pressure.resetArea(true);
    
    for (int i = 0; i < pressure.getSizeX(); ++i)
    {
        pressure.area(i, 0) = false;
        pressure.area(i, SIZE_Y - 1) = false;
    }
    
    for (int j = 0; j < pressure.getSizeY(); ++j)
    {
        pressure.area(0, j) = false;
        pressure.area(SIZE_X - 1, j) = false;
    }
    
    for (int i = 1; i < pressure.getSizeX() - 1; ++i)
    {
        for (int j = 1; j < pressure.getSizeY() - 1; ++j)
        {
            pressure.field(i, j) = i * DS + j * DS - 3;
        }
    }
}

// Инициализирует граничное условие - стенка
void prepareWall(fluid::VField2D& wall)
{
    wall.resize(SIZE_X, SIZE_Y);
    wall.x().resetArea(false);
    wall.y().resetArea(false);
    
    for (int i = 0; i < wall.getSizeX(); ++i)
    {
        wall.x().area(i, 0) = true;
        wall.y().area(i, 0) = true;
        wall.x().area(i, SIZE_Y - 1) = true;
        wall.y().area(i, SIZE_Y - 1) = true;
    }
    
    for (int j = 0; j < wall.getSizeY(); ++j)
    {
        wall.x().area(0, j) = true;
        wall.y().area(0, j) = true;
        wall.x().area(SIZE_X - 1, j) = true;
        wall.y().area(SIZE_X - 1, j) = true;
    }
}

// Инициализирует моделирующую систему
void prepareModel(fluid::Model2D& model)
{
    // Переобозначение
    fluid::VField2D& wall = model.border2D.wall2D.wall2D;
    fluid::SField2D& cavity = model.border2D.cavity2D.pressure2D;
    fluid::SField2D& pressure = model.fluid2D.basic2D.pressure2D;
    fluid::VField2D& speed = model.fluid2D.basic2D.speed2D;
    
    // Подготовка системы (первичная инициализация)
    prepareWall(wall);
    prepareScalar(pressure);
    prepareScalar(speed.x());
    prepareScalar(speed.y());
}

int main()
{
    // Класс рисования, настройки рисования, модель для рисования
    model::Painter        painter;
    model::ModelCreator2D creator;
    model::DrawingSet     settings;
    fluid::Model2D        model;
    
    // Инициализация
    //prepareModel(model);
    creator.create(SIZE_X, SIZE_Y, model);
    painter.initialize(SIZE_X, SIZE_Y, model, settings);
    
    // Вывод информации о системе в виде файлов ".png"
    painter.drawBorders();
    painter.saveToFile("testImage0.png");
    painter.drawPressure();
    painter.saveToFile("testImage1.png");
    painter.drawSpeedX();
    painter.saveToFile("testImage2.png");
    painter.drawSpeedY();
    painter.saveToFile("testImage3.png");
    
    return 0;
}