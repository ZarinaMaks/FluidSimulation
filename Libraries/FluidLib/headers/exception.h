#ifndef EXCEPTION_H
#define EXCEPTION_H

////////// fluidlib //////////////////////////////////////////////////////////
// Автор    : Баталов Семен, Зарина Максудова, Дарья Белоусова              //
// Дата     : ??.??.2020                                                    //
// Описание : Здесь представлены инструменты для обработки исключительных   //
//            ситуаций в модулях моделирования течения жидкости.            //
//////////////////////////////////////////////////////////////////////////////

#include <exception>

namespace fluid
{
    ////////// class Exception ///////////////////////////////////////////////
    // Дочерний класс, унаследованный от "std::exception". Содежит в себе   //
    // код ошибки "errCode_" (0 - отсутствие ошибок).                       //
    //////////////////////////////////////////////////////////////////////////
    
    class Exception : public std::exception
    {
        private :
            
            int errCode_;   // Код ошибки
            
        public :
            
            // (1) Конструктор (обнуляет поле)
            Exception();
            
            // (2) Конструктор (инициализирует поле)
            Exception(int newErrCode);
	    
            // (3) Конструктор копирования
            Exception(const Exception& exeption) = default;
	    
            // (4) Перегрузка оператора присваивания
            Exception& operator=(const Exception& exeption) = default;
            
            // (5) Виртуальный метод возврата сообщения об ошибке
            virtual const char* what() const noexcept = 0;
            
            // (5) Возвращает код ошибки
            int error() const;
            
            // (6) Деструктор
            virtual ~Exception() = default;
    };
    
    ////////// class FluidException //////////////////////////////////////////
    // Дочерний класс, унаследованный от "fluid::Exception". Отвечает за    //
    // ошибки в пространстве имен "fluid".                                  //
    //////////////////////////////////////////////////////////////////////////
    
    class FluidException : public Exception
    {
        private:
            
            //...
            
        public :
            
            // (1) Конструктор (обнуляет поле)
            FluidException() = default;
            
            // (2) Конструктор (инициализирует поле)
            FluidException(int newErrCode) : Exception(newErrCode) {};
            
            // (3) Конструктор копирования
            FluidException(const FluidException& exeption) = default;
            
            // (4) Перегрузка оператора присваивания
            FluidException& operator=(const FluidException& exeption) = default;
            
            // (5) Виртуальный метод возврата сообщения об ошибке
            virtual const char* what() const noexcept;
            
            // (6) Деструктор
            virtual ~FluidException() = default;
    };
    
    ////////// class FioException ////////////////////////////////////////////
    // Дочерний класс, унаследованный от "fluid::Exception". Отвечает за    //
    // ошибки в пространстве имен "fio".                                    //
    //////////////////////////////////////////////////////////////////////////
    
    class FioException : public Exception
    {
        private:
            
            //...
            
        public :
            
            // (1) Конструктор (обнуляет поле)
            FioException() = default;
            
            // (2) Конструктор (инициализирует поле)
            FioException(int newErrCode) : Exception(newErrCode) {};
            
            // (3) Конструктор копирования
            FioException(const FioException& exeption) = default;
            
            // (4) Перегрузка оператора присваивания
            FioException& operator=(const FioException& exeption) = default;
            
            // (5) Виртуальный метод возврата сообщения об ошибке
            virtual const char* what() const noexcept;
            
            // (6) Деструктор
            virtual ~FioException() = default;
    };
}

#endif