#pragma once
#include "Character.h"

class TurnManager
{
public:
	enum class Turn {
		Player,
		NPC,
		Enemy,
		Count
	};

	enum class EnemyTurn {
		FindTarget,
		Movement,
		Attack,
		Count
	};

public:
	void IncrementTurn();
	void StartTurn(Character* character, sf::View* view);
	void EndTurn(Character* character);

	void IncrementEnemyTurn();

	//Which factions turn is the game on?
	static Turn turn_;
	EnemyTurn enemy_turn_ = EnemyTurn::FindTarget;

private:
	bool was_moveable_ = false;

};

