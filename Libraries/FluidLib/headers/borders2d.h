#ifndef BORDERS2D_H
#define BORDERS2D_H

////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "basic.h"
#include "components2d.h"
#include "tools2d.h"
#include "fluids2d.h"

namespace fluid
{
    ////////// struct WallBorder2D ///////////////////////////////////////////
    // Структура содержит информацию для описания граничного условия        //
    // "твердая стенка". Отсутствие проскальзывания (нулевой) скорости и    //
    // чистые граничные условия давления Неймана.                           //
    //////////////////////////////////////////////////////////////////////////
    
    struct WallBorder2D
    {
        public :
            
            // Хранит векторы нормали к поверхности
            VField2D wall2D;
            
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
            
            // Абсцисса и ордината точки заимствования
            Real borrowX_;
            Real borrowY_;
            
            // Поле давлений и поле скоростей
            SField2D* pressure2D_;
            VField2D* speed2D_;
            
            // Информация о граничном условии
            WallBorder2D* wall2D_;
            
            // Иструменты решения задачи интерполяции
            Interpolation2D* interp2D_;
            
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
            
            // Хранит векторы нормали к границе области
            VField2D border2D;
            
            // Хранит давление на границе области
            SField2D pressure2D;
            
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
            
            // Абсцисса и ордината точки заимствования
            Real borrowX_;
            Real borrowY_;
            
            // Поле давлений и поле скоростей
            SField2D* pressure2D_;
            VField2D* speed2D_;
            
            // Информация о граничном условии
            CavityBorder2D* cavity2D_;
            
            // Иструменты решения задачи интерполяции
            Interpolation2D* interp2D_;
            
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
            void initialize(BasicTools2D& tools2D, BasicFluid2D& fluid2D, 
                            CavityBorder2D& border2D);
            
            // (5) Производит переход в новое состояние, базируясь на текущем
            void compute();
            
            // (6) Установка значений по умолчанию
            void clear();
            
            // (7) Деструктор
            ~CavityBorderModeler2D() = default;
        
        private :
            
            // (1) Находит координаты точки заимствования для (i, j) элемента
            void findBorrowDot(int i, int j);
            
            // (2) Рассчитывает скорость в (i, j) элементе
            void computeSpeed(int i, int j);
            
            // (3) Рассчитывает давление в (i, j) элементе
            void computePressure(int i, int j);
    };
    
    ////////// struct GravityBorder2D ////////////////////////////////////////
    // Структура содержит информацию для описания граничного условия        //
    // "имитация поля силы тяжести".                                        //
    //////////////////////////////////////////////////////////////////////////
    
    struct GravityBorder2D
    {
        public :
            
            // Проекции вектора ускорения своб-ого падения на "x" и "y"
            Real gX;
            Real gY;
            
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
            
            // Поле внешних сил
            VField2D* force2D_;
            
            // Информация о граничном условии
            GravityBorder2D* gravity2D_;
            
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
            
            // Поле скоростей точек стенки
            VField2D wallSpeed2D;
            
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
            
            // Поле скоростей жидкости
            VField2D* speed2D_;
            
            // Информация о граничном условии
            SpeedBorder2D* wallSpeed2D_;
            
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
            
            // Граничное условие: Твердая стенка
            WallBorder2D wall2D;
            
            // Граничное условие: Область повышенного/пониженного давления
            CavityBorder2D cavity2D;
            
            // Граничное условие: Поле силы тяжести
            GravityBorder2D gravity2D;
            
            // Граничное условие: Область постоянства скорости
            SpeedBorder2D speed2D;
            
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
            
            // Рассчет действия твердой стенки
            WallBorderModeler2D wall2D_;
            
            // Рассчет областей давления
            CavityBorderModeler2D cavity2D_;
            
            // Рассчет действия силы тяжести
            GravityBorderModeler2D gravity2D_;
            
            // Рассчет областей постоянства скорости
            SpeedBorderModeler2D speed2D_;
            
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
}

#endif