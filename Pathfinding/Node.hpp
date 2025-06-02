#ifndef NODE_H
#define NODE_H
#include <vector>
#include <iostream>


struct Node
{
    int absolutePosition;
    float value;
    std::vector<Node*> vecNeighbours;
    Node* parentNode = nullptr;

    Node(int absPosition, Node* parent = nullptr, float startValue = 0.0) : absolutePosition(absPosition), parentNode(parent), value(startValue) {}

    void add_neighbour(Node* neighbour);
    void change_value(float value);
    void print_neighbour();
};


#endif // !NODE_H
