#include "Enemy.h"
#include "Grid.h"
#include "CharacterManager.h"
#include <iostream>

Enemy::Enemy(int health, sf::Vector2f position, sf::Texture* texture,
	CharacterManager* character_manager, int movements, int attacks) : 
	Character("", health, position, texture, character_manager, movements, attacks)
{
	is_enemy_ = true;
}

Enemy::~Enemy()
{
	target_ = nullptr;
}

void Enemy::DoAction(float dt, Grid* grid)
{
	switch (stage_)
	{
	case TurnStages::FindTarget:
		//Find the closest target.
		target_ = grid->FindClosestTarget(this);
		std::cout << "Enemy: Chosen target.\n";
		IncrementTurn();
		break;
	case TurnStages::Movement:
		//Move towards the target.
		if (GetMovementActions() > 0 && target_) {
			grid->MoveCharacterTowardsTarget(this, target_);
			std::cout << "Enemy: Moving to target.\n";
			SpendMovement();
		}
		if (GetMovementActions() <= 0) {
			IncrementTurn();
		}
		break;
	case TurnStages::Attack:
		if (target_ && grid->CheckIfInRange(GetGridNode(), target_->GetGridNode(), 1)) {
			if (GetAction() > 0) {
				std::cout << "Enemy: Attacking target.\n";
				if (target_->SubtractHealth(1)) {
					character_manager_->DeleteDeadCharacter((Character*)target_);
					target_ = nullptr;
				}
				SpendAction();
			}
			else {
				IncrementTurn();
			}
		}
		else {
			IncrementTurn();
		}
		break;
	}
	if (stage_ == TurnStages::FindTarget) {
		TurnManager::DetermineCharacterTurn();
		ResetActions();
	}
}

void Enemy::IncrementTurn()
{
	stage_ = TurnStages((int)stage_ + 1 == (int)TurnStages::Count ?
		0 : (int)stage_ + 1);
}

