#pragma once
#include "GridObject.h"
#include "Memories.h"
#include "TurnManager.h"
#include "Icon.h"

class Grid;
class CharacterManager;

class Character : public GridObject, public Memories
{
public:
	Character(std::string name, int health, sf::Vector2f position,
		sf::Texture* texture, CharacterManager* character_manager, unsigned int num_movement,
		unsigned int num_attacks);
	~Character();

	virtual void DoAction(float dt, Grid* grid) = 0;


	void AddMemory(std::string what_happened);
	unsigned int GetMovement();
	bool GetMoveable();
	void SetMoveable(bool moveable);
	void InvertMoveable();

	unsigned int GetMovementActions();
	unsigned int GetAction();
	bool SpendMovement();
	bool SpendAction();

	void RenderMoveableArea();
	void RenderIcons();

	std::vector<Node*> Moveable_Nodes_;

	bool isEnemy();

protected:
	void ResetActions();

	bool is_enemy_ = false;

	std::string name_ = "";
	unsigned int movement_ = 4;
	bool show_movement_ = false;

	CharacterManager* character_manager_ = nullptr;

private:
	unsigned int num_movement_actions_ = 0;
	unsigned int max_movement_actions_ = 1;
	Icon* movement_icon_ = nullptr;
	unsigned int num_actions_ = 0;
	unsigned int max_actions_ = 1;
	Icon* actions_icon_ = nullptr;
};