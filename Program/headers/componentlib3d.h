#ifndef COMPONENTLIB3D_H
#define COMPONENTLIB3D_H

////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "errlib.h"
#include "basiclib.h"

namespace fluid
{
    ////////// class ScalarField3D ///////////////////////////////////////////
    // Класс, описывающий трехмерное скалярное поле.                        //
    //                                                                      //
    // В общем случае :                                                     //
    //  1) MIN_SIZE_X <= sizeX_ <= MAX_SIZE_X                               //
    //  2) MIN_SIZE_Y <= sizeY_ <= MAX_SIZE_Y                               //
    //  3) MIN_SIZE_Z <= sizeZ_ <= MAX_SIZE_Z                               //
    //////////////////////////////////////////////////////////////////////////
    
    class ScalarField3D
    {
        private :
            
            Real*** points_;        // Трехмерный массив элементов поля
            int     sizeX_;         // Размер поля по "X"
            int     sizeY_;         // Размер поля по "Y"
            int     sizeZ_;         // Размер поля по "Z"
            
        public :
            
            // (1) Конструктор (обнуляет поля класса)
            ScalarField3D();
            
            // (2) Конструктор (Сразу задает размер поля)
            ScalarField3D(int sizeX, int sizeY, int sizeZ);
            
            // (3) Конструктор копирования
            ScalarField3D(const ScalarField3D& field);
            
            // (4) Перегрузка оператора присваивания
            ScalarField3D& operator=(const ScalarField3D& field);
            
            // (5) Изменяет размер поля, уничтожая всю информацию
            void resize(int sizeX, int sizeY, int sizeZ);
            
            // (6) Перегрузка оператора ()
            Real& operator()(int x, int y, int z);
            
            // (7) Перегрузка оператора () (const случай)
            const Real& operator()(int x, int y, int z) const;
            
            // (8) Проверка на выход за границы
            bool isInRange(int x, int y, int z) const;
            
            // (9) Возвращает размер по "X"
            int getSizeX() const;
            
            // (10) Возвращает размер по "Y"
            int getSizeY() const;
            
            // (11) Возвращает размер по "Z"
            int getSizeZ() const;
            
            // (12) Перегрузка оператора "+="
            ScalarField3D& operator+=(const ScalarField3D& field);
            
            // (13) Перегрузка оператора "-="
            ScalarField3D& operator-=(const ScalarField3D& field);
            
            // (14) Освобождает выделенную память
            void clear();
            
            // (15) Деструктор
            ~ScalarField3D();
    };
    
    ////////// class VectorField3D ///////////////////////////////////////////
    // Класс, описывающий векторное поле, как набор трех скалярных полей.   //
    //////////////////////////////////////////////////////////////////////////
    
    class VectorField3D
    {
        private :
            
            ScalarField3D componentX_;  // Компонента "X"
            ScalarField3D componentY_;  // Компонента "Y"
            ScalarField3D componentZ_;  // Компонента "Z"
            
        public :
            
            // (1) Конструктор
            VectorField3D() = default;
            
            // (2) Конструктор (Сразу задает размер поля)
            VectorField3D(int sizeX, int sizeY, int sizeZ);
            
            // (3) Конструктор копирования
            VectorField3D(const VectorField3D& field);
            
            // (4) Перегрузка оператора присваивания
            VectorField3D& operator=(const VectorField3D& field) = default;
            
            // (5) Изменяет размер поля, уничтожая всю информацию
            void resize(int sizeX, int sizeY, int sizeZ);
            
            // (6) Доступ по ссылке к скалярному полю "X"
            ScalarField3D& x();
            
            // (7) Доступ по ссылке к скалярному полю "Y"
            ScalarField3D& y();
            
            // (8) Доступ по ссылке к скалярному полю "Z"
            ScalarField3D& z();
            
            // (9) Доступ по "const" ссылке к скалярному полю "X"
            const ScalarField3D& x() const;
            
            // (10) Доступ по "const" ссылке к скалярному полю "Y"
            const ScalarField3D& y() const;
            
            // (11) Доступ по "const" ссылке к скалярному полю "Z"
            const ScalarField3D& z() const;
            
            // (12) Возвращает размер по "X"
            int getSizeX() const;
            
            // (13) Возвращает размер по "Y"
            int getSizeY() const;
            
            // (14) Возвращает размер по "Z"
            int getSizeZ() const;
            
            // (15) Перегрузка оператора "+="
            VectorField3D& operator+=(const VectorField3D& field);
            
            // (16) Перегрузка оператора "-="
            VectorField3D& operator-=(const VectorField3D& field);
            
            // (17) Освобождает выделенную память
            void clear();
            
            // (18) Деструктор
            ~VectorField3D() = default;
    };
    
    ////////// struct Values3D ///////////////////////////////////////////////
    // Структура, предназначеная для передачи значений интерполируемой      //
    // фунции в вершинах параллелепипеда со сторонами DX, DY, DZ.           //
    //////////////////////////////////////////////////////////////////////////
    
    struct Values3D
    {
        public :
            
            Real fx0y0z0;       // Значение функции в вершине (x0, y0, z0)
            Real fx0y0z1;       // Значение функции в вершине (x0, y0, z1)
            Real fx0y1z0;       // Значение функции в вершине (x0, y1, z0)
            Real fx0y1z1;       // Значение функции в вершине (x0, y1, z1)
            Real fx1y0z0;       // Значение функции в вершине (x1, y0, z0)
            Real fx1y0z1;       // Значение функции в вершине (x1, y0, z1)
            Real fx1y1z0;       // Значение функции в вершине (x1, y1, z0)
            Real fx1y1z1;       // Значение функции в вершине (x1, y1, z1)
            
        public :
            
            // (1) Конструктор (обнуляет поля)
            Values3D();
            
            // (2) Конструктор копирования
            Values3D(const Values3D& values) = default;
            
            // (3) Перегрузка оператора присваивания
            Values3D& operator=(const Values3D& values) = default;
            
            // (4) Обнуляет поля
            void clear();
            
            // (5) Деструктор
            ~Values3D() = default;
    };
}

#endif