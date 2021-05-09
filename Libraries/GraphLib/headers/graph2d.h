#ifndef GRAPH2D_H
#define GRAPH2D_H

////////// graph2d ///////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "components2d.h"
//#include "SFML/Graphics/Image.hpp"

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
    
    ////////// class TestGraph ///////////////////////////////////////////////
    // Test....                                                             //
    //////////////////////////////////////////////////////////////////////////
    
    class TestGraph
    {
        private :
            
            // Поле пикселей - изображение моделируемой системы
            sf::Image image_;
            
            // Текстура, соответствующая изображению
            sf::Texture texture_;
            
            // Спрайт для отображения текстуры
            sf::Sprite sprite_;
            
            // Окно программы
            Window* window_;
        
        public :
            
            // (1) Конструктор
            TestGraph();
            
            // (2) Конструктор копирования
            TestGraph(const TestGraph& graph) = delete;
            
            // (3) Перегрузка оператора присваивания
            TestGraph& operator=(const TestGraph& graph) = delete;
            
            // (4) Первичная инициализация обработчика, установление связей
            void initialize(int sizeX, int sizeY, Window& window);
            
            // (5) Обрабатывает нажатия клавиш и состояние окна программы
            void draw();
            
            // (6) Деструктор
            ~TestGraph() = default;
        
        private :
            
            // (1) Изменяет цвет пикселя картинки в соотв. с сост. мыши
            bool checkMouse();
    };
}

#endif