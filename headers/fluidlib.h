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
            
            Real*** points_;            // Трехмерный массив элементов поля
            int     sizeX_;             // Размер поля по "X"
            int     sizeY_;             // Размер поля по "Y"
            int     sizeZ_;             // Размер поля по "Z"
            
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
            
            ScalarField componentX;     // Компонента "X"
            ScalarField componentY;     // Компонента "Y"
            ScalarField componentZ;     // Компонента "Z"
            
        public :
            
            // (1) Конструктор
            VectorField() = default;
            
            // (2) Конструктор (Сразу задает размер поля)
            VectorField(int sizeX, int sizeY, int sizeZ);
            
            // (3) Конструктор копирования
            VectorField(const VectorField& field);
            
            // (4) Перегрузка оператора присваивания
            VectorField& operator=(const VectorField& field);
            
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
            
            // Поля... Алармы сюда!
            
        public :
            
            // (1) Градиент (Возвращает по ссылке векторное поле)
            void grad(const ScalarField& inField, VectorField& outField);
            
            // (2) Дивергенция (Возвращает по ссылке скалярное поле)
            void div(const VectorField& inField, ScalarField& outField);
            
            // (3) Частная производная функции по "x" всюду
            void derX(const ScalarField& inField, ScalarField& outField);
            
            // (4) Частная производная функции по "y" всюду
            void derY(const ScalarField& inField, ScalarField& outField);
            
            // (5) Частная производная функции по "z" всюду
            void derZ(const ScalarField& inField, ScalarField& outField);
            
            // (6) Частная производная функции по "x" в точке
            Real derX(const ScalarField& inField, int& x, int& y, int& z);
            
            // (7) Частная производная функции по "y"  в точке
            Real derY(const ScalarField& inField, int& x, int& y, int& z);
            
            // (8) Частная производная функции по "z"  в точке
            Real derZ(const ScalarField& inField, int& x, int& y, int& z);
    };
}

#endif