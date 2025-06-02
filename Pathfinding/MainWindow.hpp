#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include "Button.hpp"
#include "Field.hpp"
#include "DephFirstSearch.hpp"
#include "DjikstraAlgorithm.hpp"

#define WIDTH 1920
#define HEIGHT 1080


class MainWindow
{
private:
    Button* _buttonDFS;
    Button* _buttonDjikstra;
    //bool _solvingAlgorithm;


public:
    MainWindow();
    ~MainWindow(); // Destruktor für Speicherverwaltung

    void run_simulation();
};

#endif //MAINWINDOW_HPP
