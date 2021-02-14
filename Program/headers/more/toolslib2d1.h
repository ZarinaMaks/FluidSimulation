#ifndef TOOLSLIB2D_H
#define TOOLSLIB2D_H

////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "errlib.h"
#include "basiclib.h"
#include "componentlib2d.h"

namespace fluid
{
    ////////// class Operator2D //////////////////////////////////////////////
    // Класс, предназначенный для отыскания частных производных,            //
    // градиентов, дивергенций скалярных и векторных полей в 2D. Все        //
    // операции производятся только в рабочей зоне "area2D_".               //
    //////////////////////////////////////////////////////////////////////////
    
    class Operator2D
    {
        private :
            
            ScalarField2D     tempSF2D_;    // Временное скалярное поле
            const WorkZone2D* area2D_;      // Область рассчетов
            
        public :
            
            ////////// Инициализация /////////////////////////////////////////
            
            // (1) Конструктор
            Operator2D();
            
            // (2) Конструктор копирования
            Operator2D(const Operator2D& newOperator) = delete;
            
            // (3) Перегрузка оператора присваивания
            Operator2D& operator=(const Operator2D& newOperator) = delete;
            
            // (4) Инициализация вспомогательных 2D полей
            void initialize(const WorkZone2D& area2D);
            
            ////////// Градиент и дивергенция ////////////////////////////////
            
            // (5) Градиент (Меняет по ссылке векторное поле)
            void grad(const ScalarField2D& inField, VectorField2D& outField);
            
            // (6) Дивергенция (Меняет по ссылке скалярное поле)
            void div(const VectorField2D& inField, ScalarField2D& outField);
            
            ////////// Частные производные всюду /////////////////////////////
            
            // (7) Частная производная функции по "x" всюду
            void derX(const ScalarField2D& inField, ScalarField2D& outField);
            
            // (8) Частная производная функции по "y" всюду
            void derY(const ScalarField2D& inField, ScalarField2D& outField);
            
            ////////// Арифметика с полями ///////////////////////////////////
            
            // (9) Добавляет поэлементно поле "field2" к полю "field1"
            void add(ScalarField2D& field1, const ScalarField2D& field2);
            
            // (10) Добавляет поэлементно поле "field2" к полю "field1"
            void add(VectorField2D& field1, const VectorField2D& field2);
            
            // (11) Вычитает поэлементно поле "field2" из поля "field1"
            void sub(ScalarField2D& field1, const ScalarField2D& field2);
            
            // (12) Вычитает поэлементно поле "field2" из поля "field1"
            void sub(VectorField2D& field1, const VectorField2D& field2);
            
            // (13) Присваивает поэлементно поле "field2" полю "field1"
            void assign(ScalarField2D& field1, const ScalarField2D& field2);
            
            // (14) Присваивает поэлементно поле "field2" полю "field1"
            void assign(VectorField2D& field1, const VectorField2D& field2);
            
            ////////// Освобождение памяти ///////////////////////////////////
            
            // (15) Освобождает выделенную память
            void clear();
            
            // (16) Деструктор
            ~Operator2D() = default;
            
        private :
            
            ////////// Частные производные в точке ///////////////////////////
            
            // (1) Частная производная функции по "x" в (x, y)
            Real derX(const ScalarField2D& inField, int x, int y);
            
            // (2) Частная производная функции по "y"  в (x, y)
            Real derY(const ScalarField2D& inField, int x, int y);
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
            
            ScalarField2D     tempSF2D_;    // Временное скалярное поле 2D
            Operator2D*       operator2D_;  // Вспомогательные инструменты
            const WorkZone2D* area2D_;      // Область рассчетов
            
        public :
            
            ////////// Инициализация /////////////////////////////////////////
            
            // (1) Конструктор
            Poisson2D();
            
            // (2) Конструктор копирования
            Poisson2D(const Poisson2D& newPoisson) = delete;
            
            // (3) Перегрузка оператора присваивания
            Poisson2D& operator=(const Poisson2D& newPoisson) = delete;
            
            // (4) Инициализация вспомогательных полей
            void initialize(const WorkZone2D& area2D, Operator2D& operator2D);
            
            ////////// Решение ур-я Пуассона методом итераций ////////////////
            
            // (5) Решает уравнение Пуассона
            void solve(ScalarField2D& field, const ScalarField2D& free, 
                       Real alpha, Real betta);
            
            // (6) Решает уравнение Пуассона
            void solve(VectorField2D& field, const VectorField2D& free,
                       Real alpha, Real betta);
            
            ////////// Освобождение памяти ///////////////////////////////////
            
            // (7) Освобождает выделенную память
            void clear();
            
            // (8) Деструктор
            ~Poisson2D() = default;
            
        private :
            
            ////////// Производит одиночный переход в новое состояние ////////
            
            // (1) Возвращает очередное приближение в точке (i, j)
            Real step(const ScalarField2D& field, const ScalarField2D& free, 
                      Real alpha, Real betta, int i, int j);
            
            // (2) Возвращает очередное приближение на всем поле
            void step(ScalarField2D& field, const ScalarField2D& free, 
                      Real alpha, Real betta);
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
            
            ////////// Вычисление приближенного значения /////////////////////
            
            // (4) Вычисляет приближенное значение в (x, y) на поле
            Real compute(const ScalarField2D& field, Real x, Real y);
            
            ////////// Обнуление /////////////////////////////////////////////
            
            // (5) Обнуляет поля
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
    // 2D пространстве. Все вычисления производятся только в рабочей зоне   //
    // "area2D_".                                                           //
    //                                                                      //
    // 1) basic     - поле, задающее направления переноса величин (поле     //
    //    скоростей).                                                       //
    // 2) viscosity - кинематическая вязкость.                              //
    // 3) density   - плотность жидкости или газа.                          //
    //////////////////////////////////////////////////////////////////////////
    
    class ModelTools2D
    {
        private :
            
            ScalarField2D     tempSF2D_;    // Временное скалярное поле 2D
            VectorField2D     tempVF2D_;    // Временное векторное поле 2D
            Operator2D*       operator2D_;  // Вспомогательные инструменты
            Poisson2D*        poisson2D_;   // Решение ур-ий Пуассона
            Interpolation2D*  interp2D_;    // Билинейная интерполяция
            const WorkZone2D* area2D_;      // Область рассчетов
            
        public :
            
            ////////// Инициализация /////////////////////////////////////////
            
            // (1) Конструктор
            ModelTools2D();
            
            // (2) Конструктор копирования
            ModelTools2D(const ModelTools2D& newTools) = delete;
            
            // (3) Перегрузка оператора присваивания
            ModelTools2D& operator=(const ModelTools2D& newTools) = delete;
            
            // (4) Инициализация вспомогательных полей
            void initialize(const WorkZone2D& area2D, 
                            Operator2D& operator2D, 
                            Poisson2D& poisson2D, 
                            Interpolation2D& interp2D);
            
            ////////// Адвекция //////////////////////////////////////////////
            
            // (5) Вычисляет, как поле "basic" переносит значения "field"
            void advection(ScalarField2D& field, const VectorField2D& basic);
            
            // (6) Вычисляет, как поле "basic" переносит значения "field"
            void advection(VectorField2D& field, const VectorField2D& basic);
            
            ////////// Вязкая диффузия ///////////////////////////////////////
            
            // (7) Рассчет вязкой диффузии для скалярного поля
            void diffusion(ScalarField2D& field, Real viscosity);
            
            // (8) Рассчет вязкой диффузии для векторного поля
            void diffusion(VectorField2D& field, Real viscosity);
            
            ////////// Действие сил //////////////////////////////////////////
            
            // (9) Рассчет действия поля сил "force" на поле "field"
            void forceImpact(VectorField2D& field, 
                             const VectorField2D& force, Real density);
            
            ////////// Освобождение памяти ///////////////////////////////////
            
            // (10) Освобождает выделенную память
            void clear();
            
            // (11) Деструктор
            ~ModelTools2D() = default;
            
        private :
            
            // (1) Рассчет действия компоненты поля сил
            void forceImpact(ScalarField2D& field, 
                             const ScalarField2D& force, Real density);
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
            void initialize(const WorkZone2D& area2D);
            
            ////////// Доступ к инструментам /////////////////////////////////
            
            // (5) Доступ к всевозможным операторам
            Operator2D& operation();
            
            // (6) Доступ к методам решения уравнения Пуассона
            Poisson2D& poisson();
            
            // (7) Доступ к методам билинейной интерполяции
            Interpolation2D& interpolation();
            
            // (8) Доступ к инструментам моделирования
            ModelTools2D& modeling();
            
            ////////// Освобождение памяти ///////////////////////////////////
            
            // (9) Освобождает выделенную память
            void clear();
            
            // (10) Деструктор
            ~BasicTools2D() = default;
    };
}

#endif