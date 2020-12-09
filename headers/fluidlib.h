#ifndef FLUIDLIB_H
#define FLUIDLIB_H

////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "errlib.h"

namespace fluid
{
    // Универсальный вещественный тип
    typedef double Real;
    
    // Максимальный и минимальный размеры поля "Field" по "X"
    const int MAX_SIZE_X = 1000;
    const int MIN_SIZE_X = 2;
    
    // Максимальный и минимальный размеры поля "Field" по "Y"
    const int MAX_SIZE_Y = 1000;
    const int MIN_SIZE_Y = 2;
    
    // Максимальный и минимальный размеры поля "Field" по "Z"
    const int MAX_SIZE_Z = 1000;
    const int MIN_SIZE_Z = 2;
    
    // Количество шагов для метода итераций Якоби
    const int JACOBI_STEP_NUMBER = 100;
    
    // Приращения аргументов
    const Real DT = 1.0;
    const Real DS = 1.0;
    const Real DX = DS;
    const Real DY = DS;
    const Real DZ = DS;
    
    ////////// bool inRangeSizeX/Y/Z /////////////////////////////////////////
    // Возвращают "true", если значение аргумента не выходит за границы.    //
    //////////////////////////////////////////////////////////////////////////
    
    bool inRangeSizeX(const int& sizeX);
    
    bool inRangeSizeY(const int& sizeY);
    
    bool inRangeSizeZ(const int& sizeZ);
    
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
            Real   a0_;             // Вспомогательный коэффициент
            Real   a1_;             // -//-
            Real   a2_;             // -//-
            Real   a3_;             // -//-
            Real   a4_;             // -//-
            Real   a5_;             // -//-
            Real   a6_;             // -//-
            Real   a7_;             // -//-
            
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
            
            // (13) 2D Рассчет вязкой диффузии для векторного поля "field"
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