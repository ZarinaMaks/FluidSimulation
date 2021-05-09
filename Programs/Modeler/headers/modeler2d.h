#ifndef MODELER2D_H
#define MODELER2D_H

////////// modeler2d /////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

//#include "fluidlib2d.h"
#include "graph2d.h"

// #include "fiolib.h???"

namespace model
{
    ////////// class MainModeler2D ///////////////////////////////////////////
    // ...
    //////////////////////////////////////////////////////////////////////////
    
    class MainModeler2D
    {
        private :
            
            // Хранит полную информацию о гидродинамической системе
            //Model2D model_;
            
            // Моделирует процессы, протекающие в гидродинамической системе
            //Modeler2D modeler_;
            
            // Хранит состояние окна программы
            graph::Window window_;
            
            // Обработчик событий
            graph::PollEvent pollEvent_;
            
            // Выводит графическое изображение системы в окно программы
            graph::TestGraph graph_;
            
        public :
            
            // (1) Конструктор
            MainModeler2D() = default;
            
            // (2) Конструктор копирования
            MainModeler2D(const MainModeler2D& modeler) = delete;
            
            // (3) Перегрузка оператора присваивания
            MainModeler2D& operator=(const MainModeler2D& modeler) = delete;
            
            // (4) Первичная инициализация модели, установление связей
            void initialize();
            
            // (5) Обработка событий, моделирование течения
            void run();
            
            // (6) Установка значений по умолчанию, завершение работы
            void clear();
            
            // (7) Деструктор
            ~MainModeler2D() = default;
    };
}

#endif