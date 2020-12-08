////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "fluidlib.h"

using namespace fluid;

/*
////////// struct Vector /////////////////////////////////////////////////////
// Описание : fluidlib.h.                                                   //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор (обнуляет поля)
Vector::Vector()
{
    x_ = 0;
    y_ = 0;
    z_ = 0;
}

// (2) Конструктор копирования
Vector::Vector(const Vector& vector)
{
    *this = vector;
}

// (3) Конструктор (задает составляющие вектора)
Vector::Vector(Real& x, Real& y, Real& z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

// (3) Перегрузка оператора присваивания
Vector& Vector::operator=(const Vector& vector)
{
    if (this != &vector)
    {
        x_ = vector.x_;
        y_ = vector.y_;
        z_ = vector.z_;
    }
    return *this;
}

// (4) Доступ к составляющей "x"
Real& Vector::x()
{
    return x_;
}

// (5) Доступ к составляющей "y"
Real& Vector::y()
{
    return y_;
}

// (6) Доступ к составляющей "z"
Real& Vector::z()
{
    return z_;
}

// (7) Константный доступ к составляющей "x"
const Real& Vector::x() const
{
    return x_;
}

// (8) Константный доступ к составляющей "y"
const Real& Vector::y() const
{
    return y_;
}

// (9) Константный доступ к составляющей "z"
const Real& Vector::z() const
{
    return z_;
}

// (4) Обнуляет поля
void Vector::clear()
{
    x_ = 0;
    y_ = 0;
    z_ = 0;
}

// (5) Деструктор
Vector::~Vector()
{
    clear();
}
*/

////////// bool inRangeSizeX/Y/Z /////////////////////////////////////////////
// Описание : fluidlib.h.                                                   //
//////////////////////////////////////////////////////////////////////////////

bool inRangeSizeX(const int& sizeX)
{
    return sizeX >= MIN_SIZE_X && sizeX <= MAX_SIZE_X;
}

bool inRangeSizeY(const int& sizeY)
{
    return sizeY >= MIN_SIZE_Y && sizeY <= MAX_SIZE_Y;
}

bool inRangeSizeZ(const int& sizeZ)
{
    return sizeZ >= MIN_SIZE_Z && sizeZ <= MAX_SIZE_Z;
}

////////// class ScalarField /////////////////////////////////////////////////
// Описание : fluidlib.h.                                                   //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор (обнуляет поля класса)
ScalarField::ScalarField()
{
    points_ = nullptr;
    sizeX_  = 0;
    sizeY_  = 0;
    sizeZ_  = 0;
}

// (2) Конструктор (Сразу задает размер поля)
ScalarField::ScalarField(int sizeX, int sizeY, int sizeZ)
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
ScalarField::ScalarField(const ScalarField& field)
{
    try
    {
        *this = field;
    }
    catch (...)
    {
        // Предотвращаем выброс исключения
    }
}

// (4) Перегрузка оператора присваивания
ScalarField& ScalarField::operator=(const ScalarField& field)
{
    // Самоприсваивание
    if (this != &field)
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
    return *this;
}

// (5) Изменяет размер поля, уничтожая всю информацию
void ScalarField::resize(int sizeX, int sizeY, int sizeZ)
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
Real& ScalarField::operator()(int x, int y, int z)
{
    // Выброс исключения, если был выход за границы
    if (!isInRange(x, y, z))
    {
        throw err::FluidException(1);
    }
    return points_[x][y][z];
}

// (7) Перегрузка оператора () (const случай)
const Real& ScalarField::operator()(int x, int y, int z) const
{
    return this->operator()(x,y,z);
}

// (8) Проверка на выход за границы
bool ScalarField::isInRange(int x, int y, int z) const
{
    // Если значения аргументов корректны
    bool isInRangeX = x < sizeX_ && x >= 0;
    bool isInRangeY = y < sizeY_ && y >= 0;
    bool isInRangeZ = z < sizeZ_ && z >= 0;
        
    return isInRangeX && isInRangeY && isInRangeZ;
}

// (9) Возвращает размер по "X"
int ScalarField::getSizeX() const
{
    return sizeX_;
}

// (10) Возвращает размер по "Y"
int ScalarField::getSizeY() const
{
    return sizeY_;
}

// (11) Возвращает размер по "Z"
int ScalarField::getSizeZ() const
{
    return sizeZ_;
}

// (12) Перегрузка оператора "+="
ScalarField& ScalarField::operator+=(const ScalarField& field)
{
    // Совпадают ли размеры полей?
    bool haveMatchX = (sizeX_ == field.getSizeX());
    bool haveMatchY = (sizeY_ == field.getSizeY());
    bool haveMatchZ = (sizeZ_ == field.getSizeZ());
    
    // Добавить, если совпадают
    if (haveMatchX && haveMatchY && haveMatchZ)
    {
        for (int i = 0; i < sizeX_; ++i)
        {
            for (int j = 0; j < sizeY_; ++j)
            {
                for (int k = 0; k < sizeZ_; ++k)
                {
                    points_[i][j][k] += field.points_[i][j][k];
                }
            }
        }
    }
    else
    {
        throw err::FluidException(2);
    }
    return *this;
}

// (13) Перегрузка оператора "-="
ScalarField& ScalarField::operator-=(const ScalarField& field)
{
    // Совпадают ли размеры полей?
    bool haveMatchX = (sizeX_ == field.getSizeX());
    bool haveMatchY = (sizeY_ == field.getSizeY());
    bool haveMatchZ = (sizeZ_ == field.getSizeZ());
    
    // Добавить, если совпадают
    if (haveMatchX && haveMatchY && haveMatchZ)
    {
        for (int i = 0; i < sizeX_; ++i)
        {
            for (int j = 0; j < sizeY_; ++j)
            {
                for (int k = 0; k < sizeZ_; ++k)
                {
                    points_[i][j][k] -= field.points_[i][j][k];
                }
            }
        }
    }
    else
    {
        throw err::FluidException(2);
    }
    return *this;
}

// (14) Освобождает выделенную память
void ScalarField::clear()
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

// (15) Деструктор
ScalarField::~ScalarField()
{
    clear();
}

////////// class VectorField /////////////////////////////////////////////////
// Описание : fluidlib.h.                                                   //
//////////////////////////////////////////////////////////////////////////////// (2) Конструктор (Сразу задает размер поля)VectorField::VectorField(int sizeX, int sizeY, int sizeZ)
{
    try
    {
        resize(sizeX, sizeY, sizeZ);
    }
    catch (...)
    {
        // Предотвращаем выброс исключения
    }
}// (3) Конструктор копированияVectorField::VectorField(const VectorField& field)
{
    try
    {
        *this = field;
    }
    catch (...)
    {
        // Предотвращаем выброс исключения
    }
}// (5) Изменяет размер поля, уничтожая всю информациюvoid VectorField::resize(int sizeX, int sizeY, int sizeZ)
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
}// (6) Доступ по ссылке к скалярному полю "X"ScalarField& VectorField::x()
{
    return componentX_;
}// (7) Доступ по ссылке к скалярному полю "Y"ScalarField& VectorField::y()
{
    return componentY_;
}// (8) Доступ по ссылке к скалярному полю "Z"ScalarField& VectorField::z()
{
    return componentZ_;
}// (9) Доступ по "const" ссылке к скалярному полю "X"const ScalarField& VectorField::x() const
{
    return componentX_;
}// (10) Доступ по "const" ссылке к скалярному полю "Y"const ScalarField& VectorField::y() const
{
    return componentY_;
}// (11) Доступ по "const" ссылке к скалярному полю "Z"const ScalarField& VectorField::z() const
{
    return componentZ_;
}// (12) Возвращает размер по "X"int VectorField::getSizeX() const
{
    return componentX_.getSizeX();
}// (13) Возвращает размер по "Y"int VectorField::getSizeY() const
{
    return componentY_.getSizeY();
}// (14) Возвращает размер по "Z"int VectorField::getSizeZ() const
{
    return componentZ_.getSizeZ();
}// (15) Перегрузка оператора "+="VectorField& VectorField::operator+=(const VectorField& field)
{
    componentX_ += field.componentX_;
    componentY_ += field.componentY_;
    componentZ_ += field.componentZ_;
    return *this;
}// (16) Перегрузка оператора "-="VectorField& VectorField::operator-=(const VectorField& field)
{
    componentX_ -= field.componentX_;
    componentY_ -= field.componentY_;
    componentZ_ -= field.componentZ_;
    return *this;
}// (17) Освобождает выделенную памятьvoid VectorField::clear()
{
    componentX_.clear();
    componentY_.clear();
    componentZ_.clear();
}

////////// class Operator ////////////////////////////////////////////////////
// Описание : fluidlib.h.                                                   //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (2) Конструктор (Сразу задает размер вспомогательных полей)
Operator::Operator(int sizeX, int sizeY, int sizeZ)
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
Operator::Operator(const Operator& newOperator)
{
    try
    {
        *this = newOperator;
    }
    catch (...)
    {
        // Предотвращаем выброс исключения
    }
}

// (5) Устанавливается размер вспомогательных полей
void Operator::resize(int sizeX, int sizeY, int sizeZ)
{
    try
    {
        tempSF_.resize(sizeX, sizeY, sizeZ);
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (6) Градиент (Возвращает по ссылке векторное поле)
void Operator::grad(const ScalarField& inField, VectorField& outField)
{
    derX(inField, outField.x());
    derY(inField, outField.y());
    derZ(inField, outField.z());
}

// (7) Дивергенция (Возвращает по ссылке скалярное поле)
void Operator::div(const VectorField& inField, ScalarField& outField)
{
    derX(inField.x(), outField);
    derY(inField.y(), tempSF_);
    outField += tempSF_;
    derZ(inField.z(), tempSF_);
    outField += tempSF_;
}

// (8) Частная производная функции по "x" всюду
void Operator::derX(const ScalarField& inField, ScalarField& outField)
{
    for (int i = 0; i < outField.getSizeX(); ++i)
    {
        for (int j = 0; j < outField.getSizeY(); ++j)
        {
            for (int k = 0; k < outField.getSizeZ(); ++k)
            {
                outField(i, j, k) = derX(inField, i, j, k);
            }
        }
    }
}

// (9) Частная производная функции по "y" всюду
void Operator::derY(const ScalarField& inField, ScalarField& outField)
{
    for (int i = 0; i < outField.getSizeX(); ++i)
    {
        for (int j = 0; j < outField.getSizeY(); ++j)
        {
            for (int k = 0; k < outField.getSizeZ(); ++k)
            {
                outField(i, j, k) = derY(inField, i, j, k);
            }
        }
    }
}

// (10) Частная производная функции по "z" всюду
void Operator::derZ(const ScalarField& inField, ScalarField& outField)
{
    for (int i = 0; i < outField.getSizeX(); ++i)
    {
        for (int j = 0; j < outField.getSizeY(); ++j)
        {
            for (int k = 0; k < outField.getSizeZ(); ++k)
            {
                outField(i, j, k) = derZ(inField, i, j, k);
            }
        }
    }
}

// (11) Освобождает выделенную память
void Operator::clear()
{
    tempSF_.clear();
}

////////// private ///////////////////////////////////////////////////////////

// (1) Частная производная функции по "x" в точке
Real Operator::derX(const ScalarField& inField, int& x, int& y, int& z)
{
    if (inField.getSizeX() <= 1)
    {
        return 0.0;
    }
    else
    if (x == 0)
    {
        return (inField(x + 1, y, z) - inField(x, y, z)) / DX;
    }
    else
    if (x == inField.getSizeX())
    {
        return (inField(x, y, z) - inField(x - 1, y, z)) / DX;
    }
    else
    {
        return (inField(x - 1, y, z) - inField(x + 1, y, z)) / (2 * DX);
    }
}

// (2) Частная производная функции по "y"  в точке
Real Operator::derY(const ScalarField& inField, int& x, int& y, int& z)
{
    if (inField.getSizeY() <= 1)
    {
        return 0.0;
    }
    else
    if (y == 0)
    {
        return (inField(x, y + 1, z) - inField(x, y, z)) / DY;
    }
    else
    if (y == inField.getSizeY())
    {
        return (inField(x, y, z) - inField(x, y - 1, z)) / DY;
    }
    else
    {
        return (inField(x, y - 1, z) - inField(x, y + 1, z)) / (2 * DY);
    }
}

// (3) Частная производная функции по "z"  в точке
Real Operator::derZ(const ScalarField& inField, int& x, int& y, int& z)
{
    if (inField.getSizeZ() <= 1)
    {
        return 0.0;
    }
    else
    if (z == 0)
    {
        return (inField(x, y, z + 1) - inField(x, y, z)) / DZ;
    }
    else
    if (z == inField.getSizeZ())
    {
        return (inField(x, y, z) - inField(x, y, z - 1)) / DZ;
    }
    else
    {
        return (inField(x, y, z - 1) - inField(x, y, z + 1)) / (2 * DZ);
    }
}

////////// class Poisson /////////////////////////////////////////////////////
// Описание : fluidlib.h.                                                   //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (2) Конструктор (Сразу задает размер вспомогательных полей)
Poisson::Poisson(int sizeX, int sizeY, int sizeZ)
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
Poisson::Poisson(const Poisson& newPoisson)
{
    try
    {
        *this = newPoisson;
    }
    catch (...)
    {
        // Предотвращаем выброс исключения
    }
}

// (5) Устанавливается размер вспомогательных полей
void Poisson::resize(int sizeX, int sizeY, int sizeZ)
{
    try
    {
        curStep_.resize(sizeX, sizeY, sizeZ);
    }
    catch (...)
    {
        clear();
        throw;
    }
}

// (6) Решает уравнение Пуассона; "free" - свободный член (Scalar)
void Poisson::solve(ScalarField& field, const ScalarField& free, 
                    Real alpha, Real betta)
{
    for (int i = 0; i < JACOBI_STEP_NUMBER; ++i)
    {
        step(field, free, alpha, betta);
    }
}

// (7) Решает уравнение Пуассона; "free" - свободный член (Vector)
void Poisson::solve(VectorField& field, const VectorField& free, 
                    Real alpha, Real betta)
{
    solve(field.x(), free.x(), alpha, betta);
    solve(field.y(), free.y(), alpha, betta);
    solve(field.z(), free.z(), alpha, betta);
}

// (11) Освобождает выделенную память
void Poisson::clear()
{
    curStep_.clear();
}

////////// private ///////////////////////////////////////////////////////////

// (1) Возвращает очередное приближение в точке (i, j, k)
Real Poisson::step(const ScalarField& field, const ScalarField& free, 
                   Real alpha, Real betta, int i, int j, int k)
{
    Real cI = 0;
    Real cJ = 0;
    Real cK = 0;
    
    // Подбираем значения по "X", если его нет, доопределяем
    if (!field.isInRange(i + 1, j, k))
    {
        cI += field(i, j, k);
    }
    else
    {
        cI += field(i + 1, j, k);
    }
    if (!field.isInRange(i - 1, j, k))
    {
        cI += field(i, j, k);
    }
    else
    {
        cI += field(i - 1, j, k);
    }
    
    // Подбираем значения по "Y", если его нет, доопределяем
    if (!field.isInRange(i, j + 1, k))
    {
        cJ += field(i, j, k);
    }
    else
    {
        cJ += field(i, j + 1, k);
    }
    if (!field.isInRange(i, j - 1, k))
    {
        cJ += field(i, j, k);
    }
    else
    {
        cJ += field(i, j - 1, k);
    }
    
    // Подбираем значения по "Z", если его нет, доопределяем
    if (!field.isInRange(i, j, k + 1))
    {
        cK += field(i, j, k);
    }
    else
    {
        cK += field(i, j, k + 1);
    }
    if (!field.isInRange(i, j, k - 1))
    {
        cK += field(i, j, k);
    }
    else
    {
        cK += field(i, j, k - 1);
    }
    
    // Вычисляем очередное приближение в точке (i, j, k)
    return (cI + cJ + cK + alpha * free(i, j, k)) / betta;
}

// (2) Возвращает очередное приближение на всем поле
void Poisson::step(ScalarField& field, const ScalarField& free, 
                   Real alpha, Real betta)
{
    for (int i = 0; i < field.getSizeX(); ++i)
    {
        for (int j = 0; j < field.getSizeY(); ++j)
        {
            for (int k = 0; k < field.getSizeZ(); ++k)
            {
                curStep_(i, j, k) = step(field, free, alpha, betta, i, j, k);
            }
        }
    }
    field = curStep_;
}