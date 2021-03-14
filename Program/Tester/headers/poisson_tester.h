#ifndef POISSON_TESTER_H
#define POISSON_TESTER_H

////////// fluidlib //////////////////////////////////////////////////////////
// Авторы   : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
//////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include "fluidlib2d.h"

namespace fluid
{
    // Число Пи (15 знаков)
    const Real PI = 3.141592653589793;
    
    ////////// class AreaCreator2D ///////////////////////////////////////////
    // Для заданного скалярного или векторного 2D поля задает на выбор один //
    // из возможных вариантов рабочей зоны:                                 //
    // 1) Прямоугольная зона, которая включает все элементы массива, кроме  //
    //    тех, что находятся на его границах.                               //
    // 2) Произвольная зона, которая так же не включает границ и задается   //
    //    срезом шума Перлина.                                              //
    //////////////////////////////////////////////////////////////////////////
    
    class AreaCreator2D
    {
        private :
            
            VField2D gradVF2D_; // Поле случайных единичных векторов
            Real     length_;   // Нормирующий коэффициент
            int      bSizeX_;   // Размер по "x" блока
            int      bSizeY_;   // Размер по "y" блока
            
            Values2D values2D_; // Значения в вершинах п/у (для интерполяции)
            int      i0_, i1_;  // Координаты "x" соседних узловых точек
            int      j0_, j1_;  // Координаты "y" соседних узловых точек
            
        public :
            
            // (1) Конструктор
            AreaCreator2D();
            
            // (2) Конструктор копирования
            AreaCreator2D(const AreaCreator2D& creator) = delete;
            
            // (3) Перегрузка оператора присваивания
            AreaCreator2D& operator=(const AreaCreator2D& creator) = delete;
            
            // (4) Генерирует поле случайных единичных векторов
            void randomConfig(int sizeX, int sizeY, int lenX, int lenY);
            
            // (5) Создает рабочую область, как срез шума Перлина, для "field"
            void createPerlinNoiseArea(SField2D& field, Real level);
            
            // (6) Создает рабочую область, как срез шума Перлина, для "field"
            void createPerlinNoiseArea(VField2D& field, Real level);
            
            // (7) Создает п/у рабочую область, исключая границы поля "field"
            void createDefaultArea(SField2D& field);
            
            // (8) Создает п/у рабочую область, исключая границы поля "field"
            void createDefaultArea(VField2D& field);
            
            // (9) Установка значений по умолчанию
            void clear();
            
            // (10) Деструктор
            ~AreaCreator2D() = default;
        
        private :
            
            // (1) Находит координаты соседних узловых точек
            void findNearestPoints(int i, int j);
            
            // (2) Рассчитывает все скалярные произведения для соседних точек
            void computeScalarProducts(int i, int j);
            
            // (3) Находит промежут-ое значение скалярного произведения
            Real interpolateValue(int i, int j);
            
            // (4) Проверяет принадлежность точки рабочей области
            bool isInsideArea(int i, int j, Real level);
            
            // (5) Исключает границы из рабочей зоны
            void deleteBorder(SField2D& field);
    };
    
    ////////// class PoissonChecker2D ////////////////////////////////////////
    // Проверяет корректность значений поля скалярных или векторных величин //
    // после решения ур-я Пуассона методом итераций Якоби.                  //
    // 1) Находит величину отклонения решения от истины.                    //
    // 2) Проверяет, не изменились ли граничные величины и те значения,     //
    //    которые не должны были меняться при работе алгоритма.             //
    //////////////////////////////////////////////////////////////////////////
    
    class PoissonChecker2D
    {
        public :
            
            // (1) Конструктор
            PoissonChecker2D() = default;
            
            // (2) Конструктор копирования
            PoissonChecker2D(const PoissonChecker2D& checker) = delete;
            
            // (3) Перегрузка оператора присваивания
            PoissonChecker2D& operator=(const PoissonChecker2D& 
                                        checker) = delete;
            
            // (4) Возвращает величину ошибки
            Real getError(const SField2D& f1, const SField2D& f2, 
                          Real alpha, Real betta);
            
            // (5) Возвращает величину ошибки
            Real getError(const VField2D& f1, const VField2D& f2, 
                          Real alpha, Real betta);
            
            // (6) Деструктор
            ~PoissonChecker2D() = default;
            
        private :
            
            // (1) Возвращает величину ошибки для точки (i, j)
            Real getError(const SField2D& f1, const SField2D& f2, 
                          Real alpha, Real betta, int i, int j);
    };
    
}

#endif
