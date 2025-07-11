#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <raylib.h>
#include <string>
#include <iostream>

class Button
{
private:

    const char* _title;
    float _posX;
    float _posY;
    float _height;
    float _width;
    int _fontOffSet;
    int _fontSize;
    bool _wasClicked;
    Rectangle _buttonFrame;

public:
    Button(const char* title, float posX, float posY, int fontSize, int fontOffSet) : _title(title), _posX(posX), _posY(posY), _fontSize(fontSize), _fontOffSet(fontOffSet)
    {
        _height = _fontSize + 2 * _fontOffSet;
        _width = MeasureText(_title, _fontSize) + 2 * _fontOffSet;
        _buttonFrame = { _posX, _posY, _width, _height };
        _wasClicked = false;
    }

    ~Button()
    {

    }

    void display_button()
    {
        DrawRectangleRoundedLines(_buttonFrame, 0.5, 0, 3, WHITE);
        if(check_mouse_position())  DrawText(_title, _posX + _fontOffSet, _posY + _fontOffSet, _fontSize, GREEN);
        else
        {
            DrawText(_title, _posX + _fontOffSet, _posY + _fontOffSet, _fontSize, RED);
        }
    }

    bool was_pressed()
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && check_mouse_position())
        {
            return true;
        }

        else
        {
            return false;
        }
    }

private:
    bool check_mouse_position()
    {

        Vector2 mousePosition = GetMousePosition();
        if (mousePosition.x > _posX && mousePosition.x < _posX + _width && mousePosition.y > _posY - _height / 2 && mousePosition.y < _posY + _height / 2) return true;
        else
        {
            return false;
        }
    }
};





#endif // !BUTTON_HPP
