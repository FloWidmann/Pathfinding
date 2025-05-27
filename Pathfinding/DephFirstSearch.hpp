#ifndef DEPHFIRSTSEARCH_HPP
#define DEPHFIRSTSEARCH_HPP
#include "Field.hpp"
#include <vector>
#include <array>
#include <iostream>
#include <stack>
#include <chrono>
#include <thread>



struct Node
{
    int absolutePosition;
    std::vector<Node*> vecNeighbours;
    Node* parentNode = nullptr;

    Node(int absPosition, Node* parent = nullptr) : absolutePosition(absPosition), parentNode(parent) {}

    void add_neighbour(Node* neighbour)
    {
        vecNeighbours.push_back(neighbour);
        neighbour->parentNode = this;
    }

    void print_neighbour()
    {
        for (Node* node : vecNeighbours)
        {
            std::cout << node->absolutePosition << " ";
        }
    }
};

void DephFirstAlgorithm(std::vector<float>& obstacleArray, int fieldWidth, int fieldHeight, 
    std::array<int, 2> startPosition, std::array<int, 2> targetPosition);


void CheckPossibleFields(std::vector<float>& obstacleArray, int fieldWidth, int fieldHeight,
    std::array<int, 2> startPosition, std::array<int, 2> targetPosition);


void ClearCheckedFields(std::vector<float>& obstacleArray);


#endif // !DEPHFIRSTSEARCH_HPP
