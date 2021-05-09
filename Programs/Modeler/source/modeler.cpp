#include "modeler2d.h"

int main()
{
    // Моделировщик
    model::MainModeler2D modeler;
    
    // Инициализация, работа, обнуление
    modeler.initialize();
    modeler.run();
    modeler.clear();
    
    return 0;
}