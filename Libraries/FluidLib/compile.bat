cd %cd%
g++ -c source\exception.cpp -I.\headers
g++ -c source\basic.cpp -I.\headers
g++ -c source\components2d.cpp -I.\headers
g++ -c source\tools2d.cpp -I.\headers
g++ -c source\fluids2d.cpp -I.\headers
g++ -c source\borders2d.cpp -I.\headers
g++ -c source\fluidlib2d.cpp -I.\headers
move /Y .\*.o .\objects\