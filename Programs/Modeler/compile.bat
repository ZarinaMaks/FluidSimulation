:: Компилирование прошраммы моделирования течения жидкости
cd %cd%
set pathLib=..\..\Libraries
set pathGraph=%pathLib%\GraphLib
set pathObj=%pathGraph%\objects

:: Используем компилятор "g++"
g++ -c source\modeler2d.cpp -I.\headers -I%pathGraph%\headers -I%pathLib%\SFML\include
g++ -c source\modeler.cpp -I.\headers -I%pathGraph%\headers -I%pathLib%\SFML\include
g++ modeler.o modeler2d.o %pathObj%\components2d.o %pathObj%\graph2d.o -o modeler ^
-L%pathLib%\SFML\lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

:: Объектные файлы уничтожаем, исполняемый помещаем в папку "binary"
del /Q /F .\*.o
move /Y .\modeler.exe .\binary\