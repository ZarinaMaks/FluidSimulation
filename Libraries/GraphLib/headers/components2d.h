#ifndef COMPONENTS2D_H
#define COMPONENTS2D_H

////////// components2d //////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>

namespace graph
{
    ////////// struct KeyStatus //////////////////////////////////////////////
    // Если произошло нажатие клавиши, то соответствующая переменная        //
    // принимает значение "true", при отжатии значение "false".             //
    //////////////////////////////////////////////////////////////////////////
    
    struct KeyStatus
    {
        public :
            
            // Состояние цифровых клавиш
            bool num1;
            bool num2;
            bool num3;
            
            // Пробел
            bool space;
            
        public :
            
            // (1) Конструктор
            KeyStatus();
            
            // (2) Конструктор копирования
            KeyStatus(const KeyStatus& status) = default;
            
            // (3) Перегрузка оператора присваивания
            KeyStatus& operator=(const KeyStatus& status) = default;
            
            // (4) Установка значений по умолчанию, завершение работы
            void clear();
            
            // (5) Деструктор
            ~KeyStatus() = default;
    };
    
    ////////// struct MouseStatus ////////////////////////////////////////////
    // Эта структура хранит информацию о текущем состоянии мыши.            //
    //////////////////////////////////////////////////////////////////////////
    
    struct MouseStatus
    {
        public :
            
            // Состояние левой и правой кнопок мыши
            bool lButton;
            bool rButton;
            
            // Координаты курсора в окне программы
            int x;
            int y;
            
            // Нахождение внутри окна
            bool inside;
            
        public :
            
            // (1) Конструктор
            MouseStatus();
            
            // (2) Конструктор копирования
            MouseStatus(const MouseStatus& status) = default;
            
            // (3) Перегрузка оператора присваивания
            MouseStatus& operator=(const MouseStatus& status) = default;
            
            // (4) Установка значений по умолчанию, завершение работы
            void clear();
            
            // (5) Деструктор
            ~MouseStatus() = default;
    };
    
    ////////// struct WindowStatus ///////////////////////////////////////////
    // Эта структура хранит информацию о текущем состоянии окна программы.  //
    //////////////////////////////////////////////////////////////////////////
    
    struct WindowStatus
    {
        public :
            
            // Окно программы было закрыто
            bool closed;
            
            // Размеры окна программы были изменены
            bool resized;
            
        public :
            
            // (1) Конструктор
            WindowStatus();
            
            // (2) Конструктор копирования
            WindowStatus(const WindowStatus& status) = default;
            
            // (3) Перегрузка оператора присваивания
            WindowStatus& operator=(const WindowStatus& status) = default;
            
            // (4) Установка значений по умолчанию, завершение работы
            void clear();
            
            // (5) Деструктор
            ~WindowStatus() = default;
    };
    
    ////////// struct Status /////////////////////////////////////////////////
    // Хранит информацию о текущем состоянии окна программы, состоянии      //
    // клавиш и мыши.                                                       //
    //////////////////////////////////////////////////////////////////////////
    
    struct Status
    {
        public :
            
            // Информация о состоянии клавиш
            KeyStatus key;
            
            // Информация о состоянии мыши
            MouseStatus mouse;
            
            // Информация о состоянии окна программы
            WindowStatus window;
            
        public :
            
            // (1) Конструктор
            Status() = default;
            
            // (2) Конструктор копирования
            Status(const Status& status) = default;
            
            // (3) Перегрузка оператора присваивания
            Status& operator=(const Status& status) = default;
            
            // (4) Установка значений по умолчанию, завершение работы
            void clear();
            
            // (5) Деструктор
            ~Status() = default;
    };
    
    ////////// struct Window /////////////////////////////////////////////////
    // Хранит информацию об окне прогаммы.                                  //
    //////////////////////////////////////////////////////////////////////////
    
    struct Window
    {
        public :
            
            // Окно программы
            sf::RenderWindow window;
            
            // Состояние окна, клавиатуры, мыши
            Status status;
            
        public :
            
            // (1) Конструктор
            Window() = default;
            
            // (2) Конструктор копирования
            Window(const Window& window) = delete;
            
            // (3) Перегрузка оператора присваивания
            Window& operator=(const Window& window) = delete;
            
            // (4) Деструктор
            ~Window() = default;
    };
}

#endif