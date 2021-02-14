////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "componentlib2d.h"

using namespace fluid;

////////// class SField2D ////////////////////////////////////////////////////
// Описание : componentlib2d.h.                                             //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор (обнуляет поля)
SField2D::SField2D()
{
    points_ = nullptr;
    sizeX_  = 0;
    sizeY_  = 0;
}

// (2) Конструктор копирования
SField2D::SField2D(const SField2D& field)
{
    *this = field;
}

// (3) Перегрузка оператора присваивания
SField2D& SField2D::operator=(const SField2D& field)
{
    // Нет самоприсваивания
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

// (4) Изменяет размер поля, уничтожая всю информацию
void SField2D::resize(int sizeX, int sizeY)
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
            points_ = new Point*[sizeX_];
            for (int i = 0; i < sizeX_; ++i)
            {
                points_[i] = new Point[sizeY_];
            }
            
            // Обновляем значения в массиве
            resetField(0);
            resetArea(false);
        }
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (5) Доступ к величинам на поле
Real& SField2D::field(int x, int y)
{
    // Выброс исключения, если был выход за границы
    if (!isInRange(x, y))
    {
        throw err::FluidException(1);
    }
    
    // Иначе возвращаем элемент
    return points_[x][y].value;
}

// (6) Доступ к величинам на поле (const)
const Real& SField2D::field(int x, int y) const
{
    // Выброс исключения, если был выход за границы
    if (!isInRange(x, y))
    {
        throw err::FluidException(1);
    }
    
    // Иначе возвращаем элемент
    return points_[x][y].value;
}

// (7) Доступ к области задания
bool& SField2D::area(int x, int y)
{
    // Выброс исключения, если был выход за границы
    if (!isInRange(x, y))
    {
        throw err::FluidException(1);
    }
    
    // Иначе возвращаем элемент
    return points_[x][y].isInArea;
}

// (8) Доступ к области задания (const)
const bool& SField2D::area(int x, int y) const
{
    // Выброс исключения, если был выход за границы
    if (!isInRange(x, y))
    {
        throw err::FluidException(1);
    }
    
    // Иначе возвращаем элемент
    return points_[x][y].isInArea;
}

// (9) Проверка на выход за границы
bool SField2D::isInRange(int x, int y) const
{
    // Если значения аргументов корректны
    bool isInRangeX = x < sizeX_ && x >= 0;
    bool isInRangeY = y < sizeY_ && y >= 0;
    
    return isInRangeX && isInRangeY;
}

// (10) Возвращает размер по "x"
int SField2D::getSizeX() const
{
    return sizeX_;
}

// (11) Возвращает размер по "y"
int SField2D::getSizeY() const
{
    return sizeY_;
}

// (12) Обновляет значения величин на поле
void SField2D::resetField(Real newValue)
{
    // Обновление всех элементов поля
    if (points_ != nullptr)
    {
        for (int i = 0; i < sizeX_; ++i)
        {
            if (points_[i] != nullptr)
            {
                for (int j = 0; j < sizeY_; ++j)
                {
                    points_[i][j].value = newValue;
                }
            }
        }
    }
}

// (13) Обновляет область задания
void SField2D::resetArea(bool newValue)
{
    // Обновление всех элементов поля
    if (points_ != nullptr)
    {
        for (int i = 0; i < sizeX_; ++i)
        {
            if (points_[i] != nullptr)
            {
                for (int j = 0; j < sizeY_; ++j)
                {
                    points_[i][j].isInArea = newValue;
                }
            }
        }
    }
}

// (14) Освобождает выделенную память
void SField2D::clear()
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

// (15) Деструктор
SField2D::~SField2D()
{
    clear();
}

////////// class VField2D ////////////////////////////////////////////////////
// Описание : componentlib2d.h.                                             //
//////////////////////////////////////////////////////////////////////////////

// (4) Изменяет размер поля, уничтожая всю информацию
void VField2D::resize(int sizeX, int sizeY)
{
    try
    {
        componentX_.resize(sizeX, sizeY);
        componentY_.resize(sizeX, sizeY);
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (5) Доступ по ссылке к скалярному полю "x"
SField2D& VField2D::x()
{
    return componentX_;
}

// (6) Доступ по ссылке к скалярному полю "y"
SField2D& VField2D::y()
{
    return componentY_;
}

// (7) Доступ по "const" ссылке к скалярному полю "x"
const SField2D& VField2D::x() const
{
    return componentX_;
}

// (8) Доступ по "const" ссылке к скалярному полю "y"
const SField2D& VField2D::y() const
{
    return componentY_;
}

// (9) Возвращает размер по "x"
int VField2D::getSizeX() const
{
    return componentX_.getSizeX();
}

// (10) Возвращает размер по "y"
int VField2D::getSizeY() const
{
    return componentX_.getSizeY();
}

// (11) Освобождает выделенную память
void VField2D::clear()
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