#ifndef FIELD_HPP
#define FIELD_HPP
#include <array>
#include <vector>
#include <raylib.h>

#define WIDTH 1920
#define HEIGHT 1080


class Field
{
    //Singleton class so that all algorithms can have access to the same vector containing info about the grit

private:

    static Field* _instance; //static variable that stores the only instance of the class

    int _sliceSize;
    int _slices;
    int _fieldLength;
    int _offSetLeft;
    int _offSetTop;
    int _lineThickness;

    bool _setTarget;
    bool _setStart;

    std::array<int, 2> _startPosXY;
    std::array<int, 2> _targetPosXY;

    std::vector<float> _sliceResistance;

    //private constructor so the class can be only instanciated through get_instance()-method
    Field(int pixelsize, int slices);

public:

    //Returns the only instance of this class or creates one, put standard-values
    static Field* get_instance(int pixelsize = 64, int slices = 12);

    static void delete_instance();

    void draw_grit();
    void draw_blocks();
    void check_mouse_input();
    void clear_all_field();
    void set_start(bool isSet);
    void set_target(bool isSet);

    int get_num_of_slices();

    bool get_target_set();
    bool get_start_set();

    std::array<int, 2> get_start_position();
    std::array<int, 2> get_target_position();

    //Return a vector with obstacles, start and end 
    std::vector<float>& get_sliceResistance();
};

#endif