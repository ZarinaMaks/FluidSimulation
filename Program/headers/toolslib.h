#ifndef TOOLSLIB_H
#define TOOLSLIB_H

////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "errlib.h"
#include "basiclib.h"
#include "componentlib2d.h"
#include "componentlib3d.h"

namespace fluid
{
    ////////// class Operator ////////////////////////////////////////////////
    // Класс, предназначенный для отыскания частных производных,            //
    // градиентов, дивергенций скалярных и векторных полей.                 //
    //////////////////////////////////////////////////////////////////////////
    
    class Operator
    {
        private :
            
            ScalarField2D tempSF2D_;    // Временное скалярное поле 2D
            ScalarField3D tempSF3D_;    // Временное скалярное поле 3D
            
        public :
            
            // (1) Конструктор
            Operator() = default;
            
            // (2) Конструктор копирования
            Operator(const Operator& newOperator);
            
            // (3) Перегрузка оператора присваивания
            Operator& operator=(const Operator& newOperator) = default;
            
            ////////// Инициализация размеров полей //////////////////////////
            
            // (4) Устанавливается размер вспомогательного 2D поля
            void resize2D(int sizeX, int sizeY);
            
            // (5) Устанавливается размер вспомогательного 3D поля
            void resize3D(int sizeX, int sizeY, int sizeZ);
            
            ////////// Градиент и дивергенция ////////////////////////////////
            
            // (6) 2D Градиент (Возвращает по ссылке векторное поле)
            void grad(const ScalarField2D& inField, VectorField2D& outField);
            
            // (7) 2D Дивергенция (Возвращает по ссылке скалярное поле)
            void div(const VectorField2D& inField, ScalarField2D& outField);
            
            // (8) 3D Градиент (Возвращает по ссылке векторное поле)
            void grad(const ScalarField3D& inField, VectorField3D& outField);
            
            // (9) 3D Дивергенция (Возвращает по ссылке скалярное поле)
            void div(const VectorField3D& inField, ScalarField3D& outField);
            
            ////////// Частные производные всюду /////////////////////////////
            
            // (10) 2D Частная производная функции по "x" всюду
            void derX(const ScalarField2D& inField, ScalarField2D& outField);
            
            // (11) 2D Частная производная функции по "y" всюду
            void derY(const ScalarField2D& inField, ScalarField2D& outField);
            
            // (12) 3D Частная производная функции по "x" всюду
            void derX(const ScalarField3D& inField, ScalarField3D& outField);
            
            // (13) 3D Частная производная функции по "y" всюду
            void derY(const ScalarField3D& inField, ScalarField3D& outField);
            
            // (14) 3D Частная производная функции по "z" всюду (3D)
            void derZ(const ScalarField3D& inField, ScalarField3D& outField);
            
            // (15) Освобождает выделенную память
            void clear();
            
            // (16) Деструктор
            ~Operator() = default;
            
        private :
            
            ////////// Частные производные в точке ///////////////////////////
            
            // (1) 2D Частная производная функции по "x" в точке
            Real derX(const ScalarField2D& inField, int x, int y);
            
            // (2) 2D Частная производная функции по "y"  в точке
            Real derY(const ScalarField2D& inField, int x, int y);
            
            // (3) 3D Частная производная функции по "x" в точке
            Real derX(const ScalarField3D& inField, int x, int y, int z);
            
            // (4) 3D Частная производная функции по "y"  в точке
            Real derY(const ScalarField3D& inField, int x, int y, int z);
            
            // (5) 3D Частная производная функции по "z"  в точке
            Real derZ(const ScalarField3D& inField, int x, int y, int z);
    };
    
    ////////// class Poisson /////////////////////////////////////////////////
    // Позволяет решать уравнение Пуассона для 2D и 3D векторных и          //
    // скалярных полей методом итераций Якоби.                              //
    //                                                                      //
    // 1) alpha, betta - коэффициенты (см. теорию).                         //
    // 2) free         - поле свободных членов уравнения.                   //
    //////////////////////////////////////////////////////////////////////////
    
    class Poisson
    {
        private :
            
            ScalarField2D tempSF2D_;    // Временное скалярное поле 2D
            ScalarField3D tempSF3D_;    // Временное скалярное поле 3D
            
        public :
            
            // (1) Конструктор
            Poisson() = default;
            
            // (2) Конструктор копирования
            Poisson(const Poisson& newPoisson);
            
            // (3) Перегрузка оператора присваивания
            Poisson& operator=(const Poisson& newPoisson) = default;
            
            ////////// Инициализация размеров полей //////////////////////////
            
            // (4) Устанавливается размер вспомогательного 2D поля
            void resize2D(int sizeX, int sizeY);
            
            // (5) Устанавливается размер вспомогательного 3D поля
            void resize3D(int sizeX, int sizeY, int sizeZ);
            
            ////////// Решение ур-я Пуассона методом итераций ////////////////
            
            // (6) 2D Решает уравнение Пуассона
            void solve(ScalarField2D& field, const ScalarField2D& free, 
                       Real alpha, Real betta);
            
            // (7) 2D Решает уравнение Пуассона
            void solve(VectorField2D& field, const VectorField2D& free,
                       Real alpha, Real betta);
            
            // (8) 3D Решает уравнение Пуассона
            void solve(ScalarField3D& field, const ScalarField3D& free, 
                       Real alpha, Real betta);
            
            // (9) 3D Решает уравнение Пуассона
            void solve(VectorField3D& field, const VectorField3D& free,
                       Real alpha, Real betta);
            
            // (10) Освобождает выделенную память
            void clear();
            
            // (11) Деструктор
            ~Poisson() = default;
            
        private :
            
            ////////// Производит одиночный переход в новое состояние ////////
            
            // (1) 2D Возвращает очередное приближение в точке (i, j)
            Real step(const ScalarField2D& field, const ScalarField2D& free, 
                      Real alpha, Real betta, int i, int j);
            
            // (2) 2D Возвращает очередное приближение на всем поле
            void step(ScalarField2D& field, const ScalarField2D& free, 
                      Real alpha, Real betta);
            
            // (3) 3D Возвращает очередное приближение в точке (i, j, k)
            Real step(const ScalarField3D& field, const ScalarField3D& free, 
                      Real alpha, Real betta, int i, int j, int k);
            
            // (4) 3D Возвращает очередное приближение на всем поле
            void step(ScalarField3D& field, const ScalarField3D& free, 
                      Real alpha, Real betta);
    };
    
    ////////// class Interpolation ///////////////////////////////////////////
    // Предоставляет методы для вычисления значения в произвольной (не      //
    // узловой) точке на скалярном 2D и 3D поле. В данном случае            //
    // используются методы билинейной и трилинейной интерполяции.           //
    //////////////////////////////////////////////////////////////////////////
    
    class Interpolation
    {
        private :
            
            Values2D values2D_;     // Набор значений "ф-ции" на прямоуг-ке
            Values3D values3D_;     // Набор значений "ф-ции" на паралл-де
            Real     a0_;           // Вспомогательный коэффициент
            Real     a1_;           // -//-
            Real     a2_;           // -//-
            Real     a3_;           // -//-
            Real     a4_;           // -//-
            Real     a5_;           // -//-
            Real     a6_;           // -//-
            Real     a7_;           // -//-
            
        public :
            
            // (1) Конструктор
            Interpolation();
            
            // (2) Конструктор копирования
            Interpolation(const Interpolation& newObj) = default;
            
            // (3) Перегрузка оператора присваивания
            Interpolation& operator=(const Interpolation& newObj) = default;
            
            // (4) 2D Вычисляет приближенное значение  в (.) на поле "field"
            Real compute(const ScalarField2D& field, Real x, Real y);
            
            // (5) 3D Вычисляет приближенное значение  в (.) на поле "field"
            Real compute(const ScalarField3D& field, Real x, Real y, Real z);
            
            // (6) Обнуляет поля
            void clear();
            
            // (7) Деструктор
            ~Interpolation() = default;
            
        private :
            
            // (1) 2D Вычисляет приближенное значение "ф-ции" в (.)
            Real compute(Real x, Real y);
            
            // (2) 3D Вычисляет приближенное значение "ф-ции" в (.)
            Real compute(Real x, Real y, Real z);
    };
    
    ////////// class Tools ///////////////////////////////////////////////////
    // Класс предоставляет инструменты для вычисления всех величин,         //
    // используемых в уравнении Навье-Стокса в очередной момент времени.    //
    //                                                                      //
    // 1) basic - поле, задающее направления переноса величин (поле         //
    //    скоростей).                                                       //
    // 2) gamma - кинематическая вязкость.                                  //
    //////////////////////////////////////////////////////////////////////////
    
    class Tools
    {
        private :
            
            ScalarField2D tempSF2D_;    // Временное скалярное поле 2D
            ScalarField3D tempSF3D_;    // Временное скалярное поле 3D
            VectorField2D tempVF2D_;    // Временное векторное поле 2D
            VectorField3D tempVF3D_;    // Временное векторное поле 3D
            Interpolation intp_;        // Методы приближенного вычисления
            Poisson       poisson_;     // Методы решения уравнения Пуассона
            
        public :
            
            // (1) Конструктор
            Tools() = default;
            
            // (2) Конструктор копирования
            Tools(const Tools& newTools);
            
            // (3) Перегрузка оператора присваивания
            Tools& operator=(const Tools& newTools) = default;
            
            ////////// Инициализация размеров полей //////////////////////////
            
            // (4) Устанавливается размер вспомогательных 2D полей
            void resize2D(int sizeX, int sizeY);
            
            // (5) Устанавливается размер вспомогательных 3D полей
            void resize3D(int sizeX, int sizeY, int sizeZ);
            
            ////////// Адвекция //////////////////////////////////////////////
            
            // (6) 2D Вычисляет, как поле "basic" переносит значения "field"
            void advection(ScalarField2D& field, const VectorField2D& basic);
            
            // (7) 3D Вычисляет, как поле "basic" переносит значения "field"
            void advection(ScalarField3D& field, const VectorField3D& basic);
            
            // (8) 2D Вычисляет, как поле "basic" переносит значения "field"
            void advection(VectorField2D& field, const VectorField2D& basic);
            
            // (9) 3D Вычисляет, как поле "basic" переносит значения "field"
            void advection(VectorField3D& field, const VectorField3D& basic);
            
            ////////// Вязкая диффузия ///////////////////////////////////////
            
            // (10) 2D Рассчет вязкой диффузии для скалярного поля "field"
            void diffusion(ScalarField2D& field, Real gamma);
            
            // (11) 3D Рассчет вязкой диффузии для скалярного поля "field"
            void diffusion(ScalarField3D& field, Real gamma);
            
            // (12) 2D Рассчет вязкой диффузии для векторного поля "field"
            void diffusion(VectorField2D& field, Real gamma);
            
            // (13) 3D Рассчет вязкой диффузии для векторного поля "field"
            void diffusion(VectorField3D& field, Real gamma);
            
            ////////// Действие сил //////////////////////////////////////////
            
            // ...
            
            // (14) Освобождает выделенную память
            void clear();
            
            // (15) Деструктор
            ~Tools() = default;
            
        private :
            
            // ...
            
    };
}

#endif