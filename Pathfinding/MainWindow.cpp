#include "MainWindow.hpp"

MainWindow::MainWindow()
{
    InitWindow(WIDTH, HEIGHT, "raylib [shapes] example - basic shapes drawing");
    SetTargetFPS(60);
    Field::getInstance(64, 12);


    _buttonDFS = new Button("DFS-Algorithm", WIDTH / 2 + 400, HEIGHT / 2, 50, 10);
}

MainWindow::~MainWindow()
{
    Field::delete_instance();
}

void MainWindow::run_simulation()
{
    Rectangle rec = { 350, 250, 100, 40 };
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Pathfinding-Algorithms Demonstration", WIDTH / 2 - 300, 40, 40, RED);
        DrawLine(WIDTH / 2 - 300, 40, WIDTH / 2 - 275, 40, WHITE);
        _buttonDFS->display_button();

        Field::getInstance()->draw_grit();
        Field::getInstance()->draw_blocks();
        Field::getInstance()->get_mouse_input();
        
        

        EndDrawing();
    }

    CloseWindow();
}



