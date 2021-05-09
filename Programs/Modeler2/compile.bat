:: Компилирование прошраммы моделирования течения жидкости
cd %cd%
set pathLib=..\..\Libraries
set pathFluid=%pathLib%\FluidLib
set pathObj=%pathFluid%\objects

:: Используем компилятор "g++"
g++ -c source\modeler2d.cpp -I.\headers -I%pathFluid%\headers -I%pathLib%\SFML\include
g++ -c source\modeler.cpp -I.\headers -I%pathFluid%\headers -I%pathLib%\SFML\include
g++ modeler.o modeler2d.o %pathObj%\exception.o %pathObj%\basic.o %pathObj%\components2d.o ^
    %pathObj%\tools2d.o %pathObj%\fluids2d.o %pathObj%\borders2d.o %pathObj%\fluidlib2d.o ^
    -o modeler -L%pathLib%\SFML\lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

:: Объектные файлы уничтожаем, исполняемый помещаем в папку "binary"
del /Q /F .\*.o
move /Y .\modeler.exe .\binary\