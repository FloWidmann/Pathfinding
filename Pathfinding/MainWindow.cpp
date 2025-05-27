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
    delete(_buttonDFS);
}


void MainWindow::run_simulation()
{
    Rectangle rec = { 350, 250, 100, 40 };
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Pathfinding-Algorithms Demonstration", WIDTH / 2 - 300, 40, 40, RED);
        _buttonDFS->display_button();
        
        if (IsKeyReleased(KEY_C))// && _solvingAlgorithm == false)
        {
            ClearCheckedFields(Field::get_instance()->get_sliceResistance());
            DephFirstAlgorithm(Field::get_instance()->get_sliceResistance(), Field::get_instance()->get_num_of_slices(), Field::get_instance()->get_num_of_slices(),
               Field::get_instance()->get_start_position(), Field::get_instance()->get_target_position());            
           // CheckPossibleFields(Field::get_instance()->get_sliceResistance(), Field::get_instance()->get_num_of_slices(), Field::get_instance()->get_num_of_slices(),
                //Field::get_instance()->get_start_position(), Field::get_instance()->get_target_position());
            
        }

        if (IsKeyReleased(KEY_V)) Field::get_instance()->clear_all_field();

        Field::get_instance()->draw_blocks();
        Field::get_instance()->draw_grit();
        Field::get_instance()->check_mouse_input();
        
        

        EndDrawing();
    }

    CloseWindow();
}


