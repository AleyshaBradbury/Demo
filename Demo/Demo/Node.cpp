#include "Node.h"
#include "Grid.h"

Node::Node(sf::Vector2i grid_position)
{
	//Set the position on the grid for the node and grid piece.
	grid_position_ = grid_position;

	//Setup the node.
	setSize(sf::Vector2f(20.0f, 20.0f));
	setOrigin(getSize() / 2.0f);
	setPosition(sf::Vector2f(grid_position_.x * Grid::grid_spacing_ + Grid::grid_spacing_ / 2.0f, 
		grid_position_.y * Grid::grid_spacing_ + Grid::grid_spacing_ / 2.0f));
	setFillColor(sf::Color::Blue);
}

sf::Vector2i Node::GetGridPosition()
{
	return grid_position_;
}

void Node::AddNeighbour(Node* node, int i)
{
	neighbours_[i] = node;
	num_neighbours_ += 1;
}

Node** Node::GetNeighbours()
{
	return neighbours_;
}

int Node::GetNumNeighbours()
{
	return num_neighbours_;
}

int Node::GetDistance()
{
	return distance;
}
