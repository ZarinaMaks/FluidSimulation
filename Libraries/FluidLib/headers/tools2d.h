#ifndef TOOLS2D_H
#define TOOLS2D_H

////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "exception.h"
#include "basic.h"
#include "components2d.h"

namespace fluid
{
    ////////// class Operator2D //////////////////////////////////////////////
    // Класс, предназначенный для отыскания частных производных,            //
    // градиентов, дивергенций скалярных и векторных полей в 2D. Все        //
    // операции производятся только в области задания поля.                 //
    //////////////////////////////////////////////////////////////////////////
    
    class Operator2D
    {
        private :
            
            SField2D tempSF2D_;     // Временное скалярное поле
            
        public :
            
            ////////// Инициализация /////////////////////////////////////////
            
            // (1) Конструктор
            Operator2D() = default;
            
            // (2) Конструктор копирования
            Operator2D(const Operator2D& newOperator) = delete;
            
            // (3) Перегрузка оператора присваивания
            Operator2D& operator=(const Operator2D& newOperator) = delete;
            
            // (4) Инициализация вспомогательного 2D поля
            void initialize(int sizeX, int sizeY);
            
            ////////// Градиент и дивергенция ////////////////////////////////
            
            // (5) Градиент поля "field1" (результат : "field2")
            void grad(const SField2D& field1, VField2D& field2);
            
            // (6) Дивергенция поля "field1" (результат : "field2")
            void div(const VField2D& field1, SField2D& field2);
            
            ////////// Частные производные всюду /////////////////////////////
            
            // (7) Частная пр-ая "field1" по "x" всюду (результат : "field2")
            void derX(const SField2D& field1, SField2D& field2);
            
            // (8) Частная пр-ая "field1" по "y" всюду (результат : "field2")
            void derY(const SField2D& field1, SField2D& field2);
            
            ////////// Арифметика с полями ///////////////////////////////////
            
            // (9) Добавляет поэлементно поле "field2" к полю "field1"
            void add(SField2D& field1, const SField2D& field2);
            
            // (10) Добавляет поэлементно поле "field2" к полю "field1"
            void add(VField2D& field1, const VField2D& field2);
            
            // (11) Вычитает поэлементно поле "field2" из поля "field1"
            void sub(SField2D& field1, const SField2D& field2);
            
            // (12) Вычитает поэлементно поле "field2" из поля "field1"
            void sub(VField2D& field1, const VField2D& field2);
            
            // (13) Присваивает поэлементно поле "field2" полю "field1"
            void assign(SField2D& field1, const SField2D& field2);
            
            // (14) Присваивает поэлементно поле "field2" полю "field1"
            void assign(VField2D& field1, const VField2D& field2);
            
            ////////// Арифметика со скалярами ///////////////////////////////
            
            // (15) Домножает все элементы скалярного поля на скаляр
            void mul(SField2D& field1, Real multiplier);
            
            // (16) Домножает все элементы векторного поля на скаляр
            void mul(VField2D& field1, Real multiplier);
            
            // (17) Установка значений по умолчанию
            void clear();
            
            // (18) Деструктор
            ~Operator2D() = default;
            
        private :
            
            // (1) Частная пр-ая "field" по "x" в (x, y)
            Real derX(const SField2D& field, int x, int y);
            
            // (2) Частная пр-ая "field" по "y" в (x, y)
            Real derY(const SField2D& field, int x, int y);
    };
    
    ////////// class Poisson2D ///////////////////////////////////////////////
    // Позволяет решать уравнение Пуассона для 2D векторных и скалярных     //
    // полей методом итераций Якоби.                                        //
    //                                                                      //
    // 1) alpha, betta - коэффициенты (см. теорию).                         //
    // 2) free         - поле свободных членов уравнения.                   //
    //////////////////////////////////////////////////////////////////////////
    
    class Poisson2D
    {
        private :
            
            SField2D    tempSF2D_;      // Временное скалярное поле 2D
            Operator2D* operator2D_;    // Вспомогательные инструменты
            
        public :
            
            ////////// Инициализация /////////////////////////////////////////
            
            // (1) Конструктор
            Poisson2D();
            
            // (2) Конструктор копирования
            Poisson2D(const Poisson2D& newPoisson) = delete;
            
            // (3) Перегрузка оператора присваивания
            Poisson2D& operator=(const Poisson2D& newPoisson) = delete;
            
            // (4) Инициализация вспомогательных полей
            void initialize(int sizeX, int sizeY, Operator2D& operator2D);
            
            ////////// Реш-е ур-я Пуассона методом итераций Якоби ////////////
            
            // (5) Решает уравнение Пуассона для скалярного поля
            void solve(SField2D& field, const SField2D& free, Real alpha, 
                       Real betta);
            
            // (6) Решает уравнение Пуассона для векторного поля
            void solve(VField2D& field, const VField2D& free, Real alpha, 
                       Real betta);
            
            // (7) Установка значений по умолчанию
            void clear();
            
            // (8) Деструктор
            ~Poisson2D() = default;
            
        private :
            
            // (1) Возвращает очередное приближение в точке (i, j)
            Real step(const SField2D& field, const SField2D& free, 
                      Real alpha, Real betta, int i, int j);
            
            // (2) Возвращает очередное приближение на всем поле
            void step(SField2D& field, const SField2D& free, Real alpha, 
                      Real betta);
    };
    
    ////////// class Interpolation2D /////////////////////////////////////////
    // Предоставляет методы для вычисления значения величины в произвольной //
    // (не узловой) точке на скалярном 2D поле. В данном случае             //
    // используется метод билинейной интерполяции.                          //
    //////////////////////////////////////////////////////////////////////////
    
    class Interpolation2D
    {
        private :
            
            Values2D values2D_;         // Набор значений на прямоуг-ке
            Real     a0_;               // Вспомогательный коэффициент
            Real     a1_;               // -//-
            Real     a2_;               // -//-
            Real     a3_;               // -//-
            
        public :
            
            ////////// Инициализация /////////////////////////////////////////
            
            // (1) Конструктор
            Interpolation2D();
            
            // (2) Конструктор копирования
            Interpolation2D(const Interpolation2D& newInterp) = delete;
            
            // (3) Перегрузка оператора присваивания
            Interpolation2D& operator=(const Interpolation2D& 
                                       newInterp) = delete;
            
            ////////// Билинейная интерполяция ///////////////////////////////
            
            // (4) Вычисляет приближенное значение в (x, y) на поле
            Real compute(const SField2D& field, Real x, Real y);
            
            // (5) Установка значений по умолчанию
            void clear();
            
            // (6) Деструктор
            ~Interpolation2D() = default;
            
        private :
            
            // (1) Вычисляет значение в (x, y) используя "Values2D"
            Real compute(Real x, Real y);
    };
    
    ////////// class ModelTools2D ////////////////////////////////////////////
    // Класс предоставляет инструменты для вычисления всех величин,         //
    // используемых в уравнениях Навье-Стокса в очередной момент времени в  //
    // 2D пространстве. Все вычисления производятся только в областях       //
    // задания.                                                             //
    //                                                                      //
    // 1) basic     - поле, задающее направления переноса величин (поле     //
    //    скоростей).                                                       //
    // 2) viscosity - кинематическая вязкость.                              //
    // 3) density   - плотность жидкости или газа.                          //
    //////////////////////////////////////////////////////////////////////////
    
    class ModelTools2D
    {
        private :
            
            SField2D         tempSF2D_;     // Временное скалярное поле 2D
            VField2D         tempVF2D_;     // Временное векторное поле 2D
            Operator2D*      operator2D_;   // Вспомогательные инструменты
            Poisson2D*       poisson2D_;    // Решение ур-ий Пуассона
            Interpolation2D* interp2D_;     // Билинейная интерполяция
            
        public :
            
            ////////// Инициализация /////////////////////////////////////////
            
            // (1) Конструктор
            ModelTools2D();
            
            // (2) Конструктор копирования
            ModelTools2D(const ModelTools2D& newTools) = delete;
            
            // (3) Перегрузка оператора присваивания
            ModelTools2D& operator=(const ModelTools2D& newTools) = delete;
            
            // (4) Инициализация вспомогательных полей
            void initialize(int sizeX, int sizeY,  Operator2D& operator2D, 
                            Poisson2D& poisson2D, Interpolation2D& interp2D);
            
            ////////// Адвекция //////////////////////////////////////////////
            
            // (5) Вычисляет, как поле "basic" переносит значения "field"
            void advection(SField2D& field, const VField2D& basic);
            
            // (6) Вычисляет, как поле "basic" переносит значения "field"
            void advection(VField2D& field, const VField2D& basic);
            
            ////////// Вязкая диффузия ///////////////////////////////////////
            
            // (7) Рассчет вязкой диффузии для скалярного поля
            void diffusion(SField2D& field, Real viscosity);
            
            // (8) Рассчет вязкой диффузии для векторного поля
            void diffusion(VField2D& field, Real viscosity);
            
            ////////// Действие сил //////////////////////////////////////////
            
            // (9) Рассчет действия поля сил "field2" на поле "field1"
            void force(VField2D& field1, const VField2D& field2);
            
            // (10) Установка значений по умолчанию
            void clear();
            
            // (11) Деструктор
            ~ModelTools2D() = default;
            
        private :
            
            // (1) Рассчет действия компоненты поля сил
            void force(SField2D& field1, const SField2D& field2);
    };
    
    ////////// class BasicTools2D ////////////////////////////////////////////
    // Класс предоставляет для работы с полями все фундаментальные          //
    // инструменты:                                                         //
    //                                                                      //
    // 1) Operator2D                                                        //
    // 2) Poisson2D                                                         //
    // 3) Interpolation2D                                                   //
    // 4) ModelTools2D                                                      //
    //////////////////////////////////////////////////////////////////////////
    
    class BasicTools2D
    {
        private :
            
            Operator2D      operator2D_;    // Вспомогательные инструменты
            Poisson2D       poisson2D_;     // Решение ур-ия Пуассона
            Interpolation2D interp2D_;      // Билинейная интерполяция
            ModelTools2D    tools2D_;       // Инструменты моделирования
            
        public :
            
            ////////// Инициализация /////////////////////////////////////////
            
            // (1) Конструктор
            BasicTools2D() = default;
            
            // (2) Конструктор копирования
            BasicTools2D(const BasicTools2D& newTools) = delete;
            
            // (3) Перегрузка оператора присваивания
            BasicTools2D& operator=(const BasicTools2D& newTools) = delete;
            
            // (4) Инициализация всех инструментов
            void initialize(int sizeX, int sizeY);
            
            ////////// Доступ к инструментам /////////////////////////////////
            
            // (5) Доступ к всевозможным операторам
            Operator2D& operation();
            
            // (6) Доступ к методам решения уравнения Пуассона
            Poisson2D& poisson();
            
            // (7) Доступ к методам билинейной интерполяции
            Interpolation2D& interp();
            
            // (8) Доступ к инструментам моделирования
            ModelTools2D& model();
            
            // (9) Установка значений по умолчанию
            void clear();
            
            // (10) Деструктор
            ~BasicTools2D() = default;
    };
}

#endif