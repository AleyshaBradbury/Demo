#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"

class GameObject : public sf::RectangleShape
{
public:
	void SetGridNode(Node* grid_position);
	Node* GetGridNode();

protected:
	Node* grid_node_ = NULL;
};

