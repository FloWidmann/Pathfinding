#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "Field.hpp"
#include "raylib.h"

class MainWindow
{
private:
    Field* _field;

public:
    MainWindow();
    ~MainWindow(); // Destruktor für Speicherverwaltung

    void init();
    void run_simulation();
};

#endif // MAINWINDOW_HPP
