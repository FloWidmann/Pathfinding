#include <iostream>
#include <raylib.h>
#include <vector>

#define WIDTH 1920
#define HEIGHT 1080


class Field
{
private:
    int _sliceSize;
    int _slices;
    int _fieldLength;
    int _offSetLeft;
    int _offSetTop;
    int _lineThickness;
    //Vector that contains values which represent the resistance of a slice 
    std::vector<float> _sliceResistance;


public:

    Field(int pixelsize, int slices)
        : _sliceSize(pixelsize), _slices(slices),
        _fieldLength(_sliceSize * _slices),
        _offSetLeft((WIDTH - _fieldLength) / 2),
        _offSetTop((HEIGHT - _fieldLength) / 2),
        _sliceResistance(_fieldLength, 0), 
        _lineThickness(10)

    {
            _sliceResistance.at(5) = 1; // Wert nach der Initialisierung setzen
    }


    void draw_grit()
    {
        for (int i = 0; i <= _fieldLength; i += _sliceSize)
        {
            DrawLineEx(Vector2{ (float)_offSetLeft, (float)i + _offSetTop }, Vector2{ (float)_fieldLength + _offSetLeft, (float)i + _offSetTop }, _lineThickness, WHITE);
            DrawLineEx(Vector2{ float(i) + _offSetLeft, (float)_offSetTop }, Vector2{ float(i) + _offSetLeft, (float)_fieldLength + _offSetTop }, _lineThickness, WHITE);
        }
    }


    //Draws blocks that represent obstacles
    void draw_blocks()
    {
        for (int y = 0; y < _slices; y++)
        {
            for (int x = 0; x < _slices; x++)
            {
                int color = _sliceResistance.at(y * _slices + x);
                
                switch (color)
                {
                case(1): {
                    DrawRectangle(_offSetLeft + x * _sliceSize + _lineThickness / 2, _offSetTop + y * _sliceSize + _lineThickness / 2,
                        _sliceSize - _lineThickness, _sliceSize - _lineThickness, RED); break;
                }
                case(2): {
                    DrawRectangle(_offSetLeft + x * _sliceSize + _lineThickness / 2, _offSetTop + y * _sliceSize + _lineThickness / 2,
                        _sliceSize - _lineThickness, _sliceSize - _lineThickness, BLUE); break;
                }
                case(3): {
                    DrawRectangle(_offSetLeft + x * _sliceSize + _lineThickness / 2, _offSetTop + y * _sliceSize + _lineThickness / 2,
                        _sliceSize - _lineThickness, _sliceSize - _lineThickness, YELLOW); break;
                }
                }           
            }
        }
    }

    void get_mouse_input()
    {
        Vector2 mousePos = GetMousePosition();

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            int indexPosX = (mousePos.x - _offSetLeft) / _sliceSize;
            int indexPosY = (mousePos.y - _offSetTop + 22) / _sliceSize;
            std::cout << "X: " << indexPosX << " Y: " << (mousePos.y - _offSetTop + 22) << std::endl;

            if ((mousePos.x > _offSetLeft && mousePos.x < _offSetLeft + _fieldLength) && (mousePos.y > _offSetTop && mousePos.y < _offSetTop + _fieldLength))
            {
                
                _sliceResistance.at( indexPosY * _slices + indexPosX) = 1;
            }
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_S))
        {
            if ((mousePos.x > _offSetLeft && mousePos.x < _offSetLeft + _fieldLength) && (mousePos.y > _offSetTop && mousePos.y < _offSetTop + _fieldLength))
            {
                int indexPosX = (mousePos.x - _offSetLeft) / _sliceSize;
                int indexPosY = (mousePos.y - _offSetTop) / _sliceSize;
                std::cout << "X: " << indexPosX << " Y: " << indexPosY << std::endl;
                _sliceResistance.at(indexPosY * _slices + indexPosX) = 2;
            }
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_T))
        {
            if ((mousePos.x > _offSetLeft && mousePos.x < _offSetLeft + _fieldLength) && (mousePos.y > _offSetTop && mousePos.y < _offSetTop + _fieldLength))
            {
                int indexPosX = (mousePos.x - _offSetLeft) / _sliceSize;
                int indexPosY = (mousePos.y - _offSetTop) / _sliceSize;
                std::cout << "X: " << indexPosX << " Y: " << indexPosY << std::endl;
                _sliceResistance.at(indexPosY * _slices + indexPosX) = 3;
            }
        }
    }


    std::vector<float> get_sliceResistance()
    {
        return _sliceResistance;
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
            _field->draw_grit();
            _field->draw_blocks();
            _field->get_mouse_input();
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
