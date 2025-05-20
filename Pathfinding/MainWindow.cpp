#include "MainWindow.hpp"

MainWindow::MainWindow()
{

    Field::getInstance(64, 12);
}

MainWindow::~MainWindow()
{
    Field::delete_instance();
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

        Field::getInstance()->draw_grit();
        Field::getInstance()->draw_blocks();
        Field::getInstance()->get_mouse_input();

        EndDrawing();
    }

    CloseWindow();
}
