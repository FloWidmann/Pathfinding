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
    _sliceResistance(_slices* _slices, 0) //Initialize vector 
{
    _startPosXY.fill(-1);
    _targetPosXY.fill(-1);
}

//single access-method
Field* Field::get_instance(int pixelsize, int slices)
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
                    _sliceSize - _lineThickness, _sliceSize - _lineThickness, YELLOW);
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
                    _sliceSize - _lineThickness, _sliceSize - _lineThickness, RED);
                break;
            }
            case 4:
            {
                DrawRectangle(_offSetLeft + x * _sliceSize + _lineThickness / 2,
                    _offSetTop + y * _sliceSize + _lineThickness / 2,
                    _sliceSize - _lineThickness, _sliceSize - _lineThickness, ORANGE);
                break;
            }
            }
        }
    }
}


//Need to change the numbering of the fields so I can check if the target is in the fields 
void Field::check_mouse_input()
{
    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        int indexPosX = (mousePos.x - _offSetLeft) / _sliceSize;
        int indexPosY = (mousePos.y - _offSetTop + 22) / _sliceSize;

        if ((mousePos.x > _offSetLeft && mousePos.x < _offSetLeft + _fieldLength) &&
            (mousePos.y > (_offSetTop - 2 * _lineThickness) && mousePos.y < _offSetTop + _fieldLength))
        {
            int currentField = _sliceResistance.at(indexPosY * _slices + indexPosX);
            int newField = 0;

            switch (currentField)
            {
            case(0): newField = 3; break;
            case(1): newField = 3; _setTarget = false; break;
            case(2): newField = 3; _setStart = false; break;
            case(3): newField = 0; break;
            default: newField = 0; break;
            }
            _sliceResistance.at(indexPosY * _slices + indexPosX) = newField;

        }
    }

    if (IsKeyReleased(KEY_S))
    {
        int indexPosX = (mousePos.x - _offSetLeft) / _sliceSize;
        int indexPosY = (mousePos.y - _offSetTop + 22) / _sliceSize;

        if ((mousePos.x > _offSetLeft && mousePos.x < _offSetLeft + _fieldLength) &&
            (mousePos.y > (_offSetTop - 2 * _lineThickness) && mousePos.y < _offSetTop + _fieldLength))
        {
            if (_sliceResistance.at(indexPosY * _slices + indexPosX) == 1)
            {
                _sliceResistance.at(indexPosY * _slices + indexPosX) = 0;
                _setStart = false;
                _startPosXY.fill(-1);
            }
            else if (!_setStart)
            {

                if (_sliceResistance.at(indexPosY * _slices + indexPosX) == 1) _setTarget = false;
                _sliceResistance.at(indexPosY * _slices + indexPosX) = 2;
                _setStart = true;
                _startPosXY = { indexPosX, indexPosY };
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
            if (_sliceResistance.at(indexPosY * _slices + indexPosX) == 1)
            {
                _sliceResistance.at(indexPosY * _slices + indexPosX) = 0;
                _setTarget = false;
                _targetPosXY.fill(-1);
            }
            else if (!_setTarget)
            {
                if (_sliceResistance.at(indexPosY * _slices + indexPosX) == 2) _setStart = false;
                _sliceResistance.at(indexPosY * _slices + indexPosX) = 1;
                _setTarget = true;
                _targetPosXY = { indexPosX, indexPosY };
            }
        }
    }
}

void Field::set_start(bool isSet)
{
    _setStart = isSet;
}

void Field::set_target(bool isSet)
{
    _setTarget = isSet;
}

bool Field::get_target_set()
{
    return _setTarget;
}

bool Field::get_start_set()
{
    return _setStart;
}

std::array<int, 2> Field::get_start_position()
{
    return _startPosXY;
}

std::array<int, 2> Field::get_target_position()
{
    return _targetPosXY;
}

int Field::get_num_of_slices()
{
    return _slices;
}

void Field::clear_all_field()
{
    for (float& num : _sliceResistance)
    {
        num = 0;
    }
    _setTarget = false;
    _setStart = false;
}