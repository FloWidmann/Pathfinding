#include "DjikstraAlgorithm.hpp"


void CheckPossibleFields(std::vector<float>& obstacleArray, int fieldWidth, int fieldHeight, std::array<int, 2> startPosition, std::array<int, 2> targetPosition)
{
    //NOTE: this first implementation works only with bool values. So no obstacles that would "slow down" the path
    //Here comes a very naive approach, let´s see how it goes

    std::vector <int> vecPossibleFields;
    bool finish = false;
    bool solvable = false;
    int i = 0;

    if (startPosition[0] >= 0 && startPosition[1] >= 0 && targetPosition[0] >= 0 && targetPosition[1] >= 0)
    {
        int checkFieldX = startPosition[0];
        int checkFieldY = startPosition[1];


        while (!finish)
        {
            //NOTE: painful discovery - logic conditions are from left to right, so this code is save because it checks checkFieldY first
            //Check West
            if ((checkFieldX - 1) >= 0 && obstacleArray.at(checkFieldY * fieldWidth + checkFieldX - 1) == 0)
            {
                vecPossibleFields.push_back(checkFieldY * fieldWidth + checkFieldX - 1);
                obstacleArray.at(checkFieldY * fieldWidth + checkFieldX - 1) = 4;
            }

            //Check South - have to subtract 1 because it´s 0 based
            if ((checkFieldY + 1) <= (fieldHeight - 1) && obstacleArray.at((checkFieldY + 1) * fieldWidth + checkFieldX) == 0)
            {
                vecPossibleFields.push_back((checkFieldY + 1) * fieldWidth + checkFieldX);
                obstacleArray.at((checkFieldY + 1) * fieldWidth + checkFieldX) = 4;
            }

            //Check East
            if ((checkFieldX + 1) <= (fieldWidth - 1) && obstacleArray.at(checkFieldY * fieldWidth + checkFieldX + 1) == 0)
            {
                vecPossibleFields.push_back(checkFieldY * fieldWidth + checkFieldX + 1);
                obstacleArray.at(checkFieldY * fieldWidth + checkFieldX + 1) = 4;
            }

            //Check North
            if ((checkFieldY - 1) >= 0 && obstacleArray.at((checkFieldY - 1) * fieldWidth + checkFieldX) == 0)
            {
                vecPossibleFields.push_back((checkFieldY - 1) * fieldWidth + checkFieldX);
                obstacleArray.at(((checkFieldY - 1) * fieldWidth + checkFieldX)) = 4;
            }

            if (!vecPossibleFields.empty())
            {
                int nextField = vecPossibleFields.back();
                vecPossibleFields.pop_back();

                int nextFieldX = nextField % fieldWidth;
                int nextFieldY = nextField / fieldWidth;

                if (nextFieldX >= 0 && nextFieldX < fieldWidth && nextFieldY >= 0 && nextFieldY < fieldHeight)
                {
                    checkFieldX = nextFieldX;
                    checkFieldY = nextFieldY;
                }

                else
                {
                    std::cout << "Fehlerhafte Berechnung von checkFieldX/checkFieldY!" << std::endl;
                }
            }

            else
            {
                finish = true;
            }
        }
    }

    else
    {
        std::cout << "Start-Position wurde nicht richtig gesetzt! (Position < 0) " << std::endl;
    }
}

//Because only data to read is requiered not to write, obstacleArray is set const
void CalculateDistanceToStart(const std::vector<float>& obstacleArray, std::vector<float>& vecDistances, int fieldWidth, int fieldHeight, std::array<int, 2> startPosition) {
    
    //if vectors aren´t equal size, abort 
    if (obstacleArray.size() != vecDistances.size()) return;

    int startPos = startPosition[0] + startPosition[1] * fieldWidth;

    for (int i = 0; i < vecDistances.size(); i++) {
        if (obstacleArray[i] == 3) {
            vecDistances[i] = FLT_MAX;
        }
        else if (i == startPos) {
            vecDistances[i] = 0.0f;
        }
        else {
            int x = i % fieldWidth;
            int y = i / fieldWidth;
            int distanceX = startPosition[0] - x;
            int distanceY = startPosition[1] - y;
            vecDistances[i] = sqrt(distanceX * distanceX + distanceY * distanceY);
        }
    }
}


//I know this isn´t the best way to do it, although I don´t know a better way yet
//It´s for educational purpose only
void DjikstraAlgorithm(std::vector<float>& obstacleArray, int fieldWidth, int fieldHeight, std::array<int, 2> startPosition, std::array<int, 2> targetPosition)
{

    std::vector<bool> vecVisited(fieldHeight * fieldWidth, false);
    std::vector<float> vecDistances(fieldHeight * fieldWidth);
    CalculateDistanceToStart(obstacleArray, vecDistances, fieldWidth, fieldHeight, startPosition);
    int startIndex = startPosition[0] + startPosition[1] * fieldWidth;
    Node* startNode = new Node(startPosition[0] + startPosition[1] * fieldWidth, nullptr, 0.0);
    std::array<int, 4> neighborOffsets = { -fieldWidth, fieldWidth, -1, 1 };

    std::cout << "Bevor calculation: \n";
    for (int i = 0; i < vecDistances.size(); i++)
    {
        if (vecDistances.at(i) <= fieldHeight * fieldWidth) std::cout << std::fixed << std::setprecision(2) << vecDistances.at(i) << " ";
        else
        {
            std::cout << "INF ";
        }
        if ((i + 1) % fieldWidth == 0) std::cout << "\n";

    }


    while (true) {
        int currentIndex = -1;
        float smallestDist = FLT_MAX;

        //Finds node with smallest distance
        for (int i = 0; i < vecDistances.size(); i++) {
            if (!vecVisited[i] && vecDistances[i] < smallestDist) {
                smallestDist = vecDistances[i];
                currentIndex = i;
            }
        }

        //No more nodes available or target found
        if (currentIndex == -1 || currentIndex == targetPosition[0] + targetPosition[1] * fieldWidth) break;
        vecVisited[currentIndex] = true;

        //4 possible ways to go, North, South, West, East
        
        for (int offset : neighborOffsets) {
            int neighborIdx = currentIndex + offset;
            if (neighborIdx >= 0 && neighborIdx < fieldWidth * fieldHeight && !vecVisited[neighborIdx]) {
                float newDist = vecDistances[currentIndex] + 1;
                if (newDist < vecDistances[neighborIdx]) {
                    vecDistances[neighborIdx] = newDist;
                }
            }
        }
    }
    std::cout << "after calculation \n \n";

    for (int i = 0; i < vecDistances.size(); i++)
    {
        if (vecDistances.at(i) <= 100) std::cout << std::fixed << std::setprecision(2) << vecDistances.at(i) << " ";
        else
        {
            std::cout << "INF ";
        }
        if ((i + 1) % fieldWidth == 0) std::cout << "\n";

    }
}