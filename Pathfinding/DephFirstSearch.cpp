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
