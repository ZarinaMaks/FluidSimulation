////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "componentlib2d.h"

using namespace fluid;

////////// class ScalarField2D ///////////////////////////////////////////////
// Описание : componentlib2d.h.                                             //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор (обнуляет поля класса)
ScalarField2D::ScalarField2D()
{
    points_ = nullptr;
    sizeX_  = 0;
    sizeY_  = 0;
}

// (2) Конструктор (Сразу задает размер поля)
ScalarField2D::ScalarField2D(int sizeX, int sizeY)
{
    try
    {
        points_ = nullptr;
        sizeX_  = 0;
        sizeY_  = 0;
        resize(sizeX, sizeY);
    }
    catch (...)
    {
        // Предотвращаем выброс исключения
    }
}

// (3) Конструктор копирования
ScalarField2D::ScalarField2D(const ScalarField2D& field)
{
    *this = field;
}

// (4) Перегрузка оператора присваивания
ScalarField2D& ScalarField2D::operator=(const ScalarField2D& field)
{
    // Самоприсваивание
    if (this != &field)
    {
        try
        {
            // Меняем размер
            resize(field.sizeX_, field.sizeY_);
            
            // Копируем данные
            for (int i = 0; i < sizeX_; ++i)
            {
                for (int j = 0; j < sizeY_; ++j)
                {
                    points_[i][j] = field.points_[i][j];
                }
            }
        }
        catch (...)
        {
            clear();
        }
    }
    return *this;
}

// (5) Изменяет размер поля, уничтожая всю информацию
void ScalarField2D::resize(int sizeX, int sizeY)
{
    // Если размеры массивов отличаются
    bool hasDiff   = sizeX_ != sizeX || sizeY_ != sizeY;
    
    // Если значения аргументов корректны
    bool isInRange = inRangeSizeX(sizeX) && inRangeSizeY(sizeY);
    
    try
    {
        // Если имеет смысл менять размер массива
        if (isInRange && hasDiff)
        {
            // Освобождение памяти
            clear();
            
            // Новые размеры
            sizeX_ = sizeX;
            sizeY_ = sizeY;
            
            // Выделение новой памяти
            points_ = new Real*[sizeX_];
            for (int i = 0; i < sizeX_; ++i)
            {
                points_[i] = new Real[sizeY_];
            }
            
            // Обнуляем массив
            reset();
        }
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (6) Перегрузка оператора ()
Real& ScalarField2D::operator()(int x, int y)
{
    // Выброс исключения, если был выход за границы
    if (!isInRange(x, y))
    {
        throw err::FluidException(1);
    }
    return points_[x][y];
}

// (7) Перегрузка оператора () (const случай)
const Real& ScalarField2D::operator()(int x, int y) const
{
    // Выброс исключения, если был выход за границы
    if (!isInRange(x, y))
    {
        throw err::FluidException(1);
    }
    return points_[x][y];
}

// (8) Проверка на выход за границы
bool ScalarField2D::isInRange(int x, int y) const
{
    // Если значения аргументов корректны
    bool isInRangeX = x < sizeX_ && x >= 0;
    bool isInRangeY = y < sizeY_ && y >= 0;
    
    return isInRangeX && isInRangeY;
}

// (9) Возвращает размер по "x"
int ScalarField2D::getSizeX() const
{
    return sizeX_;
}

// (10) Возвращает размер по "y"
int ScalarField2D::getSizeY() const
{
    return sizeY_;
}

// (11) Обнуляет содержимое
void ScalarField2D::reset()
{
    // Обнуление всех элементов поля
    if (points_ != nullptr)
    {
        for (int i = 0; i < sizeX_; ++i)
        {
            if (points_[i] != nullptr)
            {
                for (int j = 0; j < sizeY_; ++j)
                {
                    points_[i][j] = 0;
                }
            }
        }
    }
}

// (12) Освобождает выделенную память
void ScalarField2D::clear()
{
    // Освобождение памяти
    if (points_ != nullptr)
    {
        for (int i = 0; i < sizeX_; ++i)
        {
            if (points_[i] != nullptr)
            {
                delete[] points_[i];
            }
        }
        delete[] points_;
        points_ = nullptr;
    }
    
    // Обнуление переменных
    sizeX_ = 0;
    sizeY_ = 0;
}

// (13) Деструктор
ScalarField2D::~ScalarField2D()
{
    clear();
}

////////// class VectorField2D ///////////////////////////////////////////////
// Описание : componentlib2d.h.                                             //
//////////////////////////////////////////////////////////////////////////////

// (2) Конструктор (Сразу задает размер поля)
VectorField2D::VectorField2D(int sizeX, int sizeY)
{
    try
    {
        resize(sizeX, sizeY);
    }
    catch (...)
    {
        // Предотвращаем выброс исключения
    }
}

// (3) Конструктор копирования
VectorField2D::VectorField2D(const VectorField2D& field)
{
    *this = field;
}

// (5) Изменяет размер поля, уничтожая всю информацию
void VectorField2D::resize(int sizeX, int sizeY)
{
    try
    {
        componentX_.resize(sizeX, sizeY);
        componentY_.resize(sizeX, sizeY);
    }
    catch (...)
    {
        clear();
    }
}

// (6) Доступ по ссылке к скалярному полю "x"
ScalarField2D& VectorField2D::x()
{
    return componentX_;
}

// (7) Доступ по ссылке к скалярному полю "y"
ScalarField2D& VectorField2D::y()
{
    return componentY_;
}

// (8) Доступ по "const" ссылке к скалярному полю "x"
const ScalarField2D& VectorField2D::x() const
{
    return componentX_;
}

// (9) Доступ по "const" ссылке к скалярному полю "y"
const ScalarField2D& VectorField2D::y() const
{
    return componentY_;
}

// (10) Возвращает размер по "x"
int VectorField2D::getSizeX() const
{
    return componentX_.getSizeX();
}

// (11) Возвращает размер по "y"
int VectorField2D::getSizeY() const
{
    return componentX_.getSizeY();
}

// (12) Обнуляет содержимое поля
void VectorField2D::reset()
{
    componentX_.reset();
    componentY_.reset();
}

// (13) Освобождает выделенную память
void VectorField2D::clear()
{
    componentX_.clear();
    componentY_.clear();
}

////////// struct Values2D ///////////////////////////////////////////////////
// Описание : fluidlib.h.                                                   //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор (обнуляет поля)
Values2D::Values2D()
{
    fx0y0 = 0;
    fx0y1 = 0;
    fx1y0 = 0;
    fx1y1 = 0;
}

// (4) Обнуляет поля
void Values2D::clear()
{
    fx0y0 = 0;
    fx0y1 = 0;
    fx1y0 = 0;
    fx1y1 = 0;
}

////////// class WorkZone2D //////////////////////////////////////////////////
// Описание : componentlib2d.h.                                             //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор (обнуляет поля класса)
WorkZone2D::WorkZone2D()
{
    points_ = nullptr;
    sizeX_  = 0;
    sizeY_  = 0;
}

// (2) Конструктор (Сразу задает размер поля)
WorkZone2D::WorkZone2D(int sizeX, int sizeY)
{
    try
    {
        points_ = nullptr;
        sizeX_  = 0;
        sizeY_  = 0;
        resize(sizeX, sizeY);
    }
    catch (...)
    {
        // Предотвращаем выброс исключения
    }
}

// (3) Конструктор копирования
WorkZone2D::WorkZone2D(const WorkZone2D& field)
{
    *this = field;
}

// (4) Перегрузка оператора присваивания
WorkZone2D& WorkZone2D::operator=(const WorkZone2D& field)
{
    // Самоприсваивание
    if (this != &field)
    {
        try
        {
            // Меняем размер
            resize(field.sizeX_, field.sizeY_);
            
            // Копируем данные
            for (int i = 0; i < sizeX_; ++i)
            {
                for (int j = 0; j < sizeY_; ++j)
                {
                    points_[i][j] = field.points_[i][j];
                }
            }
        }
        catch (...)
        {
            clear();
        }
    }
    return *this;
}

// (5) Изменяет размер поля, уничтожая всю информацию
void WorkZone2D::resize(int sizeX, int sizeY)
{
    // Если размеры массивов отличаются
    bool hasDiff   = sizeX_ != sizeX || sizeY_ != sizeY;
    
    // Если значения аргументов корректны
    bool isInRange = inRangeSizeX(sizeX) && inRangeSizeY(sizeY);
    
    try
    {
        // Если имеет смысл менять размер массива
        if (isInRange && hasDiff)
        {
            // Освобождение памяти
            clear();
            
            // Новые размеры
            sizeX_ = sizeX;
            sizeY_ = sizeY;
            
            // Выделение новой памяти
            points_ = new bool*[sizeX_];
            for (int i = 0; i < sizeX_; ++i)
            {
                points_[i] = new bool[sizeY_];
            }
            
            // Обнуляем массив
            reset();
        }
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (6) Перегрузка оператора ()
bool& WorkZone2D::operator()(int x, int y)
{
    // Выброс исключения, если был выход за границы
    if (!isInRange(x, y))
    {
        throw err::FluidException(1);
    }
    return points_[x][y];
}

// (7) Перегрузка оператора () (const случай)
const bool& WorkZone2D::operator()(int x, int y) const
{
    // Выброс исключения, если был выход за границы
    if (!isInRange(x, y))
    {
        throw err::FluidException(1);
    }
    return points_[x][y];
}

// (8) Проверка на выход за границы
bool WorkZone2D::isInRange(int x, int y) const
{
    // Если значения аргументов корректны
    bool isInRangeX = x < sizeX_ && x >= 0;
    bool isInRangeY = y < sizeY_ && y >= 0;
        
    return isInRangeX && isInRangeY;
}

// (9) Возвращает размер по "x"
int WorkZone2D::getSizeX() const
{
    return sizeX_;
}

// (10) Возвращает размер по "y"
int WorkZone2D::getSizeY() const
{
    return sizeY_;
}

// (11) Обнуляет содержимое поля
void WorkZone2D::reset()
{
    // Обнуление всех элементов поля
    if (points_ != nullptr)
    {
        for (int i = 0; i < sizeX_; ++i)
        {
            if (points_[i] != nullptr)
            {
                for (int j = 0; j < sizeY_; ++j)
                {
                    points_[i][j] = false;
                }
            }
        }
    }
}

// (12) Освобождает выделенную память
void WorkZone2D::clear()
{
    // Освобождение памяти
    if (points_ != nullptr)
    {
        for (int i = 0; i < sizeX_; ++i)
        {
            if (points_[i] != nullptr)
            {
                delete[] points_[i];
            }
        }
        delete[] points_;
        points_ = nullptr;
    }
    
    // Обнуление переменных
    sizeX_ = 0;
    sizeY_ = 0;
}

// (13) Деструктор
WorkZone2D::~WorkZone2D()
{
    clear();
}