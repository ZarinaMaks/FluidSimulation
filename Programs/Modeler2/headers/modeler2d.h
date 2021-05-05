#ifndef MODELER2D_H
#define MODELER2D_H

////////// modeler2d /////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include "fluidlib2d.h"
#include <cmath>
#include <iostream>

namespace model
{
    // Начальные параметры жидкости
    const fluid::Real INIT_PRESSURE  = 0.0;
    const fluid::Real INIT_SPEED_X   = 0.0;
    const fluid::Real INIT_SPEED_Y   = 0.0;
    const fluid::Real INIT_VISCOSITY = 1.0;
    const fluid::Real INIT_DENSITY   = 1000.0;
    
    // Начальные параметры поля силы тяжести
    const fluid::Real INIT_GX = 0.0;
    const fluid::Real INIT_GY = 9.8;
    
    // Начальные параметры давления на левом и правом срезе трубы
    const fluid::Real INIT_L_PRESSURE = 100000;
    const fluid::Real INIT_R_PRESSURE = 0;
    
    // Начальные параметры скорости верхней и нижней стен
    const fluid::Real INIT_U_WALL_SPEED = 0;
    const fluid::Real INIT_D_WALL_SPEED = 0;
    
    ////////// struct DrawingSet /////////////////////////////////////////////
    // ...
    //////////////////////////////////////////////////////////////////////////
    
    struct DrawingSet
    {
        public :
            
            // Цвет распределения скорости и давления по знаку
            sf::Color pSpeedColor;
            sf::Color nSpeedColor;
            sf::Color pPressureColor;
            sf::Color nPressureColor;
            
            // Цвет фона
            sf::Color backGroundColor;
            
            // Цвет границ
            sf::Color wallColor;
            sf::Color cavityColor;
            
            // Отступ от краев изображения
            int shift;
            
            // Диапазон величин давления и скорости
            fluid::Real maxPressure;
            fluid::Real maxSpeed;
            
        public :
            
            // (1) Конструктор
            DrawingSet();
            
            // (2) Конструктор копирования
            DrawingSet(const DrawingSet& set) = default;
            
            // (3) Перегрузка оператора присваивания
            DrawingSet& operator=(const DrawingSet& set) = default;
            
            // (4) Деструктор
            ~DrawingSet() = default;
    };
    
    ////////// class Painter /////////////////////////////////////////////////
    // ...
    //////////////////////////////////////////////////////////////////////////
    
    class Painter
    {
        private :
            
            // Изображение системы
            sf::Image image_;
            
            // Указатель на набор данных системы
            fluid::Model2D* model_;
            
            // Указатель на настройки режима рисования
            DrawingSet* settings_;
            
        public :
            
            // (1) Конструктор
            Painter();
            
            // (2) Конструктор копирования
            Painter(const Painter& painter) = delete;
            
            // (3) Перегрузка оператора присваивания
            Painter& operator=(const Painter& painter) = delete;
            
            // (4) Первичная инициализация модели, установление связей
            void initialize(int sizeX, int sizeY, fluid::Model2D& model, 
                            DrawingSet& settings);
            
            // (5) Подготовка фона системы
            void drawBorders();
            
            // (6) Выводит давление
            void drawPressure();
            
            // (7) Выводит компоненту скорости "x"
            void drawSpeedX();
            
            // (8) Выводит компоненту скорости "y"
            void drawSpeedY();
            
            // (9) Сохраняет картинку в файл
            void saveToFile(const std::string& filename);
            
            // (10) Деструктор
            ~Painter() = default;
            
        private :
            
            // (1) Заливает фон цветом фона
            void drawBackGround();
            
            // (2) Чертит границу стенки
            void drawWall();
            
            // (3) Чертит зоны постоянства давления
            void drawCavity();
            
            // (4) Выводит скалярное поле
            void drawSField(fluid::SField2D& field, fluid::Real max, 
                            sf::Color pColor, sf::Color nColor);
    };
    
    ////////// class ModelCreator1 ///////////////////////////////////////////
    // ...
    //////////////////////////////////////////////////////////////////////////
    
    class ModelCreator1
    {
        public :
            
            // (1) Конструктор
            ModelCreator1() = default;
            
            // (2) Конструктор копирования
            ModelCreator1(const ModelCreator1& creator) = delete;
            
            // (3) Перегрузка оператора присваивания
            ModelCreator1& operator=(const ModelCreator1& creator) = delete;
            
            // (4) Первичная инициализация модели, установление связей
            void create(int sizeX, int sizeY, fluid::Model2D& model);
            
            // (7) Деструктор
            ~ModelCreator1() = default;
            
        private :
            
            // (1) Задает всем полям нужный размер
            void resize(int sizeX, int sizeY, fluid::Model2D& model);
            
            // (2) Инициализирует поле скоростей
            void initSpeed(fluid::Model2D& model);
            
            // (3) Инициализирует поле давления
            void initPressure(fluid::Model2D& model);
            
            // (4) Инициализирует поле массовых сил
            void initForce(fluid::Model2D& model);
            
            // (5) Вязкая диффузия и плотность
            void initConst(fluid::Model2D& model);
            
            // (6) Формирует граничное условие - твердая стенка
            void initWallBorder(fluid::Model2D& model);
            
            // (7) Формирует граничное условие - сила тяжести
            void initGravityBorder(fluid::Model2D& model);
    };
    
    ////////// class ModelCreator2 ///////////////////////////////////////////
    // ...
    //////////////////////////////////////////////////////////////////////////
    
    class ModelCreator2
    {
        public :
            
            // (1) Конструктор
            ModelCreator2() = default;
            
            // (2) Конструктор копирования
            ModelCreator2(const ModelCreator2& creator) = delete;
            
            // (3) Перегрузка оператора присваивания
            ModelCreator2& operator=(const ModelCreator2& creator) = delete;
            
            // (4) Первичная инициализация модели, установление связей
            void create(int sizeX, int sizeY, fluid::Model2D& model);
            
            // (7) Деструктор
            ~ModelCreator2() = default;
            
        private :
            
            // (1) Задает всем полям нужный размер
            void resize(int sizeX, int sizeY, fluid::Model2D& model);
            
            // (2) Инициализирует поле скоростей
            void initSpeed(fluid::Model2D& model);
            
            // (3) Инициализирует поле давления
            void initPressure(fluid::Model2D& model);
            
            // (4) Инициализирует поле массовых сил
            void initForce(fluid::Model2D& model);
            
            // (5) Вязкая диффузия и плотность
            void initConst(fluid::Model2D& model);
            
            // (6) Формирует граничное условие - твердая стенка
            void initWallBorder(fluid::Model2D& model);
            
            // (7) Формирует граничное условие - сила тяжести
            void initGravityBorder(fluid::Model2D& model);
            
            // (8) Формирует граничное условие - открытая грань
            void initCavityBorder(fluid::Model2D& model);
    };
    
    ////////// class ModelCreator3 ///////////////////////////////////////////
    // ...
    //////////////////////////////////////////////////////////////////////////
    
    class ModelCreator3
    {
        public :
            
            // (3) Конструктор
            ModelCreator3() = default;
            
            // (2) Конструктор копирования
            ModelCreator3(const ModelCreator3& creator) = delete;
            
            // (3) Перегрузка оператора присваивания
            ModelCreator3& operator=(const ModelCreator3& creator) = delete;
            
            // (4) Первичная инициализация модели, установление связей
            void create(int sizeX, int sizeY, fluid::Model2D& model);
            
            // (7) Деструктор
            ~ModelCreator3() = default;
            
        private :
            
            // (1) Задает всем полям нужный размер
            void resize(int sizeX, int sizeY, fluid::Model2D& model);
            
            // (2) Инициализирует поле скоростей
            void initSpeed(fluid::Model2D& model);
            
            // (3) Инициализирует поле давления
            void initPressure(fluid::Model2D& model);
            
            // (4) Инициализирует поле массовых сил
            void initForce(fluid::Model2D& model);
            
            // (5) Вязкая диффузия и плотность
            void initConst(fluid::Model2D& model);
            
            // (6) Формирует граничное условие - твердая стенка
            void initWallBorder(fluid::Model2D& model);
            
            // (7) Формирует граничное условие - сила тяжести
            void initGravityBorder(fluid::Model2D& model);
            
            // (8) Формирует граничное условие - открытая грань
            void initCavityBorder(fluid::Model2D& model);
            
            // (9) Формирует граничное условие - движущаяся стенка
            void initSpeedBorder(fluid::Model2D& model);
    };
    
    ////////// class MainModeler2D ///////////////////////////////////////////
    // ...
    //////////////////////////////////////////////////////////////////////////
    
    class MainModeler2D
    {
        private :
            
            // Хранит полную информацию о гидродинамической системе
            fluid::Model2D model_;
            
            // Настройки режима рисования
            DrawingSet drawingSet_;
            
            // Моделирует процессы, протекающие в гидродинамической системе
            fluid::Modeler2D modeler_;
            
            // Инструменты записи состояния системы в файл ".png"
            Painter painter_;
            
            // Создает пробную систему
            ModelCreator2 creator_;
            
        public :
            
            // (1) Конструктор
            MainModeler2D() = default;
            
            // (2) Конструктор копирования
            MainModeler2D(const MainModeler2D& modeler) = delete;
            
            // (3) Перегрузка оператора присваивания
            MainModeler2D& operator=(const MainModeler2D& modeler) = delete;
            
            // (4) Первичная инициализация модели, установление связей
            void initialize(int sizeX, int sizeY);
            
            // (5) Обработка событий, моделирование течения
            void run(int cycleNum);
            
            // (6) Деструктор
            ~MainModeler2D() = default;
            
        private :
            
            // (1) Записывает состояние системы в файл ".png"
            void printStatus();
    };
}

#endif