#pragma once
#include "Node.h"
#include "GeneralVariables.h"
#include "GameObject.h"

class GridObject : public GameObject
{
public:
	GridObject(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture,
		GameObject* parent = nullptr);
	void SetGridNode(Node* grid_position);
	Node* GetGridNode();
	//Can a character stand on top of this thing?
	bool isOverlap();
	//Reset the health of the character to max health.
	void ResetHealth();
	//Remove health from character and delete them if they have no health left.
	bool SubtractHealth(int health);
	//Return the amount of health remaining.
	int GetHealth();

	void RenderHealthText();
	void MoveObject(sf::Vector2f position);

protected:
	Node* grid_node_ = NULL;
	//Can a character stand on top of this thing?
	bool overlap_ = true;

	int max_health_ = 2;

private:
	void SetHealthText();
	
	int health_ = 0;
	sf::Text health_text_;
};

