#include "MainWindow.hpp"




MainWindow::MainWindow()
{
    InitWindow(WIDTH, HEIGHT, "raylib [shapes] example - basic shapes drawing");
    SetTargetFPS(60);
    Field::get_instance(64, 12);
    _buttonDFS = new Button("DFS-Algorithm", WIDTH / 2 + 400, HEIGHT / 2, 50, 10);
    _buttonDjikstra = new Button("Djikstra Algorithm", WIDTH / 2 + 400, HEIGHT / 2 + 100, 50, 10);
}

MainWindow::~MainWindow()
{
    Field::delete_instance();
    delete(_buttonDjikstra);
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
        _buttonDjikstra->display_button();

        if (_buttonDFS->was_pressed())
        {
            ClearCheckedFields(Field::get_instance()->get_sliceResistance());
            DephFirstAlgorithm(Field::get_instance()->get_sliceResistance(), Field::get_instance()->get_num_of_slices(), Field::get_instance()->get_num_of_slices(),
               Field::get_instance()->get_start_position(), Field::get_instance()->get_target_position());            
        }

        if (_buttonDjikstra->was_pressed())
        {
            DjikstraAlgorithm(Field::get_instance()->get_sliceResistance(), Field::get_instance()->get_num_of_slices(), Field::get_instance()->get_num_of_slices(),
                Field::get_instance()->get_start_position(), Field::get_instance()->get_target_position());
        }


        if (IsKeyReleased(KEY_V)) Field::get_instance()->clear_all_field();

        Field::get_instance()->draw_blocks();
        Field::get_instance()->draw_grit();
        Field::get_instance()->check_mouse_input();
        
        

        EndDrawing();
    }

    CloseWindow();
}


