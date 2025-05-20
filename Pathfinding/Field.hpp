#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>
#include "raylib.h"

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
    bool _setTarget;
    bool _setStart;

    std::vector<float> _sliceResistance;

public:
    Field(int pixelsize, int slices);

    void draw_grit();
    void draw_blocks();
    void get_mouse_input();

    std::vector<float> get_sliceResistance();
};

#endif // FIELD_HPP
