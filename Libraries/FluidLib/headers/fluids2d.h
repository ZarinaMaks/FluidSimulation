#ifndef FLUIDS2D_H
#define FLUIDS2D_H

////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "basic.h"
#include "components2d.h"
#include "tools2d.h"

namespace fluid
{
    ////////// struct BasicFluid2D ///////////////////////////////////////////
    // Структура содержит базовые величины и поля, которые требуются для    //
    // моделирования.                                                       //
    //////////////////////////////////////////////////////////////////////////
    
    struct BasicFluid2D
    {
        public :
            
            // Поле внешних сил
            VField2D force2D;
            
            // Поле скоростей
            VField2D speed2D;
            
            // Поле давления
            SField2D pressure2D;
            
            // Кинематическая вязкость
            Real viscosity;
            
            // Плотность
            Real density;
            
        public :
            
            // (1) Конструктор
            BasicFluid2D();
            
            // (2) Конструктор копирования
            BasicFluid2D(const BasicFluid2D& fluid) = default;
            
            // (3) Перегрузка оператора присваивания
            BasicFluid2D& operator=(const BasicFluid2D& fluid) = default;
            
            // (4) Деструктор
            ~BasicFluid2D() = default;
    };
    
    ////////// class BasicFluidModeler2D /////////////////////////////////////
    // Моделирует течение несжимаемой жидкости, используя инструменты       //
    // моделирования "BasicTools2D" и данные из структуры "BasicFields2D".  //
    //////////////////////////////////////////////////////////////////////////
    
    class BasicFluidModeler2D
    {
        private :
            
            // Временное скалярное поле 2D
            SField2D tempSF2D_;
            
            // Временное векторное поле 2D
            VField2D tempVF2D_;
            
            // Инструменты моделирования
            BasicTools2D* tools2D_;
            
            // Данные моделируемой жидкости
            BasicFluid2D* fluid2D_;
            
        public :
            
            // (1) Конструктор
            BasicFluidModeler2D();
            
            // (2) Конструктор копирования
            BasicFluidModeler2D(const BasicFluidModeler2D& modeler) = delete;
            
            // (3) Перегрузка оператора присваивания
            BasicFluidModeler2D& operator=(const BasicFluidModeler2D& 
                                           fluid) = delete;
            
            // (4) Инициализация всех полей
            void initialize(int sizeX, int sizeY, BasicTools2D& tools2D, 
                            BasicFluid2D& fluid2D);
            
            // (5) Производит переход в новое состояние, базируясь на текущем
            void compute();
            
            // (6) Установка значений по умолчанию
            void clear();
            
            // (7) Деструктор
            ~BasicFluidModeler2D() = default;
    };
    
    ////////// struct Fluid2D ////////////////////////////////////////////////
    // Хранит всю информацию о парамерах жидкости:                          //
    //                                                                      //
    // 1) BasicFields2D                                                     //
    //////////////////////////////////////////////////////////////////////////
    
    struct Fluid2D
    {
        public :
            
            // Базовые величины моделирования
            BasicFluid2D basic2D;
            
        public :
            
            // (1) Конструктор
            Fluid2D() = default;
            
            // (2) Конструктор копирования
            Fluid2D(const Fluid2D& fluid) = default;
            
            // (3) Перегрузка оператора присваивания
            Fluid2D& operator=(const Fluid2D& fluid) = default;
            
            // (4) Деструктор
            ~Fluid2D() = default;
    };
    
    ////////// class FluidModeler2D //////////////////////////////////////////
    // Моделирует течение жидкости. Вся информация, которая требуется для   //
    // моделирования, находится в структуре "Fluid2D".                      //
    //////////////////////////////////////////////////////////////////////////
    
    class FluidModeler2D
    {
        private :
            
            // Рассчет течения жидкости
            BasicFluidModeler2D basic2D_;
            
        public :
            
            // (1) Конструктор
            FluidModeler2D() = default;
            
            // (2) Конструктор копирования
            FluidModeler2D(const FluidModeler2D& modeler) = delete;
            
            // (3) Перегрузка оператора присваивания
            FluidModeler2D& operator=(const FluidModeler2D& modeler) = delete;
            
            // (4) Инициализация всех полей
            void initialize(int sizeX, int sizeY, BasicTools2D& tools2D,
                            Fluid2D& fluid2D);
            
            // (5) Производит переход в новое состояние, базируясь на текущем
            void compute();
            
            // (6) Установка значений по умолчанию
            void clear();
            
            // (7) Деструктор
            ~FluidModeler2D() = default;
    };
}

#endif