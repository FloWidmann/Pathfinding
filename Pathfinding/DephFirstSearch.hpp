#ifndef DEPHFIRSTSEARCH_HPP
#define DEPHFIRSTSEARCH_HPP
#include "Field.hpp"
#include <vector>
#include <array>
#include <iostream>
#include <stack>
#include "Node.hpp"





void DephFirstAlgorithm(std::vector<float>& obstacleArray, int fieldWidth, int fieldHeight, 
    std::array<int, 2> startPosition, std::array<int, 2> targetPosition);


void CheckPossibleFields(std::vector<float>& obstacleArray, int fieldWidth, int fieldHeight,
    std::array<int, 2> startPosition, std::array<int, 2> targetPosition);


void ClearCheckedFields(std::vector<float>& obstacleArray);


#endif // !DEPHFIRSTSEARCH_HPP
