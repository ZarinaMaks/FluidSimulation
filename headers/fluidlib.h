#ifndef FLUIDLIB_H
#define FLUIDLIB_H

////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include <exception>

namespace fluid
{
    // Максимальный и минимальный размеры поля по "X"
    const int MAX_SIZE_X = 1000;
    const int MIN_SIZE_X = 10;
    
    // Максимальный и минимальный размеры поля по "Y"
    const int MAX_SIZE_Y = 1000;
    const int MIN_SIZE_Y = 10;
    
    // Максимальный и минимальный размеры поля по "Z"
    const int MAX_SIZE_Z = 1000;
    const int MIN_SIZE_Z = 10;
    
    // Универсальный вещественный тип
    typedef double real;
    
    ////////// class FluidException //////////////////////////////////////////
    // Дочерний класс, унаследованный от "std::exception". Содежит в себе   //
    // код ошибки "errCode_" >= 0 (0 - отсутствие ошибок).                  //
    // Описание ошибок см. файл....                                         //
    //////////////////////////////////////////////////////////////////////////
    
    class FluidException : public std::exception
    {
        private :
            
            int errCode_;   // Код ошибки
            
        public :
            
            // (1) Конструктор (обнуляет поле)
            FluidException();
            
            // (2) Конструктор (инициализирует поле)
            FluidException(const int& code);
            
            // (3) Конструктор копирования
            FluidException(const FluidException& exeption);
            
            // (4) Перегрузка оператора присваивания
            FluidException& operator=(const FluidException& exeption);
            
            // (5) Возвращает код ошибки
            int error() const;
            
            // (6) Установить значение ошибки
            void setErrCode(const int& code);
    };
    
    ////////// struct Vector /////////////////////////////////////////////////
    // Эта структура описывает трехмерный вектор.                           //
    //////////////////////////////////////////////////////////////////////////
    
    struct Vector
    {
        public :
            
            real x;         // Составляющая "x"
            real y;         // Составляющая "y"
            real z;         // Составляющая "z"
            
        public :
            
            // (1) Конструктор (обнуляет поля)
            Vector();
            
            // (2) Конструктор копирования
            Vector(const Vector& vector);
            
            // (3) Перегрузка оператора присваивания
            Vector& operator=(const Vector& vector);
            
            // (4) Обнуляет поля
            void clear();
            
            // (5) Деструктор
            ~Vector();
    };
    
    ////////// class Field ///////////////////////////////////////////////////
    // Поле величин типа "Т", подразумевается использование скалярного и    //
    // векторного полей.                                                    //
    //                                                                      //
    // В общем случае :                                                     //
    //  1) MIN_SIZE_X <= sizeX_ <= MAX_SIZE_X                               //
    //  2) MIN_SIZE_Y <= sizeY_ <= MAX_SIZE_Y                               //
    //  3) MIN_SIZE_Z <= sizeZ_ <= MAX_SIZE_Z                               //
    //////////////////////////////////////////////////////////////////////////
    
    template <typename T>
    
    class Field
    {
        private :
            
            T*** cells_;    // Трехмерный массив элементов поля
            int  sizeX_;    // Размер поля по "X"
            int  sizeY_;    // Размер поля по "Y"
            int  sizeZ_;    // Размер поля по "Z"
            
        public :
            
            // (1) Конструктор (обнуляет поля класса)
            Field();
            
            // (2) Конструктор (Сразу задает размер поля)
            Field(const int& sizeX, const int& sizeY, const int& sizeZ);
            
            // (3) Конструктор копирования
            Field(const Field& field);
            
            // (4) Перегрузка оператора присваивания
            Field& operator=(const Field& field);
            
            // (5) Изменяет размер поля, уничтожая имеющуюся информацию
            void resize(const int& sizeX, const int& sizeY, const int& sizeZ);
            
            // (6) Перегрузка оператора ()
            T& operator()(const int& x, const int& y, const int& z);
            
            // (7) Перегрузка оператора () (const случай)
            const T& operator()(const int& x, const int& y, 
                                const int& z) const;
            
            // (8) Возвращает размер по "X"
            int getSizeX() const;
            
            // (9) Возвращает размер по "Y"
            int getSizeY() const;
            
            // (10) Возвращает размер по "Z"
            int getSizeZ() const;
            
            // (11) Освобождает выделенную память
            void clear();
            
            // (12) Деструктор
            ~Field();
    };
    
    ////////// class Field ///////////////////////////////////////////////////////
    // Описание методов.                                                        //
    //////////////////////////////////////////////////////////////////////////////
    
    template <typename T>
    
    // (1) Конструктор (обнуляет поля класса)
    Field<T>::Field()
    {
        cells_ = nullptr;
        sizeX_ = 0;
        sizeY_ = 0;
        sizeZ_ = 0;
    }
    
    template <typename T>
    
    // (2) Конструктор (Сразу задает размер поля)
    Field<T>::Field(const int& sizeX, const int& sizeY, const int& sizeZ)
    {
        try
        {
            resize(sizeX, sizeY, sizeZ);
        }
        catch (...)
        {
            // Предотвращаем выброс исключения
        }
    }
    
    template <typename T>
    
    // (3) Конструктор копирования
    Field<T>::Field(const Field& field)
    {
        *this = field;
    }
    
    template <typename T>
    
    // (4) Перегрузка оператора присваивания
    Field<T>& Field<T>::operator=(const Field& field)
    {
        // Самоприсваивание
        if (this != &field)
        {
            // Меняем размер
            try
            {
                resize(field.sizeX_, field.sizeY_, field.sizeZ_);
            }
            catch (...)
            {
                // Предотвращаем выброс исключения
            }
            
            // Копируем данные
            for (int i = 0; i < sizeX_; ++i)
            {
                for (int j = 0; j < sizeY_; ++j)
                {
                    for (int k = 0; k < sizeZ_; ++k)
                    {
                        cells_[i][j][k] = field.cells_[i][j][k];
                    }
                }
            }
        }
        return *this;
    }
    
    template <typename T>
    
    // (5) Изменяет размер поля, уничтожая имеющуюся информацию
    void Field<T>::resize(const int& sizeX, const int& sizeY, 
                          const int& sizeZ)
    {
        // Если размеры массивов отличаются
        bool hasDiff = sizeX_ != sizeX || sizeY_ != sizeY || sizeZ_ != sizeZ;
        
        // Если значения аргументов корректны 
        bool isOkX = sizeX >= MIN_SIZE_X && sizeX <= MAX_SIZE_X;
        bool isOkY = sizeY >= MIN_SIZE_Y && sizeY <= MAX_SIZE_Y;
        bool isOkZ = sizeZ >= MIN_SIZE_Y && sizeY <= MAX_SIZE_Y;
        bool isOk  = isOkX && isOkY && isOkZ;
        
        // Если имеет смысл менять размер массива
        try
        {
            if (isOk && hasDiff)
            {
                // Освобождение памяти
                clear();
                
                // Новые размеры
                sizeX_ = sizeX;
                sizeY_ = sizeY;
                sizeZ_ = sizeZ;
                
                // Выделение новой памяти
                cells_ = new T**[sizeX_];
                for (int i = 0; i < sizeX_; ++i)
                {
                    cells_[i] = new T*[sizeY_];
                    for (int j = 0; j < sizeY_; ++j)
                    {
                        cells_[i][j] = new T[sizeZ_];
                    }
                }
            }
        }
        catch (std::bad_alloc&)
        {
            clear();
            throw FluidException(1);
        }
        catch (std::exception&)
        {
            clear();
            throw FluidException(2);
        }
        catch (...)
        {
            clear();
            throw FluidException(3);
        }
    }
    
    template <typename T>
    
    // (6) Перегрузка оператора ()
    T& Field<T>::operator()(const int& x, const int& y, const int& z)
    {
        // Если значения аргументов корректны
        bool isOkX = x < sizeX_ && x >= 0;
        bool isOkY = y < sizeY_ && y >= 0;
        bool isOkZ = z < sizeZ_ && z >= 0;
        
        // Выброс исключения, если был выход за границы
        if (!isOkX || !isOkY || !isOkZ)
        {
            throw FluidException(4);
        }
        return cells_[x][y][z];
    }
    
    template <typename T>
    
    // (7) Перегрузка оператора () (const случай)
    const T& Field<T>::operator()(const int& x, const int& y, 
                                  const int& z) const
    {
        return this->operator()(x,y,z);
    }
    
    template <typename T>
    
    // (8) Возвращает размер по "X"
    int Field<T>::getSizeX() const
    {
        return sizeX_;
    }
    
    template <typename T>
    
    // (9) Возвращает размер по "Y"
    int Field<T>::getSizeY() const
    {
        return sizeY_;
    }
    
    template <typename T>
    
    // (10) Возвращает размер по "Z"
    int Field<T>::getSizeZ() const
    {
        return sizeZ_;
    }
    
    template <typename T>
    
    // (11) Освобождает выделенную память
    void Field<T>::clear()
    {
        // Освобождение памяти
        if (cells_ != nullptr)
        {
            for (int i = 0; i < sizeX_; ++i)
            {
                if (cells_[i] != nullptr)
                {
                    for (int j = 0; j < sizeY_; ++j)
                    {
                        if (cells_[i][j] != nullptr)
                        {
                            delete[] cells_[i][j];
                        }
                    }
                    delete[] cells_[i];
                }
            }
            delete[] cells_;
            cells_ = nullptr;
        }
        
        // Обнуление переменных
        sizeX_ = 0;
        sizeY_ = 0;
        sizeZ_ = 0;
    }
    
    template <typename T>
    
    // (12) Деструктор
    Field<T>::~Field()
    {
        clear();
    }
    
    ////////// typedefs //////////////////////////////////////////////////////
    // Определения типов скалярного и векторного полей.                     //
    //////////////////////////////////////////////////////////////////////////
    
    // Векторное поле
    typedef Field<Vector> VectorField;
    
    // Скалярное поле
    typedef Field<real>   ScalarField;
    
    ////////// class Operator ////////////////////////////////////////////////
    // Класс, предназначенный для отыскания градиентов, дивергенций,        //
    // лапласианов в определенной точке поля.                               //
    //////////////////////////////////////////////////////////////////////////
    
    class Operator
    {
        private :
            
            // Поля...
            
        public :
            
            // (1) Градиент
            Vector grad(const ScalarField& field, const int& x, const int& y, 
                        const int& z);
            
            // (2) Дивергенция
            real div(const VectorField& field, const int& x, const int& y, 
                     const int& z);
            
            // (3) Оператор Лапласа
            real divGrad(const ScalarField& field, const int& x, const int& y, 
                         const int& z);
    };
}

#endif