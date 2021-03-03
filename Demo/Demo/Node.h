#pragma once
#include <SFML/Graphics.hpp>

class GridPiece;

class Node : public sf::RectangleShape
{
public:
	Node(sf::Vector2i grid_position);
	void RenderMoveable(sf::RenderWindow* window);

	//Set the grid piece the node is attatched to.
	void SetGridPiece(GridPiece* grid_piece);
	//Get the grid piece attatched to the node.
	GridPiece* GetGridPiece();
	//Get the position of the node in the grid.
	sf::Vector2i GetGridPosition();
	void AddNeighbour(Node* node, int i);
	Node* GetNeighbour(int i);
	int GetNumNeighbours();
	int GetDistance();

private:
	GridPiece* grid_piece_ = nullptr;
	//The position of the node in the grid.
	sf::Vector2i grid_position_ = sf::Vector2i(0.0f, 0.0f);
	//The nodes neighboring this one.
	Node* neighbours_[4] = {NULL, NULL, NULL, NULL};
	//The number of neighbours created so far.
	int num_neighbours_ = 0;
	int distance = 1;

	sf::RectangleShape moveable_;
};
