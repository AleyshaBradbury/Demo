#pragma once
#include "Character.h"
#include "NPC.h"

class Enemy : public Character
{
public:
	Enemy(float health, sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, CharacterManager* character_manager);

	GridObject* DoAction(float dt, Grid* grid);

	void HandleTarget();

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

