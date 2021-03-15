#ifndef FLUIDLIB2D_H
#define FLUIDLIB2D_H

////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "exception.h"
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
            
            VField2D force2D;       // Поле внешних сил
            VField2D speed2D;       // Поле скоростей
            SField2D pressure2D;    // Поле давления
            Real     viscosity;     // Кинематическая вязкость
            Real     density;       // Плотность
            
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
            
            SField2D       tempSF2D_;   // Временное скалярное поле 2D
            VField2D       tempVF2D_;   // Временное векторное поле 2D
            BasicTools2D*  tools2D_;    // Инструменты моделирования
            BasicFluid2D*  fluid2D_;    // Данные моделируемой жидкости
            
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
    
    ////////// struct WallBorder2D ///////////////////////////////////////////
    // Структура содержит информацию для описания граничного условия        //
    // "твердая стенка". Отсутствие проскальзывания (нулевой) скорости и    //
    // чистые граничные условия давления Неймана.                           //
    //////////////////////////////////////////////////////////////////////////
    
    struct WallBorder2D
    {
        public :
            
            VField2D wall2D;    // Хранит векторы нормали к поверхности
            
        public :
            
            // (1) Конструктор
            WallBorder2D() = default;
            
            // (2) Конструктор копирования
            WallBorder2D(const WallBorder2D& border) = default;
            
            // (3) Перегрузка оператора присваивания
            WallBorder2D& operator=(const WallBorder2D& border) = default;
            
            // (4) Деструктор
            ~WallBorder2D() = default;
    };
    
    ////////// class WallBorderModeler2D /////////////////////////////////////
    // Моделирует граничные условия, данные о которых находятся в структуре //
    // "WallBorder2D" с использованием инструментов "BasicTools2D".         //
    //////////////////////////////////////////////////////////////////////////
    
    class WallBorderModeler2D
    {
        private :
            
            Real             borrowX_;      // Абсцисса точки заимствования
            Real             borrowY_;      // Ордината точки заимствования
            SField2D*        pressure2D_;   // Поле давлений
            VField2D*        speed2D_;      // Поле скоростей
            WallBorder2D*    wall2D_;       // Информация о гр. условии
            Interpolation2D* interp2D_;     // Иструменты интерполирования
            
        public :
            
            // (1) Конструктор
            WallBorderModeler2D();
            
            // (2) Конструктор копирования
            WallBorderModeler2D(const WallBorderModeler2D& modeler) = delete;
            
            // (3) Перегрузка оператора присваивания
            WallBorderModeler2D& operator=(const WallBorderModeler2D& 
                                           modeler) = delete;
            
            // (4) Инициализация всех полей
            void initialize(BasicTools2D& tools2D, BasicFluid2D& fluid2D, 
                            WallBorder2D& border2D);
            
            // (5) Производит переход в новое состояние, базируясь на текущем
            void compute();
            
            // (6) Установка значений по умолчанию
            void clear();
            
            // (7) Деструктор
            ~WallBorderModeler2D() = default;
            
        private :
            
            // (1) Находит координаты точки заимствования для (i, j) элемента
            void findBorrowDot(int i, int j);
            
            // (2) Рассчитывает скорость в (i, j) элементе
            void computeSpeed(int i, int j);
            
            // (3) Рассчитывает давление в (i, j) элементе
            void computePressure(int i, int j);
    };
    
    ////////// struct CavityBorder2D /////////////////////////////////////////
    // Структура содержит информацию для описания граничного условия        //
    // "отсутствие преграды".                                               //
    //////////////////////////////////////////////////////////////////////////
    
    struct CavityBorder2D
    {
        public :
            
            SField2D cavity2D;  // Хранит давления свободных областей
            
        public :
            
            // (1) Конструктор
            CavityBorder2D() = default;
            
            // (2) Конструктор копирования
            CavityBorder2D(const CavityBorder2D& border) = default;
            
            // (3) Перегрузка оператора присваивания
            CavityBorder2D& operator=(const CavityBorder2D& border) = default;
            
            // (4) Деструктор
            ~CavityBorder2D() = default;
    };
    
    ////////// class CavityBorderModeler2D ///////////////////////////////////
    // Моделирует граничные условия, данные о которых находятся в структуре //
    // "CavityBorder2D".                                                    //
    //////////////////////////////////////////////////////////////////////////
    
    class CavityBorderModeler2D
    {
        private :
            
            SField2D*       pressure2D_;    // Поле давлений
            VField2D*       speed2D_;       // Поле скоростей
            CavityBorder2D* cavity2D_;      // Информация о гр. условии
            
        public :
            
            // (1) Конструктор
            CavityBorderModeler2D();
            
            // (2) Конструктор копирования
            CavityBorderModeler2D(const CavityBorderModeler2D& 
                                  modeler) = delete;
            
            // (3) Перегрузка оператора присваивания
            CavityBorderModeler2D& operator=(const CavityBorderModeler2D& 
                                             modeler) = delete;
            
            // (4) Инициализация всех полей
            void initialize(BasicFluid2D& fluid2D, CavityBorder2D& border2D);
            
            // (5) Производит переход в новое состояние, базируясь на текущем
            void compute();
            
            // (6) Установка значений по умолчанию
            void clear();
            
            // (7) Деструктор
            ~CavityBorderModeler2D() = default;
    };
    
    ////////// struct GravityBorder2D ////////////////////////////////////////
    // Структура содержит информацию для описания граничного условия        //
    // "имитация поля силы тяжести".                                        //
    //////////////////////////////////////////////////////////////////////////
    
    struct GravityBorder2D
    {
        public :
            
            Real gX;    // Проекция вектора ускорения св. падения на "x"
            Real gY;    // Проекция вектора ускорения св. падения на "y"
            
        public :
            
            // (1) Конструктор
            GravityBorder2D();
            
            // (2) Конструктор копирования
            GravityBorder2D(const GravityBorder2D& border) = default;
            
            // (3) Перегрузка оператора присваивания
            GravityBorder2D& operator=(const GravityBorder2D& 
                                       border) = default;
            
            // (4) Деструктор
            ~GravityBorder2D() = default;
    };
    
    ////////// class GravityBorderModeler2D //////////////////////////////////
    // Моделирует граничные условия, данные о которых находятся в структуре //
    // "GravityBorder2D".                                                   //
    //////////////////////////////////////////////////////////////////////////
    
    class GravityBorderModeler2D
    {
        private :
            
            VField2D*        force2D_;      // Поле внешних сил
            GravityBorder2D* gravity2D_;    // Информация о гр-ом условии
            
        public :
            
            // (1) Конструктор
            GravityBorderModeler2D();
            
            // (2) Конструктор копирования
            GravityBorderModeler2D(const GravityBorderModeler2D& 
                                   modeler) = delete;
            
            // (3) Перегрузка оператора присваивания
            GravityBorderModeler2D& operator=(const GravityBorderModeler2D& 
                                              modeler) = delete;
            
            // (4) Инициализация всех полей
            void initialize(BasicFluid2D& fluid2D, GravityBorder2D& border2D);
            
            // (5) Производит переход в новое состояние, базируясь на текущем
            void compute();
            
            // (6) Установка значений по умолчанию
            void clear();
            
            // (7) Деструктор
            ~GravityBorderModeler2D() = default;
    };
    
    ////////// struct SpeedBorder2D //////////////////////////////////////////
    // Структура содержит информацию для описания граничного условия        //
    // "скользящая стенка".                                                 //
    // Хранит информацию о скоростях точек стенки (скорости должны быть     //
    // направлены по касательной к стенке). Применяется в паре с граничным  //
    // условием "твердая стенка" (WallBorder2D) и обрабатывается после      //
    // него.                                                                //
    //////////////////////////////////////////////////////////////////////////
    
    struct SpeedBorder2D
    {
        public :
            
            VField2D wallSpeed2D;   // Поле скоростей точек стенки
            
        public :
            
            // (1) Конструктор
            SpeedBorder2D() = default;
            
            // (2) Конструктор копирования
            SpeedBorder2D(const SpeedBorder2D& border) = default;
            
            // (3) Перегрузка оператора присваивания
            SpeedBorder2D& operator=(const SpeedBorder2D& border) = default;
            
            // (4) Деструктор
            ~SpeedBorder2D() = default;
    };
    
    ////////// class SpeedBorderModeler2D ////////////////////////////////////
    // Моделирует граничные условия, данные о которых находятся в структуре //
    // "SpeedBorder2D".                                                     //
    //////////////////////////////////////////////////////////////////////////
    
    class SpeedBorderModeler2D
    {
        private :
            
            VField2D*      speed2D_;        // Поле скоростей жидкости
            SpeedBorder2D* wallSpeed2D_;    // Информация о гр-ом условии
            
        public :
            
            // (1) Конструктор
            SpeedBorderModeler2D();
            
            // (2) Конструктор копирования
            SpeedBorderModeler2D(const SpeedBorderModeler2D& 
                                 modeler) = delete;
            
            // (3) Перегрузка оператора присваивания
            SpeedBorderModeler2D& operator=(const SpeedBorderModeler2D& 
                                            modeler) = delete;
            
            // (4) Инициализация всех полей
            void initialize(BasicFluid2D& fluid2D, SpeedBorder2D& border2D);
            
            // (5) Производит переход в новое состояние, базируясь на текущем
            void compute();
            
            // (6) Установка значений по умолчанию
            void clear();
            
            // (7) Деструктор
            ~SpeedBorderModeler2D() = default;
    };
    
    ////////// struct Fluid2D ////////////////////////////////////////////////
    // Хранит всю информацию о парамерах жидкости:                          //
    //                                                                      //
    // 1) BasicFields2D                                                     //
    //////////////////////////////////////////////////////////////////////////
    
    struct Fluid2D
    {
        public :
            
            BasicFluid2D basic2D;   // Базовые величины моделирования
            
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
            
            BasicFluidModeler2D basic2D_;   // Рассчет течения жидкости
            
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
    
    ////////// struct Border2D ///////////////////////////////////////////////
    // Хранит всю информацию для моделирования граничных условий течения    //
    // жидкости:                                                            //
    //                                                                      //
    // 1) WallBorder2D                                                      //
    // 2) CavityBorder2D                                                    //
    // 3) GravityBorder2D                                                   //
    // 4) SpeedBorder2D                                                     //
    //////////////////////////////////////////////////////////////////////////
    
    struct Border2D
    {
        public :
            
            WallBorder2D    wall2D;     // Твердая стенка
            CavityBorder2D  cavity2D;   // Область повыш./пониж. давления
            GravityBorder2D gravity2D;  // Поле силы тяжести
            SpeedBorder2D   speed2D;    // Область постоянства скорости
            
        public :
            
            // (1) Конструктор
            Border2D() = default;
            
            // (2) Конструктор копирования
            Border2D(const Border2D& border) = default;
            
            // (3) Перегрузка оператора присваивания
            Border2D& operator=(const Border2D& border) = default;
            
            // (4) Деструктор
            ~Border2D() = default;
    };
    
    ////////// class BorderModeler2D /////////////////////////////////////////
    // Моделирует все граничные условия. Информация, которая требуется для  //
    // моделирования, находится в структуре "Border2D".                     //
    //////////////////////////////////////////////////////////////////////////
    
    class BorderModeler2D
    {
        private :
            
            WallBorderModeler2D    wall2D_;     // Рассчет твердой стенки
            CavityBorderModeler2D  cavity2D_;   // Рассчет обл-ей давления
            GravityBorderModeler2D gravity2D_;  // Рассчет поля силы тяжести
            SpeedBorderModeler2D   speed2D_;    // Рассчет обл-ей скорости
            
        public :
            
            // (1) Конструктор
            BorderModeler2D() = default;
            
            // (2) Конструктор копирования
            BorderModeler2D(const BorderModeler2D& modeler) = delete;
            
            // (3) Перегрузка оператора присваивания
            BorderModeler2D& operator=(const BorderModeler2D& 
                                       modeler) = delete;
            
            // (4) Инициализация всех полей
            void initialize(BasicTools2D& tools2D, Fluid2D& fluid2D, 
                            Border2D& border2D);
            
            // (5) Производит переход в новое состояние, базируясь на текущем
            void compute();
            
            // (6) Установка значений по умолчанию
            void clear();
            
            // (7) Деструктор
            ~BorderModeler2D() = default;
    };
    
    ////////// struct Model2D ////////////////////////////////////////////////
    // Хранит всю информацию для моделирования течения жидкости или газа в  //
    // определенной системе с граничными условиями. Включает:               //
    //                                                                      //
    // 1) Fluid2D  : параметры, связанные с жидкостью.                      //
    // 2) Border2D : параметры граничных условий.                           //
    //////////////////////////////////////////////////////////////////////////
    
    struct Model2D
    {
        public :
            
            Fluid2D  fluid2D;   // Все параметры течения
            Border2D border2D;  // Все граничные условия
            
        public :
            
            // (1) Конструктор
            Model2D() = default;
            
            // (2) Конструктор копирования
            Model2D(const Model2D& model) = default;
            
            // (3) Перегрузка оператора присваивания
            Model2D& operator=(const Model2D& model) = default;
            
            // (4) Деструктор
            ~Model2D() = default;
    };
    
    ////////// class Modeler2D ///////////////////////////////////////////////
    // Моделирует течение жидкости в определенной системе, которая          //
    // описывается структурой "Model2D". Включает:                          //
    //                                                                      //
    // 1) BasicTools2D    : Базовые инструменты моделирования.              //
    // 2) FluidModeler2D  : Моделирует течение жидкости.                    //
    // 3) BorderModeler2D : Моделирует граничные условия.                   //
    //////////////////////////////////////////////////////////////////////////
    
    class Modeler2D
    {
        private :
            
            BasicTools2D    tools2D_;   // Набор базовых инструментов
            FluidModeler2D  fluid2D_;   // Рассчитывает течение жидкости
            BorderModeler2D border2D_;  // Рассчитывает граничные условия
            
        public :
            
            // (1) Конструктор
            Modeler2D() = default;
            
            // (2) Конструктор копирования
            Modeler2D(const Modeler2D& modeler) = delete;
            
            // (3) Перегрузка оператора присваивания
            Modeler2D& operator=(const Modeler2D& modeler) = delete;
            
            // (4) Инициализация всех полей
            void initialize(int sizeX, int sizeY, Model2D& model2D);
            
            // (5) Производит переход в новое состояние, базируясь на текущем
            void compute();
            
            // (6) Установка значений по умолчанию
            void clear();
            
            // (7) Деструктор
            ~Modeler2D() = default;
    };
}

#endif