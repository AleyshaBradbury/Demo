#pragma once
#include "Character.h"
#include "NPC.h"

class Enemy : public Character
{
public:
	Enemy(int health, sf::Vector2f position, sf::Texture* texture, 
		CharacterManager* character_manager, int movements, int attacks);
	~Enemy();

	void DoAction(float dt, Grid* grid);

private:
	enum class TurnStages {
		FindTarget,
		Movement,
		Attack,
		Count
	};

	void IncrementTurn();

	GridObject* target_ = nullptr;
	TurnStages stage_ = TurnStages::FindTarget;
};

