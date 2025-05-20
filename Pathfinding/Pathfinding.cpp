#include <iostream>
#include <raylib.h>
#include <vector>
#include "Field.hpp"
#include "MainWindow.hpp" h

#define WIDTH 1920
#define HEIGHT 1080



int main()
{
    MainWindow mainWindow;
    mainWindow.init();
    mainWindow.run_simulation();
}
