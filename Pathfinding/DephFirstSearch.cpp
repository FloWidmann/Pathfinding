#include "DephFirstSearch.hpp"

void DepthFirstSearch(std::vector<float>& obstacleArray, int fieldWidth, int fieldHeight, std::array<int, 2> startPosition, std::array<int, 2> tartgetPosition)
{
    //NOTE: this first implementation works only with bool values. So no obstacles that would "slow down" the path
    //Here comes a very naive approach, let´s see how it goes

    std::vector <int> vecPossibleFields;
    bool finish = false;

    if (startPosition[0] >= 0 && startPosition[1] >= 0)
    {
        int checkFieldX = startPosition[0];
        int checkFieldY = startPosition[1];

        while (!finish)
        {
            //Check North
            if (obstacleArray.at((checkFieldY - 1) * fieldWidth + checkFieldX) == 0 && (checkFieldY - 1) >= 0)
            {
                vecPossibleFields.push_back((checkFieldY - 1) * fieldWidth + checkFieldX);
                obstacleArray.at(((checkFieldY - 1) * fieldWidth + checkFieldX)) = 4;

            }

            //Check West
            if (obstacleArray.at(checkFieldY * fieldWidth + checkFieldX - 1) == 0 && (checkFieldX - 1) >= 0)
            {
                vecPossibleFields.push_back(checkFieldY * fieldWidth + checkFieldX - 1);
                obstacleArray.at(checkFieldY * fieldWidth + checkFieldX - 1) = 4;
            }

            //Check South
            if (obstacleArray.at((checkFieldY + 1) * fieldWidth + checkFieldX) == 0 && (checkFieldY + 1) <= fieldHeight)
            {
                vecPossibleFields.push_back((checkFieldY + 1) * fieldWidth + checkFieldX);
                obstacleArray.at((checkFieldY + 1) * fieldWidth + checkFieldX) = 4;
            }

            //Check East
            if (obstacleArray.at(checkFieldY * fieldWidth + checkFieldX + 1) == 0 && (checkFieldX + 1) <= fieldWidth)
            {
                vecPossibleFields.push_back(checkFieldY * fieldWidth + checkFieldX + 1);
                obstacleArray.at(checkFieldY * fieldWidth + checkFieldX + 1) = 4;
            }
            finish = true;
        }
    }

    else
    {
        std::cout << "Start-Position wurde nicht richtig gesetzt! (Position < 0) " << std::endl;
    }
}