#ifndef ASTAR_HPP
#define ASTAR_HPP
#include <array>
#include <vector>
#include <iostream>
#include <stack>
#include <limits>
#include <queue>
#include <algorithm>
#include <iomanip>
#include "Node.hpp"

void CheckPossibleFields(std::vector<float>& obstacleArray, int fieldWidth, int fieldHeight, std::array<int, 2> startPosition, std::array<int, 2> targetPosition);

void DjikstraAlgorithm(std::vector<float>& obstacleArray, int fieldWidth, int fieldHeight, std::array<int, 2> startPosition, std::array<int, 2> targetPosition);

#endif // !ASTAR_HPP
