:: Компилирование прошраммы - тестировщика библиотеки "fluidlib"
cd %cd%
set libPath=..\..\Libraries\FluidLib
set libObj=%libPath%\objects

:: Используем компилятор "g++"
g++ -c source\poisson_tester.cpp -I.\headers -I%libPath%\headers
g++ -c source\poisson.cpp -I.\headers -I%libPath%\headers
g++ %libObj%\exception.o %libObj%\basic.o %libObj%\components2d.o ^
    %libObj%\tools2d.o %libObj%\fluidlib2d.o poisson_tester.o ^
    poisson.o -o poisson

:: Объектные файлы уничтожаем, исполняемый помещаем в папку "binary"
del /Q /F .\*.o
move /Y .\poisson.exe .\binary\