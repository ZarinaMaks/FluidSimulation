:: Подготовка путей
cd %cd%
set libPath=..\..\Libraries\SFML

:: Компилируем библиотеку
g++ -c source\components2d.cpp -I.\headers -I%libPath%\include
g++ -c source\graph2d.cpp -I.\headers -I%libPath%\include

:: Перемещаем объектные файлы в нужную папку
move /Y .\*.o .\objects\