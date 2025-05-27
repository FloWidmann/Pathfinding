#include <iostream>
#include <raylib.h>
#include <vector>
#include <string>
#include <array>
#include "MainWindow.hpp"

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




int main()
{

    MainWindow mainWindow;
    mainWindow.run_simulation();

}