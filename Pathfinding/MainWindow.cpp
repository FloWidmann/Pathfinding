#include "MainWindow.hpp"





MainWindow::MainWindow()
{
    InitWindow(WIDTH, HEIGHT, "raylib [shapes] example - basic shapes drawing");
    SetTargetFPS(60);
    Field::get_instance(64, 12);
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
        
        if (IsKeyReleased(KEY_C))// && _solvingAlgorithm == false)
        {
            DepthFirstSearch(Field::get_instance()->get_sliceResistance(), Field::get_instance()->get_num_of_slices(), Field::get_instance()->get_num_of_slices(),
                Field::get_instance()->get_start_position(), { 0,0 });
        }

        Field::get_instance()->draw_grit();
        Field::get_instance()->draw_blocks();
        Field::get_instance()->check_mouse_input();
        
        

        EndDrawing();
    }

    CloseWindow();
}