#ifndef FIELD_HPP
#define FIELD_HPP

#include <raylib.h>
#include <vector>

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

    std::vector<float> _sliceResistance;

    //private constructor so the class can be only instanciated through getInstance()-method
    Field(int pixelsize, int slices);

public:

    //Returns the only instance of this class or creates one, put standard-values
    static Field* getInstance(int pixelsize = 64, int slices = 12);

    static void delete_instance();
    void draw_grit();
    void draw_blocks();
    void get_mouse_input();

    //Return a vector with obstacles, start and end 
    std::vector<float>& get_sliceResistance();
};
#endif // !FIELD_HPP
