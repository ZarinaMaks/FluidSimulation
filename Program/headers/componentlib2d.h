#ifndef COMPONENTLIB2D_H
#define COMPONENTLIB2D_H

////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "errlib.h"
#include "basiclib.h"

namespace fluid
{
    ////////// class ScalarField2D ///////////////////////////////////////////
    // Класс, описывающий двумерное скалярное поле.                         //
    //                                                                      //
    // В общем случае :                                                     //
    //  1) MIN_SIZE_X <= sizeX_ <= MAX_SIZE_X                               //
    //  2) MIN_SIZE_Y <= sizeY_ <= MAX_SIZE_Y                               //
    //////////////////////////////////////////////////////////////////////////
    
    class ScalarField2D
    {
        private :
            
            Real** points_;     // Трехмерный массив элементов поля
            int    sizeX_;      // Размер поля по "X"
            int    sizeY_;      // Размер поля по "Y"
            
        public :
            
            // (1) Конструктор (обнуляет поля класса)
            ScalarField2D();
            
            // (2) Конструктор (Сразу задает размер поля)
            ScalarField2D(int sizeX, int sizeY);
            
            // (3) Конструктор копирования
            ScalarField2D(const ScalarField2D& field);
            
            // (4) Перегрузка оператора присваивания
            ScalarField2D& operator=(const ScalarField2D& field);
            
            // (5) Изменяет размер поля, уничтожая всю информацию
            void resize(int sizeX, int sizeY);
            
            // (6) Перегрузка оператора ()
            Real& operator()(int x, int y);
            
            // (7) Перегрузка оператора () (const случай)
            const Real& operator()(int x, int y) const;
            
            // (8) Проверка на выход за границы
            bool isInRange(int x, int y) const;
            
            // (9) Возвращает размер по "X"
            int getSizeX() const;
            
            // (10) Возвращает размер по "Y"
            int getSizeY() const;
            
            // (11) Перегрузка оператора "+="
            ScalarField2D& operator+=(const ScalarField2D& field);
            
            // (12) Перегрузка оператора "-="
            ScalarField2D& operator-=(const ScalarField2D& field);
            
            // (13) Освобождает выделенную память
            void clear();
            
            // (14) Деструктор
            ~ScalarField2D();
    };
    
    ////////// class VectorField2D ///////////////////////////////////////////
    // Класс, описывающий двумерное векторное поле, как набор двух          //
    // двумерных скалярных полей.                                           //
    //////////////////////////////////////////////////////////////////////////
    
    class VectorField2D
    {
        private :
            
            ScalarField2D componentX_;  // Компонента "X"
            ScalarField2D componentY_;  // Компонента "Y"
            
        public :
            
            // (1) Конструктор
            VectorField2D() = default;
            
            // (2) Конструктор (Сразу задает размер поля)
            VectorField2D(int sizeX, int sizeY);
            
            // (3) Конструктор копирования
            VectorField2D(const VectorField2D& field);
            
            // (4) Перегрузка оператора присваивания
            VectorField2D& operator=(const VectorField2D& field) = default;
            
            // (5) Изменяет размер поля, уничтожая всю информацию
            void resize(int sizeX, int sizeY);
            
            // (6) Доступ по ссылке к скалярному полю "X"
            ScalarField2D& x();
            
            // (7) Доступ по ссылке к скалярному полю "Y"
            ScalarField2D& y();
            
            // (8) Доступ по "const" ссылке к скалярному полю "X"
            const ScalarField2D& x() const;
            
            // (9) Доступ по "const" ссылке к скалярному полю "Y"
            const ScalarField2D& y() const;
            
            // (10) Возвращает размер по "X"
            int getSizeX() const;
            
            // (11) Возвращает размер по "Y"
            int getSizeY() const;
            
            // (12) Перегрузка оператора "+="
            VectorField2D& operator+=(const VectorField2D& field);
            
            // (13) Перегрузка оператора "-="
            VectorField2D& operator-=(const VectorField2D& field);
            
            // (14) Освобождает выделенную память
            void clear();
            
            // (15) Деструктор
            ~VectorField2D() = default;
    };
    
    ////////// struct Values2D ///////////////////////////////////////////////
    // Структура, предназначеная для передачи значений интерполируемой      //
    // фунции в вершинах прямоугольника со сторонами DX, DY.                //
    //////////////////////////////////////////////////////////////////////////
    
    struct Values2D
    {
        public :
            
            Real fx0y0;       // Значение функции в вершине (x0, y0)
            Real fx0y1;       // Значение функции в вершине (x0, y1)
            Real fx1y0;       // Значение функции в вершине (x1, y0)
            Real fx1y1;       // Значение функции в вершине (x1, y1)
            
        public :
            
            // (1) Конструктор (обнуляет поля)
            Values2D();
            
            // (2) Конструктор копирования
            Values2D(const Values2D& values) = default;
            
            // (3) Перегрузка оператора присваивания
            Values2D& operator=(const Values2D& values) = default;
            
            // (4) Обнуляет поля
            void clear();
            
            // (5) Деструктор
            ~Values2D() = default;
    };
}

#endif