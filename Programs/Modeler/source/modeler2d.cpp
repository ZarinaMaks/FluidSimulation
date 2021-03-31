////////// modeler2d /////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "modeler2d.h"

using namespace model;

////////// class MainModeler2D ///////////////////////////////////////////////
// Описание : modeler2d.h                                                   //
//////////////////////////////////////////////////////////////////////////////

// (4) Первичная инициализация модели, установление связей
void MainModeler2D::initialize()
{
    // Устанавливаем 8-ой уровень сглаживания
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    // Объект, который является главным окном приложения
    window_.window.create(sf::VideoMode(600, 600), 
                           "Test Model", sf::Style::Default, settings);
        
    // Задаём максимальную частоту кадров
    window_.window.setFramerateLimit(60);
    
    // Устанавливаем связи между объектами
    pollEvent_.initialize(window_);
    graph_.initialize(600, 600, window_);
    
}

// (5) Обработка событий, моделирование течения
void MainModeler2D::run()
{
    while (!window_.status.window.closed)
    {
        graph_.draw();
        pollEvent_.checkEvents();
    }
}

// (6) Установка значений по умолчанию, завершение работы
void MainModeler2D::clear()
{
    window_.window.close();
}