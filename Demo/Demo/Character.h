#pragma once
#include "GameObject.h"
#include "Memories.h"

class Character : public GameObject, public Memories
{
public:
	Character(std::string name, float health);
	void AddMemory(std::string what_happened);
	int GetMovement();
	bool GetMoveable();
	void SetMoveable(bool moveable);
	void InvertMoveable();

	void RenderMoveableArea(sf::RenderWindow* window);

	std::vector<Node*> Moveable_Nodes_;

protected:
	std::string name_;
	int movement_ = 4;
	bool show_movement_ = false;
};