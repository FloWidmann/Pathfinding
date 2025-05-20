#include "MainWindow.hpp"

MainWindow::MainWindow() : _field(new Field(64, 12))
{}

MainWindow::~MainWindow()
{
    delete _field; // Speicher freigeben
}

void MainWindow::init()
{
    InitWindow(WIDTH, HEIGHT, "raylib [shapes] example - basic shapes drawing");
    SetTargetFPS(60);
}

void MainWindow::run_simulation()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Pathfinding-Algorithms Demonstration", WIDTH / 2 - 300, 40, 35, RED);
        _field->draw_grit();
        _field->draw_blocks();
        _field->get_mouse_input();
        EndDrawing();
    }

    CloseWindow();
}
