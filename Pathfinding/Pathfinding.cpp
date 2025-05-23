#include <iostream>
#include <raylib.h>
#include <vector>
#include <string>
#include <array>


#define WIDTH 1920
#define HEIGHT 1080


//The first one is called Depth first search algorithm DFS
//I implemented it on my own so no judgment here pls
//First timing a tree here we go 
//source for info https://brilliant.org/wiki/depth-first-search-dfs/#:~:text=Depth%2Dfirst%20search%20(DFS)%20is%20an%20algorithm%20for%20searching,path%2C%20and%20then%20explores%20it.


void change_float_to_bool(std::vector<float>& vec) {
    for (float& num : vec) {
        num = (num >= 0.5) ? 1 : 0; //ternary operator - if condition then 1 otherwise 0
    }
}



void DepthFirstSearch(std::vector<float>& obstacleArray, int fieldWidth, int fieldHeight, int posStartX, int posStartY, int posTargetX, int posTargetY)
{
    //NOTE: this first implementation works only with bool values. So no obstacles that would "slow down" the path
    //Here comes a very naive approach, let´s see how it goes

    change_float_to_bool(obstacleArray);
    std::vector <int> vecPossibleFields;
    int checkFieldX = posStartX;
    int checkFielY = posStartY;
    bool finish = false;

    while(!finish)
    {
        //Check North
        if (obstacleArray.at((posStartY - 1) * fieldWidth + posStartX) == 0 && (posStartY - 1) > 0)
        {
            vecPossibleFields.push_back((posStartY + 1) * fieldWidth + posStartX);
        }
    
        //Check West
        if (obstacleArray.at(posStartY * fieldWidth + posStartX - 1) == 0 && (posStartX - 1) > 0)
        {
            vecPossibleFields.push_back((posStartY + 1) * fieldWidth + posStartX);
        }
    
        //Check South
        if (obstacleArray.at((posStartY + 1) * fieldWidth + posStartX) == 0 && (posStartY + 1) > fieldHeight)
        {
            vecPossibleFields.push_back((posStartY + 1) * fieldWidth + posStartX);
        }
    
        //Check East
        if (obstacleArray.at(posStartY * fieldWidth + posStartX + 1) == 0 && (posStartX + 1) < fieldWidth)
        {
            vecPossibleFields.push_back((posStartY + 1) * fieldWidth + posStartX);
        }
    }   

    for (int positions : vecPossibleFields)
    {
        std::cout << positions << " ";
    }
    
}


#include "MainWindow.hpp" 



int main()
{

    MainWindow mainWindow;
    mainWindow.run_simulation();
    for (float position : Field::get_instance()->get_sliceResistance())
    {
        std::cout << position << " ";
    }

}