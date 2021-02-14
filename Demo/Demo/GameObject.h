#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"

class GameObject : public sf::RectangleShape
{
public:
	void SetGridNode(Node* grid_position);
	Node* GetGridNode();
	//Can a character stand on top of this thing?
	bool isOverlap();

protected:
	Node* grid_node_ = NULL;
	//Can a character stand on top of this thing?
	bool overlap_ = true;
};

