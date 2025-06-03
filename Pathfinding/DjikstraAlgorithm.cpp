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


//For next iteration I want to use the class nodes
void DjikstraAlgorithm(std::vector<float>& obstacleArray, int fieldWidth, int fieldHeight, std::array<int, 2> startPosition, std::array<int, 2> targetPosition)
{
    int totalNodes = fieldWidth * fieldHeight;
    std::vector<bool> vecVisited(totalNodes, false);
    std::vector<float> vecDistances(totalNodes, std::numeric_limits<float>::infinity());
    std::vector<int> previous(totalNodes, -1); // -1 is no predecessor


    int startPos = startPosition[0] + startPosition[1] * fieldWidth;
    int targetPos = targetPosition[0] + targetPosition[1] * fieldWidth;

    vecDistances[startPos] = 0.0f;

    // Min-Heap (Priority Queue)
    //contains a pair with distance, position - saves the input in a vector - sorts the values -> lowest is first
    //a Min-Heap is much faster than iterating through a vector. Min-Heap saves smallest value automatically first
    std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> priorityQueue;
    priorityQueue.push({ 0.0f, startPos });

    // Different directions
    std::array<std::array<int, 2>, 4> directions = { {{1, 0}, {-1, 0}, {0, 1}, {0, -1}} };

    while (!priorityQueue.empty()) {

        //Smallest distance is set
        std::pair<float, int> current = priorityQueue.top();
        float currentDist = current.first;
        int currentNode = current.second;

        priorityQueue.pop(); //remove first item


        if (vecVisited[currentNode]) continue; //if vec is already visited - skip rest of the while iteration
        vecVisited[currentNode] = true; //set currentNode to visited, because every node should only be visited once

        int x = currentNode % fieldWidth;
        int y = currentNode / fieldWidth;

        for (auto& dir : directions) {
            int newX = x + dir[0];
            int newY = y + dir[1];
            int neighborIndex = newX + newY * fieldWidth;

            // Prüfen, ob der Nachbar gültig ist
            if (newX < 0 || newX >= fieldWidth || newY < 0 || newY >= fieldHeight) continue;
            if (obstacleArray[neighborIndex] == 3) continue; // Hindernis

            float edgeWeight = 1.0f; // Falls jede Bewegung gleiche Kosten hat
            float newDist = vecDistances[currentNode] + edgeWeight;

            if (newDist < vecDistances[neighborIndex]) {
                vecDistances[neighborIndex] = newDist;
                previous[neighborIndex] = currentNode; // Speichert den Ursprung des Pfades
                priorityQueue.push({ newDist, neighborIndex });
            }
        }
    }

    std::vector<int> path;
    int current = targetPos;

    while (current != -1) {
        path.push_back(current);
        current = previous[current]; // Rückwärts zum Ursprung gehen
    }
    std::reverse(path.begin(), path.end()); // Reihenfolge korrigieren
    for (int pos : path)
    {
        obstacleArray.at(pos) = 4;
    }
    obstacleArray.at(startPos) = 2;
    obstacleArray.at(targetPos) = 1;
}