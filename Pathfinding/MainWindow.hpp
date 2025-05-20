#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "Field.hpp"
#include "raylib.h"

class MainWindow
{
public:
    MainWindow();
    ~MainWindow(); // Destruktor f�r Speicherverwaltung

    void init();
    void run_simulation();
};

#endif // MAINWINDOW_HPP
