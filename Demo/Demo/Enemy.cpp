#include "Enemy.h"
#include "Grid.h"
#include "CharacterManager.h"

Enemy::Enemy(float health, sf::Vector2f size, sf::Vector2f position, sf::Texture* texture,
	CharacterManager* character_manager) : 
	Character("", health, size, position, texture, character_manager)
{
}

GridObject* Enemy::DoAction(float dt, Grid* grid)
{
	switch (stage_)
	{
	case TurnStages::FindTarget:
		//Find the closest target.
		target_ = grid->FindClosestTarget(this);
		IncrementTurn();
		break;
	case TurnStages::Movement:
		//Move towards the target.
		if (target_) {
			grid->MoveCharacterTowardsTarget(this, target_);
		}
		IncrementTurn();
		break;
	case TurnStages::Attack:
		if (target_ && grid->CheckIfInRange(GetGridNode(),
			target_->GetGridNode(), 1)) {
			if (target_->SubtractHealth(1)) {
				return target_;
			}
		}
		IncrementTurn();
		break;
	}
	if (stage_ == TurnStages::FindTarget) {
		TurnManager::DetermineCharacterTurn();
	}
	return nullptr;
}

void Enemy::HandleTarget()
{
}

void Enemy::IncrementTurn()
{
	stage_ = TurnStages((int)stage_ + 1 == (int)TurnStages::Count ?
		0 : (int)stage_ + 1);
}

