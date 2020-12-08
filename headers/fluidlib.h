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
    const int MIN_SIZE_X = 1;
    
    // Максимальный и минимальный размеры поля "Field" по "Y"
    const int MAX_SIZE_Y = 1000;
    const int MIN_SIZE_Y = 1;
    
    // Максимальный и минимальный размеры поля "Field" по "Z"
    const int MAX_SIZE_Z = 1000;
    const int MIN_SIZE_Z = 1;
    
    // Количество шагов для метода итераций Якоби
    const int JACOBI_STEP_NUMBER = 100;
    
    // Приращения аргументов
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
    
    /*
    ////////// class Vector //////////////////////////////////////////////////
    // Этот класс описывает трехмерный вектор.                              //
    //////////////////////////////////////////////////////////////////////////
    
    class Vector
    {
        private :
            
            Real x_;        // Составляющая "x"
            Real y_;        // Составляющая "y"
            Real z_;        // Составляющая "z"
            
        public :
            
            // (1) Конструктор (обнуляет поля)
            Vector();
            
            // (2) Конструктор копирования
            Vector(const Vector& vector);
            
            // (3) Конструктор (задает составляющие вектора)
            Vector(Real& x, Real& y, Real& z);
            
            // (4) Перегрузка оператора присваивания
            Vector& operator=(const Vector& vector);
            
            // (5) Доступ к составляющей "x"
            Real& x();
            
            // (6) Доступ к составляющей "y"
            Real& y();
            
            // (7) Доступ к составляющей "z"
            Real& z();
            
            // (8) Константный доступ к составляющей "x"
            const Real& x() const;
            
            // (9) Константный доступ к составляющей "y"
            const Real& y() const;
            
            // (10) Константный доступ к составляющей "z"
            const Real& z() const;
            
            // (11) Обнуляет поля
            void clear();
            
            // (12) Деструктор
            ~Vector();
    };
    */
    
    ////////// class ScalarField /////////////////////////////////////////////
    // Класс, описывающий скалярное поле.                                   //
    //                                                                      //
    // В общем случае :                                                     //
    //  1) MIN_SIZE_X <= sizeX_ <= MAX_SIZE_X                               //
    //  2) MIN_SIZE_Y <= sizeY_ <= MAX_SIZE_Y                               //
    //  3) MIN_SIZE_Z <= sizeZ_ <= MAX_SIZE_Z                               //
    //////////////////////////////////////////////////////////////////////////
    
    class ScalarField
    {
        private :
            
            Real*** points_;        // Трехмерный массив элементов поля
            int     sizeX_;         // Размер поля по "X"
            int     sizeY_;         // Размер поля по "Y"
            int     sizeZ_;         // Размер поля по "Z"
            
        public :
            
            // (1) Конструктор (обнуляет поля класса)
            ScalarField();
            
            // (2) Конструктор (Сразу задает размер поля)
            ScalarField(int sizeX, int sizeY, int sizeZ);
            
            // (3) Конструктор копирования
            ScalarField(const ScalarField& field);
            
            // (4) Перегрузка оператора присваивания
            ScalarField& operator=(const ScalarField& field);
            
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
            ScalarField& operator+=(const ScalarField& field);
            
            // (13) Перегрузка оператора "-="
            ScalarField& operator-=(const ScalarField& field);
            
            // (14) Освобождает выделенную память
            void clear();
            
            // (15) Деструктор
            ~ScalarField();
    };
    
    ////////// class VectorField /////////////////////////////////////////////
    // Класс, описывающий векторное поле, как набор трех скалярных полей.   //
    //////////////////////////////////////////////////////////////////////////
    
    class VectorField
    {
        private :
            
            ScalarField componentX_;    // Компонента "X"
            ScalarField componentY_;    // Компонента "Y"
            ScalarField componentZ_;    // Компонента "Z"
            
        public :
            
            // (1) Конструктор
            VectorField() = default;
            
            // (2) Конструктор (Сразу задает размер поля)
            VectorField(int sizeX, int sizeY, int sizeZ);
            
            // (3) Конструктор копирования
            VectorField(const VectorField& field);
            
            // (4) Перегрузка оператора присваивания
            VectorField& operator=(const VectorField& field) = default;
            
            // (5) Изменяет размер поля, уничтожая всю информацию
            void resize(int sizeX, int sizeY, int sizeZ);
            
            // (6) Доступ по ссылке к скалярному полю "X"
            ScalarField& x();
            
            // (7) Доступ по ссылке к скалярному полю "Y"
            ScalarField& y();
            
            // (8) Доступ по ссылке к скалярному полю "Z"
            ScalarField& z();
            
            // (9) Доступ по "const" ссылке к скалярному полю "X"
            const ScalarField& x() const;
            
            // (10) Доступ по "const" ссылке к скалярному полю "Y"
            const ScalarField& y() const;
            
            // (11) Доступ по "const" ссылке к скалярному полю "Z"
            const ScalarField& z() const;
            
            // (12) Возвращает размер по "X"
            int getSizeX() const;
            
            // (13) Возвращает размер по "Y"
            int getSizeY() const;
            
            // (14) Возвращает размер по "Z"
            int getSizeZ() const;
            
            // (15) Перегрузка оператора "+="
            VectorField& operator+=(const VectorField& field);
            
            // (16) Перегрузка оператора "-="
            VectorField& operator-=(const VectorField& field);
            
            // (17) Освобождает выделенную память
            void clear();
            
            // (18) Деструктор
            ~VectorField() = default;
    };
    
    ////////// class Operator ////////////////////////////////////////////////
    // Класс, предназначенный для отыскания частных производных,            //
    // градиентов, дивергенций скалярных и векторных полей.                 //
    //////////////////////////////////////////////////////////////////////////
    
    class Operator
    {
        private :
            
            ScalarField tempSF_;    // Временное скалярное поле
            
        public :
            
            // (1) Конструктор
            Operator() = default;
            
            // (2) Конструктор (Сразу задает размер вспомогательных полей)
            Operator(int sizeX, int sizeY, int sizeZ);
            
            // (3) Конструктор копирования
            Operator(const Operator& newOperator);
            
            // (4) Перегрузка оператора присваивания
            Operator& operator=(const Operator& newOperator) = default;
            
            // (5) Устанавливается размер вспомогательных полей
            void resize(int sizeX, int sizeY, int sizeZ);
            
            // (6) Градиент (Возвращает по ссылке векторное поле)
            void grad(const ScalarField& inField, VectorField& outField);
            
            // (7) Дивергенция (Возвращает по ссылке скалярное поле)
            void div(const VectorField& inField, ScalarField& outField);
            
            // (8) Частная производная функции по "x" всюду
            void derX(const ScalarField& inField, ScalarField& outField);
            
            // (9) Частная производная функции по "y" всюду
            void derY(const ScalarField& inField, ScalarField& outField);
            
            // (10) Частная производная функции по "z" всюду
            void derZ(const ScalarField& inField, ScalarField& outField);
            
            // (11) Освобождает выделенную память
            void clear();
            
            // (12) Деструктор
            ~Operator() = default;
            
        private :
            
            // (1) Частная производная функции по "x" в точке
            Real derX(const ScalarField& inField, int& x, int& y, int& z);
            
            // (2) Частная производная функции по "y"  в точке
            Real derY(const ScalarField& inField, int& x, int& y, int& z);
            
            // (3) Частная производная функции по "z"  в точке
            Real derZ(const ScalarField& inField, int& x, int& y, int& z);
    };
    
    ////////// class Poisson /////////////////////////////////////////////////
    // Позволяет решать уравнение Пуассона для векторных и скалярных полей  //
    // методом итераций Якоби.                                              //
    //////////////////////////////////////////////////////////////////////////
    
    class Poisson
    {
        private :
            
            ScalarField curStep_;   // Состояние поля на текущем шаге
            
        public :
            
            // (1) Конструктор
            Poisson() = default;
            
            // (2) Конструктор (Сразу задает размер вспомогательных полей)
            Poisson(int sizeX, int sizeY, int sizeZ);
            
            // (3) Конструктор копирования
            Poisson(const Poisson& newPoisson);
            
            // (4) Перегрузка оператора присваивания
            Poisson& operator=(const Poisson& newPoisson) = default;
            
            // (5) Устанавливается размер вспомогательных полей
            void resize(int sizeX, int sizeY, int sizeZ);
            
            // (6) Решает уравнение Пуассона; "free" - свободный член (Scalar)
            void solve(ScalarField& field, const ScalarField& free, 
                       Real alpha, Real betta);
            
            // (7) Решает уравнение Пуассона; "free" - свободный член (Vector)
            void solve(VectorField& field, const VectorField& free,
                       Real alpha, Real betta);
            
            // (8) Освобождает выделенную память
            void clear();
            
            // (9) Деструктор
            ~Poisson() = default;
            
        private :
            
            // (1) Возвращает очередное приближение в точке (i, j, k)
            Real step(const ScalarField& field, const ScalarField& free, 
                      Real alpha, Real betta, int i, int j, int k);
            
            // (2) Возвращает очередное приближение на всем поле
            void step(ScalarField& field, const ScalarField& free, 
                      Real alpha, Real betta);
    };
    
    ////////// struct Values /////////////////////////////////////////////////
    // Структура, предназначеная для передачи значений интерполируемой      //
    // фунции в вершинах параллелепипеда со сторонами DX, DY, DZ.           //
    //////////////////////////////////////////////////////////////////////////
    
    struct Values
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
            Values();
            
            // (2) Конструктор копирования
            Values(const Values& values) = default;
            
            // (3) Перегрузка оператора присваивания
            Values& operator=(const Values& values) = default;
            
            // (4) Обнуляет поля
            void clear();
            
            // (5) Деструктор
            ~Values() = default;
    };
    
    ////////// class Interpolation ///////////////////////////////////////////
    // Предоставляет методы для вычисления значения в произвольной (не      //
    // узловой) точке на скалярном поле. В данном случае используется метод //
    // трилинейной интерполяции.                                            //
    //////////////////////////////////////////////////////////////////////////
    
    class Interpolation
    {
        private :
            
            Values values_;     // Набор значений "ф-ции" в вершинах
            Real   a0_;         // Вспомогательные коэффициенты
            Real   a1_;
            Real   a2_;
            Real   a3_;
            Real   a4_;
            Real   a5_;
            Real   a6_;
            Real   a7_;
            
        public :
            
            // (1) Конструктор
            Interpolation();
            
            // (2) Конструктор копирования
            Interpolation(const Interpolation& newObj) = default;
            
            // (3) Перегрузка оператора присваивания
            Interpolation& operator=(const Interpolation& newObj) = default;
            
            // (4) Вычисляет приближенное значение  в (.) на поле "field"
            Real compute(const ScalarField& field, Real x, Real y, Real z);
            
            // (5) Обнуляет поля
            void clear();
            
            // (6) Деструктор
            ~Interpolation() = default;
            
        private :
            
            // (1) Вычисляет приближенное значение  в (.), используя "values"
            Real compute(Real x, Real y, Real z);
    };
    
    
}

#endif