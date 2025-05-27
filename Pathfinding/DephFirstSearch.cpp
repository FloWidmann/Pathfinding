#include "DephFirstSearch.hpp"




void DephFirstAlgorithm(std::vector<float>& obstacleArray, int fieldWidth, int fieldHeight, std::array<int, 2> startPosition, std::array<int, 2> targetPosition)
{
    
    Node* startNode = new Node(startPosition[0] + startPosition[1] * fieldWidth);
    std::stack<Node*> nodeStack;
    std::vector<bool> vecVisited(fieldWidth * fieldHeight, false);
    nodeStack.push(startNode);
    vecVisited[startNode->absolutePosition] = true;
    
    bool finish = false;

    if (startPosition[0] >= 0 && startPosition[1] >= 0 && targetPosition[0] >= 0 && targetPosition[1] >= 0)
    {
        

        while (!nodeStack.empty())
        {
            Node* currentNode = nodeStack.top();
            int checkField = currentNode->absolutePosition;
            int checkFieldX = checkField % fieldWidth;
            int checkFieldY = checkField / fieldWidth;
            nodeStack.pop();


            //Check if the position is equal to the target plus backtracking of the right path
            if (currentNode->absolutePosition == targetPosition[0] + targetPosition[1] * fieldWidth) {
                
                std::cout << "Ziel erreicht bei: " << currentNode->absolutePosition << std::endl;

  
                std::vector<int> finalPath;
                while (currentNode != nullptr) {
                    finalPath.push_back(currentNode->absolutePosition);
                    currentNode = currentNode->parentNode;
                }

                for (int pos : finalPath) {
                    obstacleArray.at(pos) = 4;
                }

                obstacleArray.at(targetPosition[0] + targetPosition[1] * fieldWidth) = 1;
                obstacleArray.at(startPosition[0] + startPosition[1] * fieldWidth) = 2;

                break;
            }



            //Check West
            if ((checkFieldX - 1) >= 0 && obstacleArray.at(checkFieldY * fieldWidth + checkFieldX - 1) <= 2 && !vecVisited[checkFieldY * fieldWidth + checkFieldX - 1])
            {
                Node* newNode = new Node(checkFieldY * fieldWidth + checkFieldX - 1, currentNode);
                currentNode->add_neighbour(newNode);
                nodeStack.push(newNode);
                vecVisited[newNode->absolutePosition] = true;
            }

            //Check South - have to subtract 1 because it´s 0 based
            if ((checkFieldY + 1) <= (fieldHeight - 1) && obstacleArray.at((checkFieldY + 1) * fieldWidth + checkFieldX) <= 2 && !vecVisited[(checkFieldY + 1) * fieldWidth + checkFieldX])
            {
                Node* newNode = new Node((checkFieldY + 1) * fieldWidth + checkFieldX, currentNode);
                currentNode->add_neighbour(newNode);
                nodeStack.push(newNode);
                vecVisited[newNode->absolutePosition] = true;
            }

            //Check East
            if ((checkFieldX + 1) <= (fieldWidth - 1) && obstacleArray.at(checkFieldY * fieldWidth + checkFieldX + 1) <= 2 && !vecVisited[checkFieldY * fieldWidth + checkFieldX + 1])
            {
                Node* newNode = new Node(checkFieldY * fieldWidth + checkFieldX + 1, currentNode);
                currentNode->add_neighbour(newNode);
                nodeStack.push(newNode);
                vecVisited[newNode->absolutePosition] = true;
            }

            //Check North
            if ((checkFieldY - 1) >= 0 && obstacleArray.at((checkFieldY - 1) * fieldWidth + checkFieldX) <= 2 && !vecVisited[(checkFieldY - 1) * fieldWidth + checkFieldX])
            {
                Node* newNode = new Node((checkFieldY - 1) * fieldWidth + checkFieldX, currentNode);
                currentNode->add_neighbour(newNode);
                nodeStack.push(newNode);
                vecVisited[newNode->absolutePosition] = true;
            }
            //delete currentNode;
        }

        //delete startNode;
    }
}



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
            if ((checkFieldX - 1) >= 0 && obstacleArray.at(checkFieldY * fieldWidth + checkFieldX - 1) == 0 )
            {
                vecPossibleFields.push_back(checkFieldY * fieldWidth + checkFieldX - 1);
                obstacleArray.at(checkFieldY * fieldWidth + checkFieldX - 1) = 4;
            }

            //Check South - have to subtract 1 because it´s 0 based
            if ((checkFieldY + 1) <= (fieldHeight - 1)  && obstacleArray.at((checkFieldY + 1) * fieldWidth + checkFieldX) == 0 )
            {
                vecPossibleFields.push_back((checkFieldY + 1) * fieldWidth + checkFieldX);
                obstacleArray.at((checkFieldY + 1) * fieldWidth + checkFieldX) = 4;
            }

            //Check East
            if ((checkFieldX + 1) <= (fieldWidth - 1) && obstacleArray.at(checkFieldY * fieldWidth + checkFieldX + 1) == 0 )
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




void ClearCheckedFields(std::vector<float>& obstacleArray)
{
    for (float& num : obstacleArray)
    {
        if (num == 4)
        {
            num = 0;
        }
    }
}
