#ifndef DEPHFIRSTSEARCH_HPP
#define DEPHFIRSTSEARCH_HPP
#include <vector>
#include <array>
#include <iostream>
#include <unordered_set>

void CheckPossibleFields(std::vector<float>& obstacleArray, int fieldWidth, int fieldHeight,
    std::array<int, 2> startPosition, std::array<int, 2> targetPosition);


void ClearCheckedFields(std::vector<float>& obstacleArray);


#endif // !DEPHFIRSTSEARCH_HPP
