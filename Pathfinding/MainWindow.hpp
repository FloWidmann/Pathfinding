#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "Button.hpp"
#include "Field.hpp"



class MainWindow
{
private:
    Button* _buttonDFS;
    bool _solvingAlgorithm;


public:
    MainWindow();
    ~MainWindow(); // Destruktor für Speicherverwaltung

    void run_simulation();
};

#endif //MAINWINDOW_HPP
