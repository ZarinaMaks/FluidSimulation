#ifndef FLUIDLIB2D_H
#define FLUIDLIB2D_H

////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "errlib.h"
#include "basiclib.h"
#include "componentlib2d.h"
#include "toolslib2d.h"

namespace fluid
{
    ////////// struct BasicFields2D //////////////////////////////////////////
    // Структура содержит базовые величины и поля, которые требуются для    //
    // моделирования.                                                       //
    //////////////////////////////////////////////////////////////////////////
    
    struct BasicFields2D
    {
        public :
            
            VField2D force2D;       // Поле внешних сил
            VField2D speed2D;       // Поле скоростей
            SField2D pressure2D;    // Поле давления
            Real     viscosity;     // Кинематическая вязкость
            Real     density;       // Плотность
            
        public :
            
            // (1) Конструктор
            BasicFields2D();
            
            // (2) Конструктор копирования
            BasicFields2D(const BasicFields2D& fields) = default;
            
            // (3) Перегрузка оператора присваивания
            BasicFields2D& operator=(const BasicFields2D& fields) = default;
            
            // (4) Деструктор
            ~BasicFields2D() = default;
    };
    
    ////////// class BasicFieldsModeler2D ////////////////////////////////////
    // Моделирует течение несжимаемой жидкости, используя инструменты       //
    // моделирования "BasicTools2D" и данные из структуры "BasicFields2D".  //
    //////////////////////////////////////////////////////////////////////////
    
    class BasicFieldsModeler2D
    {
        private :
            
            SField2D       tempSF2D_;   // Временное скалярное поле 2D
            VField2D       tempVF2D_;   // Временное векторное поле 2D
            BasicTools2D*  tools2D_;    // Инструменты моделирования
            BasicFields2D* fields2D_;   // Данные моделируемой жидкости
            
        public :
            
            ////////// Инициализация /////////////////////////////////////////
            
            // (1) Конструктор
            BasicFieldsModeler2D();
            
            // (2) Конструктор копирования
            BasicFieldsModeler2D(const BasicFieldsModeler2D& 
                                 modeler) = delete;
            
            // (3) Перегрузка оператора присваивания
            BasicFieldsModeler2D& operator=(const BasicFieldsModeler2D& 
                                            fields) = delete;
            
            // (4) Инициализация всех полей
            void initialize(int sizeX, int sizeY, BasicTools2D& tools2D, 
                            BasicFields2D& fields2D);
            
            ////////// Переход в новое состояние /////////////////////////////
            
            // (5) Производит переход в новое состояние, базируясь на текущем
            void compute();
            
            // (6) Установка значений по умолчанию
            void clear();
            
            // (7) Деструктор
            ~BasicFieldsModeler2D() = default;
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
            WallBorder2D*    wall2D_;       // Информация о границе
            Interpolation2D* interp2D_;     // Иструменты интерполирования
            
        public :
            
            ////////// Инициализация /////////////////////////////////////////
            
            // (1) Конструктор
            WallBorderModeler2D();
            
            // (2) Конструктор копирования
            WallBorderModeler2D(const WallBorderModeler2D& modeler) = delete;
            
            // (3) Перегрузка оператора присваивания
            WallBorderModeler2D& operator=(const WallBorderModeler2D& 
                                           modeler) = delete;
            
            // (4) Инициализация всех полей
            void initialize(BasicTools2D& tools2D, BasicFields2D& fields2D, 
                            WallBorder2D& border2D);
            
            ////////// Переход в новое состояние /////////////////////////////
            
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
            CavityBorder2D* cavity2D_;      // Информация о границе
            
        public :
            
            ////////// Инициализация /////////////////////////////////////////
            
            // (1) Конструктор
            CavityBorderModeler2D();
            
            // (2) Конструктор копирования
            CavityBorderModeler2D(const CavityBorderModeler2D& 
                                  modeler) = delete;
            
            // (3) Перегрузка оператора присваивания
            CavityBorderModeler2D& operator=(const CavityBorderModeler2D& 
                                             modeler) = delete;
            
            // (4) Инициализация всех полей
            void initialize(BasicFields2D& fields2D, 
                            CavityBorder2D& border2D);
            
            ////////// Переход в новое состояние /////////////////////////////
            
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
            
            Real             density_;      // Плотность жидкости, газа
            VField2D*        force2D_;      // Поле внешних сил
            GravityBorder2D* gravity2D_;    // Информация о границе
            
        public :
            
            ////////// Инициализация /////////////////////////////////////////
            
            // (1) Конструктор
            GravityBorderModeler2D();
            
            // (2) Конструктор копирования
            GravityBorderModeler2D(const GravityBorderModeler2D& 
                                   modeler) = delete;
            
            // (3) Перегрузка оператора присваивания
            GravityBorderModeler2D& operator=(const GravityBorderModeler2D& 
                                              modeler) = delete;
            
            // (4) Инициализация всех полей
            void initialize(BasicFields2D& fields2D, 
                            GravityBorder2D& border2D);
            
            ////////// Переход в новое состояние /////////////////////////////
            
            // (5) Производит переход в новое состояние, базируясь на текущем
            void compute();
            
            // (6) Установка значений по умолчанию
            void clear();
            
            // (7) Деструктор
            ~GravityBorderModeler2D() = default;
    };
}

#endif