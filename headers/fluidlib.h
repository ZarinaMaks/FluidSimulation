#ifndef FLUIDLIB_H
#define FLUIDLIB_H

////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <cstdlib>

namespace fluid
{
    // Универсальный вещественный тип
    typedef double real;
    
    ////////// class VectorField /////////////////////////////////////////////
    // Класс - векторное поле, содержит трехмерный массив векторов          //
    // "Vector"...                                                          //
    //////////////////////////////////////////////////////////////////////////
    
    class VectorField
    {
        private :
            
            Vector*** vectors_;     // Трехверный массив трехмерных векторов
            int       sizeX_;       // Кол-во элементов поля по компоненте "x"
            int       sizeY_;       // Кол-во элементов поля по компоненте "y"
            int       sizeZ_;       // Кол-во элементов поля по компоненте "z"
        
        public :
            
            // (1) Конструктор
            VectorField();
            
            // (2) Конструктор копирования
            VectorField(const VectorField& field);
            
            // (3) Перегрузка оператора присваивания
            VectorField& operator=(const VectorField& field);
            
            // (4) 
            const Vector& get(int& i, int& j, int& k) const;
            
            // (5) 
            Vector& get(int& i, int& j, int& k);
            
            // (6) Освобождает выделенную память
            void clear();
            
            // (7) Деструктор
            ~VectorField();
            
            //TODO: add more methods
    };
    
    ////////// class ScalarField /////////////////////////////////////////////
    // Класс - поле скаляров, содержит трехмерный массив скаляров типа      //
    // "real"...                                                            //
    //////////////////////////////////////////////////////////////////////////
    
    class ScalarField
    {
        private :
            
            real*** scalars_;       // Трехмерный массив скаляров
            int     sizeX_;         // Кол-во элементов поля по компоненте "x"
            int     sizeY_;         // Кол-во элементов поля по компоненте "y"
            int     sizeZ_;         // Кол-во элементов поля по компоненте "z"
    
        public :
            
            // (1) Конструктор
            ScalarField();
            
            // (3) Конструктор копирования
            ScalarField(const ScalarField& field);
            
            // (3) Перегрузка оператора присваивания
            VectorField& operator=(const VectorField& field);
            
            // (4)
            const real& get(int& i, int& j, int& k) const;
            
            // (5)
            real& get(int& i, int& j, int& k);
            
            // (6) Освобождает выделенную память
            void clear();
            
            // (7) Деструктор
            ~ScalarField();
            
            //TODO: add more methods
    };
}

#endif