#ifndef NODE_H
#define NODE_H
#include <vector>
#include <iostream>


struct Node
{
    int absolutePosition;
    std::vector<Node*> vecNeighbours;
    Node* parentNode = nullptr;

    Node(int absPosition, Node* parent = nullptr) : absolutePosition(absPosition), parentNode(parent) {}

    void add_neighbour(Node* neighbour);

    void print_neighbour();
};


#endif // !NODE_H
