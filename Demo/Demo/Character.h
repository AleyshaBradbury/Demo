#pragma once
#include "GameObject.h"
#include "Memories.h"
#include "TurnManager.h"

class Grid;
class CharacterManager;

class Character : public GameObject, public Memories
{
public:
	Character(std::string name, float health, CharacterManager* character_manager);

	virtual GameObject* DoAction(float dt, Grid* grid) = 0;


	void AddMemory(std::string what_happened);
	int GetMovement();
	bool GetMoveable();
	void SetMoveable(bool moveable);
	void InvertMoveable();

	void RenderMoveableArea();

	std::vector<Node*> Moveable_Nodes_;

protected:
	std::string name_;
	int movement_ = 4;
	bool show_movement_ = false;
	CharacterManager* character_manager_;
};