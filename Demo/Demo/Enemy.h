#pragma once
#include "Character.h"
#include "NPC.h"

class Enemy : public Character
{
public:
	Enemy(float health, CharacterManager* character_manager);

	GameObject* DoAction(float dt, Grid* grid);

	void HandleTarget();

private:
	enum class TurnStages {
		FindTarget,
		Movement,
		Attack,
		Count
	};

	void IncrementTurn();

	GameObject* target_ = nullptr;
	TurnStages stage_ = TurnStages::FindTarget;
};

