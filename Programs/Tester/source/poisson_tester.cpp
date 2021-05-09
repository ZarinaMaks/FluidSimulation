////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "poisson_tester.h"

using namespace fluid;

////////// class AreaCreator2D ///////////////////////////////////////////////
// Описание : poisson_tester.h.                                             //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (1) Конструктор
AreaCreator2D::AreaCreator2D()
{
    length_ = 0;
    bSizeX_ = 0;
    bSizeY_ = 0;
    i0_ = 0;
    i1_ = 0;
    j0_ = 0;
    j1_ = 0;
}

// (4) Генерирует поле случайных единичных векторов
void AreaCreator2D::randomConfig(int sizeX, int sizeY, int lenX, int lenY)
{
    try
    {
        gradVF2D_.resize(sizeX, sizeY);
        bSizeX_ = lenX;
        bSizeY_ = lenY;
        length_ = 0.5 * sqrt(lenX * lenX + lenY * lenY);
    }
    catch (...)
    {
        clear();
        throw;
    }
    
    // Угол наклона единичного вектора
    Real angle = 0;
    
    // Проходим по всему полю, инициализируя узлы большой сетки
    for (int i = 0; i < sizeX; ++i)
    {
        for (int j = 0; j < sizeY; ++j)
        {
            // Производим запись векторов только в узлы большой сетки
            if (i % lenX == 0 && j % lenY == 0)
            {
                // Генерируем случайный угол
                angle = static_cast<Real> (rand()) / RAND_MAX;
                angle *= 2 * PI;
                
                // Записываем единичный вектор
                gradVF2D_.x().field(i, j) = std::cos(angle);
                gradVF2D_.y().field(i, j) = std::sin(angle);
            }
        }
    }
}

// (5) Создает рабочую область, как срез шума Перлина, для "field"
void AreaCreator2D::createPerlinNoiseArea(SField2D& field, Real level)
{
    // Проходим по всему полю
    for (int i = 0; i < field.getSizeX(); ++i)
    {
        for (int j = 0; j < field.getSizeY(); ++j)
        {
            field.area(i, j) = isInsideArea(i, j, level);
        }
    }
    
    // Дополнительно убираем границу массива
    deleteBorder(field);
}

// (6) Создает рабочую область, как срез шума Перлина, для "field"
void AreaCreator2D::createPerlinNoiseArea(VField2D& field, Real level)
{
    // Сначала ищем область для компоненты "x"
    createPerlinNoiseArea(field.x(), level);
    
    // Далее копируем эту область во вторую компоненту
    for (int i = 0; i < field.getSizeX(); ++i)
    {
        for (int j = 0; j < field.getSizeY(); ++j)
        {
            field.y().area(i, j) = field.x().area(i, j);
        }
    }
}

// (7) Создает п/у рабочую область, исключая границы поля "field"
void AreaCreator2D::createDefaultArea(SField2D& field)
{
    field.resetArea(true);
    deleteBorder(field);
}

// (8) Создает п/у рабочую область, исключая границы поля "field"
void AreaCreator2D::createDefaultArea(VField2D& field)
{
    createDefaultArea(field.x());
    createDefaultArea(field.y());
}

// (9) Установка значений по умолчанию
void AreaCreator2D::clear()
{
    length_ = 0;
    bSizeX_ = 0;
    bSizeY_ = 0;
    i0_ = 0;
    i1_ = 0;
    j0_ = 0;
    j1_ = 0;
    values2D_.clear();
    gradVF2D_.clear();
}

////////// private ///////////////////////////////////////////////////////////

// (1) Находит координаты соседних узловых точек
void AreaCreator2D::findNearestPoints(int i, int j)
{
    // Находим ближних слева и справа
    if (i % bSizeX_ == 0)
    {
        i0_ = i;
        i1_ = i;
    }
    else
    {
        i0_ = i - i % bSizeX_;
        i1_ = i0_ + bSizeX_;
    }
    
    // Находим ближних сверху и снизу
    if (j % bSizeY_ == 0)
    {
        j0_ = j;
        j1_ = j;
    }
    else
    {
        j0_ = j - j % bSizeY_;
        j1_ = j0_ + bSizeY_;
    }
}

// (2) Рассчитывает все скалярные произведения для соседних точек
void AreaCreator2D::computeScalarProducts(int i, int j)
{
    values2D_.fx0y0 = ((i - i0_) * (gradVF2D_.x().field(i0_, j0_)) + 
                       (j - j0_) * (gradVF2D_.y().field(i0_, j0_))) / length_;
    values2D_.fx0y1 = ((i - i0_) * (gradVF2D_.x().field(i0_, j1_)) + 
                       (j - j1_) * (gradVF2D_.y().field(i0_, j1_))) / length_;
    values2D_.fx1y0 = ((i - i1_) * (gradVF2D_.x().field(i1_, j0_)) + 
                       (j - j0_) * (gradVF2D_.y().field(i1_, j0_))) / length_;
    values2D_.fx1y1 = ((i - i1_) * (gradVF2D_.x().field(i1_, j1_)) + 
                       (j - j1_) * (gradVF2D_.y().field(i1_, j1_))) / length_;
}

// (3) Находит промежут-ое значение скалярного произведения
Real AreaCreator2D::interpolateValue(int i, int j)
{
    // Линейная интерполяция основных значений по "x"
    Real f1 = (values2D_.fx0y0 * (i1_ - i) + 
               values2D_.fx1y0 * (i - i0_)) / bSizeX_;
    Real f2 = (values2D_.fx0y1 * (i1_ - i) + 
               values2D_.fx1y1 * (i - i0_)) / bSizeX_;
    
    // Частный случай - линейная интерполяция по "j"
    if (i0_ == i1_)
    {
        f1 = values2D_.fx0y0;
        f2 = values2D_.fx0y1;
    }
    
    // Частный случай - линейная интерполяция по "i"
    if (j0_ == j1_)
    {
        return f1;
    }
    
    // Линейная интерполяция вспомогательных значений
    return (f1 * (j1_ - j) + f2 * (j - j0_)) / bSizeY_;
}

// (4) Проверяет принадлежность точки рабочей области
bool AreaCreator2D::isInsideArea(int i, int j, Real level)
{
    // Подготовка к поиску значения шума в точке (i, j)
    findNearestPoints(i, j);
    computeScalarProducts(i, j);
    
    // Если значение шума выше опред. уровня, то точка входит
    return interpolateValue(i, j) > level; 
}

// (5) Исключает границы из рабочей зоны
void AreaCreator2D::deleteBorder(SField2D& field)
{
    // Удаляем верхнюю и нижнюю
    for (int i = 0; i < field.getSizeX(); ++i)
    {
        field.area(i, 0) = false;
        field.area(i, field.getSizeY() - 1) = false;
    }
    
    // Удаляем левую и правую
    for (int j = 1; j < field.getSizeY() - 1; ++j)
    {
        field.area(0, j) = false;
        field.area(field.getSizeX() - 1, j) = false;
    }
}

////////// class PoissonChecker2D ////////////////////////////////////////////
// Описание : poisson_tester.h.                                             //
//////////////////////////////////////////////////////////////////////////////

////////// public ////////////////////////////////////////////////////////////

// (4) Возвращает величину ошибки
Real PoissonChecker2D::getError(const SField2D& f1, const SField2D& f2, 
                                Real alpha, Real betta)
{
    // Среднеквадратичная ошибка и кол-во точек рабочей зоны
    Real error = 0;
    int number = 0;
    
    // Проходим по всем точкам рабочей зоны
    for (int i = 0; i < f1.getSizeX(); ++i)
    {
        for (int j = 0; j < f1.getSizeY(); ++j)
        {
            if (f1.area(i, j) && f2.area(i, j))
            {
                ++number;
                error += std::pow(getError(f1, f2, alpha, betta, i, j), 2);
            }
        }
    }
    
    // Возвращаем среднеквадратичную ошибку
    return std::sqrt(error / number);
}

// (5) Возвращает величину ошибки
Real PoissonChecker2D::getError(const VField2D& f1, const VField2D& f2, 
                                Real alpha, Real betta)
{
    // Среднеквадратичная ошибка из двух компонент
    Real error = 0;
    
    // Сумма квадратов ошибок по каждой компоненте
    error += std::pow(getError(f1.x(), f2.x(), alpha, betta), 2);
    error += std::pow(getError(f1.y(), f2.y(), alpha, betta), 2);
    
    // Возвращаем среднеквадратичную ошибку
    return std::sqrt(error / 2);
}

////////// private ///////////////////////////////////////////////////////////

// (1) Возвращает величину ошибки для точки (i, j)
Real PoissonChecker2D::getError(const SField2D& f1, const SField2D& f2, 
                                Real alpha, Real betta, int i, int j)
{
    // Вспомогательные переменные
    Real cI = f1.field(i + 1, j) + f1.field(i - 1, j);
    Real cJ = f1.field(i, j + 1) + f1.field(i, j - 1);
    
    // Вычисляем очередное приближение в точке (i, j)
    return f1.field(i, j) - (cI + cJ + alpha * f2.field(i, j)) / betta;
}