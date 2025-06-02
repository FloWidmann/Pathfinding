#include "Node.hpp"

void Node::add_neighbour(Node* neighbour)
{
    vecNeighbours.push_back(neighbour);
    neighbour->parentNode = this;
}


void Node::print_neighbour()
{
    for (Node* node : vecNeighbours)
    {
        std::cout << node->absolutePosition << " ";
    }
}
