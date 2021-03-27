#ifndef GRAPH2D_H
#define GRAPH2D_H

////////// graph2d ///////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "components2d.h"

namespace graph
{
    ////////// class PollEvent ///////////////////////////////////////////////
    // Обрабатывает события в окне "window_->window" и записывает           //
    // результаты в структуру "window_->status".                            //
    //////////////////////////////////////////////////////////////////////////
    
    class PollEvent
    {
        private :
            
            // Событие в окне программы
            sf::Event event_;
            
            // Окно программы
            Window* window_;
        
        public :
            
            // (1) Конструктор
            PollEvent();
            
            // (2) Конструктор копирования
            PollEvent(const PollEvent& pollEvent) = delete;
            
            // (3) Перегрузка оператора присваивания
            PollEvent& operator=(const PollEvent& pollEvent) = delete;
            
            // (4) Первичная инициализация обработчика, установление связей
            void initialize(Window& window);
            
            // (5) Обрабатывает нажатия клавиш и состояние окна программы
            void checkEvents();
            
            // (6) Деструктор
            ~PollEvent() = default;
        
        private :
            
            // (1) Обновляет значение соответствующей переменной клавиши
            void keyRefresh(bool isPressed);
            
            // (2) Обновляет значение соответствующей переменной кнопки мыши
            void mouseButtonRefresh(bool isPressed);
    };
    
    ////////// class Graph ///////////////////////////////////////////////////
    // To do...                                                             //
    //////////////////////////////////////////////////////////////////////////
    
    /*
    class Graph
    {
        private :
            
            // Информация о моделируемой системе
            //fluid::Model2D* model_;
            
            // Окно программы
            Window* window_;
        
        public :
            
            // (1) Конструктор
            Graph();
            
            // (2) Конструктор копирования
            Graph(const Graph& graph) = delete;
            
            // (3) Перегрузка оператора присваивания
            Graph& operator=(const Graph& graph) = delete;
            
            // (4) Первичная инициализация обработчика, установление связей
            void initialize(Window& window, fluid::Model2D& model);
            
            // (5) Обрабатывает нажатия клавиш и состояние окна программы
            void draw();
            
            // (6) Деструктор
            ~Graph() = default;
    };
    */
}

#endif