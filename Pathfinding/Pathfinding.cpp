#include <iostream>
#include "Astar.hpp"
#include <raylib.h>


enum Colors
{

};
struct Field
{
	int iPosx;
	int iPosy;
	Field* parent;

};





int main()
{	
	const int iScreenHeight = 736;
	const int iScreenWidth = 1280;
	const int iPixelSize = 32;
	InitWindow(iScreenWidth, iScreenHeight, "Pathfinding");
	
	while (!WindowShouldClose())
	{
		BeginDrawing();
		for (int i = 0; i < 1280 ; i += iPixelSize)
		{
			for (int j = 0; j < 720 ; j += iPixelSize)
			{
				DrawRectangle(i, j, iPixelSize, iPixelSize, GREEN);
				DrawLine(i, 0, i, iScreenHeight, BLACK);
				DrawLine(0, j, iScreenWidth, j, BLACK);

			}
		}

		EndDrawing();
	}

	return 0;
}