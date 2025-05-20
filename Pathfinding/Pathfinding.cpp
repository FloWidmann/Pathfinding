#include <iostream>
#include <raylib.h>
#include <vector>

#define WIDTH 1920
#define HEIGHT 1080


class Field
{
private:
    int _pixelsize;
    int _slices;
    int _fieldSize;
    int _offSetLeft;
    int _offSetTop;
    //Vector that contains values which represent the resistance of a slice 
    std::vector<float> _sliceResistance;


public:

    Field(int pixelsize, int slices)
        : _pixelsize(pixelsize), _slices(slices),
        _fieldSize(_pixelsize* _slices),
        _offSetLeft((WIDTH - _fieldSize) / 2),
        _offSetTop((HEIGHT - _fieldSize) / 2),
        _sliceResistance(_fieldSize, 0) 
    {}

    void draw_field()
    {
        for (int i = 0; i <= _fieldSize; i += _pixelsize)
        {
            DrawLineEx(Vector2{ (float)_offSetLeft, (float)i + _offSetTop }, Vector2{ (float)_fieldSize + _offSetLeft, (float)i + _offSetTop }, 10, WHITE);
            DrawLineEx(Vector2{ float(i) + _offSetLeft, (float)_offSetTop }, Vector2{ float(i) + _offSetLeft, (float)_fieldSize + _offSetTop }, 10, WHITE);
        }
    }
};


class MainWindow
{
private:
    Field* _field;

public:

    MainWindow() : _field(new Field(64,12))
    {}

    void init()
    {
        InitWindow(WIDTH, HEIGHT, "raylib [shapes] example - basic shapes drawing");
        SetTargetFPS(60);
    }

    void run_simulation()
    {
        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Pathfinding-Algorithms Demonstration", WIDTH / 2 - 300, 40, 35, RED);
            _field->draw_field();
            EndDrawing();
        }

        CloseWindow();
    }
};

int main()
{
    MainWindow mainWindow;
    mainWindow.init();
    mainWindow.run_simulation();
}
