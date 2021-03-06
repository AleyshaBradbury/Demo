#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"
#include "GeneralVariables.h"

class GameObject : public sf::RectangleShape
{
public:
	void SetGridNode(Node* grid_position);
	Node* GetGridNode();
	//Can a character stand on top of this thing?
	bool isOverlap();
	//Reset the health of the character to max health.
	void ResetHealth();
	//Remove health from character and delete them if they have no health left.
	bool SubtractHealth(float health);
	//Return the amount of health remaining.
	float GetHealth();

protected:
	Node* grid_node_ = NULL;
	//Can a character stand on top of this thing?
	bool overlap_ = true;

	float max_health_ = 2.0f;
	float health_ = 2.0f;
};

