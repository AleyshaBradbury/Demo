#pragma once
#include "GameObject.h"
#include "Memories.h"

class Character : public GameObject, public Memories
{
public:
	Character(std::string name, float health);
	//Reset the health of the character to max health.
	void ResetHealth();
	//Remove health from character and delete them if they have no health left.
	bool SubtractHealth(float health);
	//Return the amount of health remaining.
	float GetHealth();
	void AddMemory(std::string what_happened);
	int GetMovement();
	bool GetMoveable();
	void SetMoveable(bool moveable);
	void InvertMoveable();

	void RenderMoveableArea(sf::RenderWindow* window);

	std::vector<Node*> Moveable_Nodes_;

protected:
	std::string name_;
	float health_;
	float max_health_;
	int movement_ = 3;

	bool show_movement_ = false;
};