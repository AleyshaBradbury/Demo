#pragma once
#include <SFML/Graphics.hpp>

class Node : public sf::RectangleShape
{
public:
	Node(sf::Vector2i grid_position);

	//Get the position of the node in the grid.
	sf::Vector2i GetGridPosition();
	void AddNeighbour(Node* node, int i);
	Node** GetNeighbours();
	int GetNumNeighbours();
	int GetDistance();

private:
	//The position of the node in the grid.
	sf::Vector2i grid_position_ = sf::Vector2i(0.0f, 0.0f);
	//The nodes neighboring this one.
	Node* neighbours_[4] = {NULL, NULL, NULL, NULL};
	//The number of neighbours created so far.
	int num_neighbours_ = 0;
	int distance = 1;
};
