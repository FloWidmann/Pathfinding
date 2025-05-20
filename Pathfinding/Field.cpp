#include "Field.hpp"

Field* Field::_instance = nullptr; // initialize static instance

Field::Field(int pixelsize, int slices)
    : _sliceSize(pixelsize), _slices(slices),
    _fieldLength(_sliceSize* _slices),
    _offSetLeft((WIDTH - _fieldLength) / 2),
    _offSetTop((HEIGHT - _fieldLength) / 2),
    _lineThickness(10),
    _setTarget(false),
    _setStart(false),
    _sliceResistance(_fieldLength, 0) //Initialize vector 
{
    _sliceResistance.at(5) = 1;
}

//single access-method
Field* Field::getInstance(int pixelsize, int slices)
{
    if (_instance == nullptr)
    {
        _instance = new Field(pixelsize, slices);
    }
    return _instance;
}

//delete singleton 
void Field::delete_instance()
{
    delete _instance;
    _instance = nullptr;
}

//reference to vector is more efficient
std::vector<float>& Field::get_sliceResistance()
{
    return _sliceResistance;
}

void Field::draw_grit()
{
    for (int i = 0; i <= _fieldLength; i += _sliceSize)
    {
        DrawLineEx(Vector2{ (float)_offSetLeft, (float)i + _offSetTop },
            Vector2{ (float)_fieldLength + _offSetLeft, (float)i + _offSetTop },
            _lineThickness, WHITE);
        DrawLineEx(Vector2{ float(i) + _offSetLeft, (float)_offSetTop },
            Vector2{ float(i) + _offSetLeft, (float)_fieldLength + _offSetTop },
            _lineThickness, WHITE);
    }
}

void Field::draw_blocks()
{
    for (int y = 0; y < _slices; y++)
    {
        for (int x = 0; x < _slices; x++)
        {
            int color = _sliceResistance.at(y * _slices + x);

            switch (color)
            {
            case 1:
            {
                DrawRectangle(_offSetLeft + x * _sliceSize + _lineThickness / 2,
                    _offSetTop + y * _sliceSize + _lineThickness / 2,
                    _sliceSize - _lineThickness, _sliceSize - _lineThickness, RED);
                break;
            }
            case 2:
            {
                DrawRectangle(_offSetLeft + x * _sliceSize + _lineThickness / 2,
                    _offSetTop + y * _sliceSize + _lineThickness / 2,
                    _sliceSize - _lineThickness, _sliceSize - _lineThickness, BLUE);
                break;
            }
            case 3:
            {
                DrawRectangle(_offSetLeft + x * _sliceSize + _lineThickness / 2,
                    _offSetTop + y * _sliceSize + _lineThickness / 2,
                    _sliceSize - _lineThickness, _sliceSize - _lineThickness, YELLOW);
                break;
            }
            }
        }
    }
}

void Field::get_mouse_input()
{
    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        int indexPosX = (mousePos.x - _offSetLeft) / _sliceSize;
        int indexPosY = (mousePos.y - _offSetTop + 22) / _sliceSize;

        if ((mousePos.x > _offSetLeft && mousePos.x < _offSetLeft + _fieldLength) &&
            (mousePos.y > (_offSetTop - 2 * _lineThickness) && mousePos.y < _offSetTop + _fieldLength))
        {
            if (_sliceResistance.at(indexPosY * _slices + indexPosX) == 1)
                _sliceResistance.at(indexPosY * _slices + indexPosX) = 0;
            else
                _sliceResistance.at(indexPosY * _slices + indexPosX) = 1;
        }
    }

    if (IsKeyReleased(KEY_S))
    {
        int indexPosX = (mousePos.x - _offSetLeft) / _sliceSize;
        int indexPosY = (mousePos.y - _offSetTop + 22) / _sliceSize;

        if ((mousePos.x > _offSetLeft && mousePos.x < _offSetLeft + _fieldLength) &&
            (mousePos.y > (_offSetTop - 2 * _lineThickness) && mousePos.y < _offSetTop + _fieldLength))
        {
            if (_sliceResistance.at(indexPosY * _slices + indexPosX) == 2)
            {
                _sliceResistance.at(indexPosY * _slices + indexPosX) = 0;
                _setStart = false;
            }
            else if (!_setStart)
            {
                _sliceResistance.at(indexPosY * _slices + indexPosX) = 2;
                _setStart = true;
            }
        }
    }

    if (IsKeyReleased(KEY_T))
    {
        int indexPosX = (mousePos.x - _offSetLeft) / _sliceSize;
        int indexPosY = (mousePos.y - _offSetTop + 22) / _sliceSize;

        if ((mousePos.x > _offSetLeft && mousePos.x < _offSetLeft + _fieldLength) &&
            (mousePos.y > (_offSetTop - 2 * _lineThickness) && mousePos.y < _offSetTop + _fieldLength))
        {
            if (_sliceResistance.at(indexPosY * _slices + indexPosX) == 3)
            {
                _sliceResistance.at(indexPosY * _slices + indexPosX) = 0;
                _setTarget = false;
            }
            else if (!_setTarget)
            {
                _sliceResistance.at(indexPosY * _slices + indexPosX) = 3;
                _setTarget = true;
            }
        }
    }
}
