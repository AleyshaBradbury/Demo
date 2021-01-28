#include "Node.h"
#include "Grid.h"

Node::Node(sf::Vector2i grid_position)
{
	//Set the position on the grid for the node and grid piece.
	grid_position_ = grid_position;

	//Setup the node.
	float size = Grid::grid_spacing_ / 5.0f * 3.0f;
	setSize(sf::Vector2f(size, size));
	setOrigin(getSize() / 2.0f);
	setPosition(sf::Vector2f(grid_position_.x * Grid::grid_spacing_ + Grid::grid_spacing_ / 2.0f, 
		grid_position_.y * Grid::grid_spacing_ + Grid::grid_spacing_ / 2.0f));
	setFillColor(sf::Color::Blue);

	//Setup the semi-transparent movement indicator.
	moveable_.setSize(sf::Vector2f(Grid::grid_spacing_, Grid::grid_spacing_));
	moveable_.setOrigin(moveable_.getSize() / 2.f);
	moveable_.setPosition(getPosition());
	moveable_.setFillColor(sf::Color(0.0f, 0.0f, 255.0f, 100.0f));
}

void Node::RenderMoveable(sf::RenderWindow* window)
{
	window->draw(moveable_);
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

Node* Node::GetNeighbour(int i)
{
	return neighbours_[i];
}

int Node::GetNumNeighbours()
{
	return num_neighbours_;
}

int Node::GetDistance()
{
	return distance;
}
