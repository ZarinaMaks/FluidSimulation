////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "componentlib3d.h"

using namespace fluid;

////////// class ScalarField3D ///////////////////////////////////////////////
// Описание : componentlib3d.h.                                             //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор (обнуляет поля класса)
ScalarField3D::ScalarField3D()
{
    points_ = nullptr;
    sizeX_  = 0;
    sizeY_  = 0;
    sizeZ_  = 0;
}

// (2) Конструктор (Сразу задает размер поля)
ScalarField3D::ScalarField3D(int sizeX, int sizeY, int sizeZ)
{
    try
    {
        points_ = nullptr;
        sizeX_  = 0;
        sizeY_  = 0;
        sizeZ_  = 0;
        resize(sizeX, sizeY, sizeZ);
    }
    catch (...)
    {
        // Предотвращаем выброс исключения
    }
}

// (3) Конструктор копирования
ScalarField3D::ScalarField3D(const ScalarField3D& field)
{
    *this = field;
}

// (4) Перегрузка оператора присваивания
ScalarField3D& ScalarField3D::operator=(const ScalarField3D& field)
{
    // Самоприсваивание
    if (this != &field)
    {
        try
        {
            // Меняем размер
            resize(field.getSizeX(), field.getSizeY(), field.getSizeZ());
            
            // Копируем данные
            for (int i = 0; i < sizeX_; ++i)
            {
                for (int j = 0; j < sizeY_; ++j)
                {
                    for (int k = 0; k < sizeZ_; ++k)
                    {
                        points_[i][j][k] = field.points_[i][j][k];
                    }
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
void ScalarField3D::resize(int sizeX, int sizeY, int sizeZ)
{
    // Если размеры массивов отличаются
    bool hasDiff   = sizeX_ != sizeX || sizeY_ != sizeY || sizeZ_ != sizeZ;
    
    // Если значения аргументов корректны
    bool isInRange = inRangeSizeX(sizeX) && inRangeSizeY(sizeY) 
                     && inRangeSizeZ(sizeZ);
    
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
            sizeZ_ = sizeZ;
            
            // Выделение новой памяти
            points_ = new Real**[sizeX_];
            for (int i = 0; i < sizeX_; ++i)
            {
                points_[i] = new Real*[sizeY_];
                for (int j = 0; j < sizeY_; ++j)
                {
                    points_[i][j] = new Real[sizeZ_];
                }
            }
        }
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (6) Перегрузка оператора ()
Real& ScalarField3D::operator()(int x, int y, int z)
{
    // Выброс исключения, если был выход за границы
    if (!isInRange(x, y, z))
    {
        throw err::FluidException(1);
    }
    return points_[x][y][z];
}

// (7) Перегрузка оператора () (const случай)
const Real& ScalarField3D::operator()(int x, int y, int z) const
{
    // Выброс исключения, если был выход за границы
    if (!isInRange(x, y, z))
    {
        throw err::FluidException(1);
    }
    return points_[x][y][z];
}

// (8) Проверка на выход за границы
bool ScalarField3D::isInRange(int x, int y, int z) const
{
    // Если значения аргументов корректны
    bool isInRangeX = x < sizeX_ && x >= 0;
    bool isInRangeY = y < sizeY_ && y >= 0;
    bool isInRangeZ = z < sizeZ_ && z >= 0;
    
    return isInRangeX && isInRangeY && isInRangeZ;
}

// (9) Возвращает размер по "x"
int ScalarField3D::getSizeX() const
{
    return sizeX_;
}

// (10) Возвращает размер по "y"
int ScalarField3D::getSizeY() const
{
    return sizeY_;
}

// (11) Возвращает размер по "z"
int ScalarField3D::getSizeZ() const
{
    return sizeZ_;
}

// (12) Освобождает выделенную память
void ScalarField3D::clear()
{
    // Освобождение памяти
    if (points_ != nullptr)
    {
        for (int i = 0; i < sizeX_; ++i)
        {
            if (points_[i] != nullptr)
            {
                for (int j = 0; j < sizeY_; ++j)
                {
                    if (points_[i][j] != nullptr)
                    {
                        delete[] points_[i][j];
                    }
                }
                delete[] points_[i];
            }
        }
        delete[] points_;
        points_ = nullptr;
    }
    
    // Обнуление переменных
    sizeX_ = 0;
    sizeY_ = 0;
    sizeZ_ = 0;
}

// (13) Деструктор
ScalarField3D::~ScalarField3D()
{
    clear();
}

////////// class VectorField3D ///////////////////////////////////////////////
// Описание : componentlib3d.h.                                             //
//////////////////////////////////////////////////////////////////////////////

// (2) Конструктор (Сразу задает размер поля)
VectorField3D::VectorField3D(int sizeX, int sizeY, int sizeZ)
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

// (3) Конструктор копирования
VectorField3D::VectorField3D(const VectorField3D& field)
{
    *this = field;
}

// (5) Изменяет размер поля, уничтожая всю информацию
void VectorField3D::resize(int sizeX, int sizeY, int sizeZ)
{
    try
    {
        componentX_.resize(sizeX, sizeY, sizeZ);
        componentY_.resize(sizeX, sizeY, sizeZ);
        componentZ_.resize(sizeX, sizeY, sizeZ);
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (6) Доступ по ссылке к скалярному полю "x"
ScalarField3D& VectorField3D::x()
{
    return componentX_;
}

// (7) Доступ по ссылке к скалярному полю "y"
ScalarField3D& VectorField3D::y()
{
    return componentY_;
}

// (8) Доступ по ссылке к скалярному полю "z"
ScalarField3D& VectorField3D::z()
{
    return componentZ_;
}

// (9) Доступ по "const" ссылке к скалярному полю "x"
const ScalarField3D& VectorField3D::x() const
{
    return componentX_;
}

// (10) Доступ по "const" ссылке к скалярному полю "y"
const ScalarField3D& VectorField3D::y() const
{
    return componentY_;
}

// (11) Доступ по "const" ссылке к скалярному полю "z"
const ScalarField3D& VectorField3D::z() const
{
    return componentZ_;
}

// (12) Возвращает размер по "x"
int VectorField3D::getSizeX() const
{
    return componentX_.getSizeX();
}

// (13) Возвращает размер по "y"
int VectorField3D::getSizeY() const
{
    return componentX_.getSizeY();
}

// (14) Возвращает размер по "z"
int VectorField3D::getSizeZ() const
{
    return componentX_.getSizeZ();
}

// (15) Освобождает выделенную память
void VectorField3D::clear()
{
    componentX_.clear();
    componentY_.clear();
    componentZ_.clear();
}

////////// struct Values3D ///////////////////////////////////////////////////
// Описание : componentlib3d.h.                                             //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор (обнуляет поля)
Values3D::Values3D()
{
    fx0y0z0 = 0;
    fx0y0z1 = 0;
    fx0y1z0 = 0;
    fx0y1z1 = 0;
    fx1y0z0 = 0;
    fx1y0z1 = 0;
    fx1y1z0 = 0;
    fx1y1z1 = 0;
}

// (4) Обнуляет поля
void Values3D::clear()
{
    fx0y0z0 = 0;
    fx0y0z1 = 0;
    fx0y1z0 = 0;
    fx0y1z1 = 0;
    fx1y0z0 = 0;
    fx1y0z1 = 0;
    fx1y1z0 = 0;
    fx1y1z1 = 0;
}

////////// class WorkZone3D //////////////////////////////////////////////////
// Описание : componentlib3d.h.                                             //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор (обнуляет поля класса)
WorkZone3D::WorkZone3D()
{
    points_ = nullptr;
    sizeX_  = 0;
    sizeY_  = 0;
    sizeZ_  = 0;
}

// (2) Конструктор (Сразу задает размер поля)
WorkZone3D::WorkZone3D(int sizeX, int sizeY, int sizeZ)
{
    try
    {
        points_ = nullptr;
        sizeX_  = 0;
        sizeY_  = 0;
        sizeZ_  = 0;
        resize(sizeX, sizeY, sizeZ);
    }
    catch (...)
    {
        // Предотвращаем выброс исключения
    }
}

// (3) Конструктор копирования
WorkZone3D::WorkZone3D(const WorkZone3D& field)
{
    *this = field;
}

// (4) Перегрузка оператора присваивания
WorkZone3D& WorkZone3D::operator=(const WorkZone3D& field)
{
    // Самоприсваивание
    if (this != &field)
    {
        try
        {
            // Меняем размер
            resize(field.getSizeX(), field.getSizeY(), field.getSizeZ());
            
            // Копируем данные
            for (int i = 0; i < sizeX_; ++i)
            {
                for (int j = 0; j < sizeY_; ++j)
                {
                    for (int k = 0; k < sizeZ_; ++k)
                    {
                        points_[i][j][k] = field.points_[i][j][k];
                    }
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
void WorkZone3D::resize(int sizeX, int sizeY, int sizeZ)
{
    // Если размеры массивов отличаются
    bool hasDiff   = sizeX_ != sizeX || sizeY_ != sizeY || sizeZ_ != sizeZ;
    
    // Если значения аргументов корректны
    bool isInRange = inRangeSizeX(sizeX) && inRangeSizeY(sizeY) 
                     && inRangeSizeZ(sizeZ);
    
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
            sizeZ_ = sizeZ;
            
            // Выделение новой памяти
            points_ = new bool**[sizeX_];
            for (int i = 0; i < sizeX_; ++i)
            {
                points_[i] = new bool*[sizeY_];
                for (int j = 0; j < sizeY_; ++j)
                {
                    points_[i][j] = new bool[sizeZ_];
                }
            }
        }
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (6) Перегрузка оператора ()
bool& WorkZone3D::operator()(int x, int y, int z)
{
    // Выброс исключения, если был выход за границы
    if (!isInRange(x, y, z))
    {
        throw err::FluidException(1);
    }
    return points_[x][y][z];
}

// (7) Перегрузка оператора () (const случай)
const bool& WorkZone3D::operator()(int x, int y, int z) const
{
    // Выброс исключения, если был выход за границы
    if (!isInRange(x, y, z))
    {
        throw err::FluidException(1);
    }
    return points_[x][y][z];
}

// (8) Проверка на выход за границы
bool WorkZone3D::isInRange(int x, int y, int z) const
{
    // Если значения аргументов корректны
    bool isInRangeX = x < sizeX_ && x >= 0;
    bool isInRangeY = y < sizeY_ && y >= 0;
    bool isInRangeZ = z < sizeZ_ && z >= 0;
    
    return isInRangeX && isInRangeY && isInRangeZ;
}

// (9) Возвращает размер по "x"
int WorkZone3D::getSizeX() const
{
    return sizeX_;
}

// (10) Возвращает размер по "y"
int WorkZone3D::getSizeY() const
{
    return sizeY_;
}

// (11) Возвращает размер по "z"
int WorkZone3D::getSizeZ() const
{
    return sizeZ_;
}

// (12) Освобождает выделенную память
void WorkZone3D::clear()
{
    // Освобождение памяти
    if (points_ != nullptr)
    {
        for (int i = 0; i < sizeX_; ++i)
        {
            if (points_[i] != nullptr)
            {
                for (int j = 0; j < sizeY_; ++j)
                {
                    if (points_[i][j] != nullptr)
                    {
                        delete[] points_[i][j];
                    }
                }
                delete[] points_[i];
            }
        }
        delete[] points_;
        points_ = nullptr;
    }
    
    // Обнуление переменных
    sizeX_ = 0;
    sizeY_ = 0;
    sizeZ_ = 0;
}

// (13) Деструктор
WorkZone3D::~WorkZone3D()
{
    clear();
}