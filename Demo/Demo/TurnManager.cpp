#include "TurnManager.h"

void TurnManager::IncrementTurn()
{
	turn_ = Turn((int)turn_ + 1 == (int)Turn::Count ? 0 : (int)turn_ + 1);
}

void TurnManager::StartTurn(Character* character)
{
	was_moveable_ = character->GetMoveable();
	character->SetMoveable(true);
}

void TurnManager::EndTurn(Character* character)
{
	character->SetMoveable(was_moveable_);
}

void TurnManager::IncrementEnemyTurn()
{
	enemy_turn_ = EnemyTurn((int)enemy_turn_ + 1 == (int)EnemyTurn::Count ? 
		0 : (int)enemy_turn_ + 1);
}
