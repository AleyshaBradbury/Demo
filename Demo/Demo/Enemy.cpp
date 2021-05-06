#include "Enemy.h"
#include "Grid.h"
#include "CharacterManager.h"
#include <iostream>

Enemy::Enemy(int health, sf::Vector2f position, sf::Texture* texture,
	CharacterManager* character_manager, int movements, int attacks, std::string name,
	std::string drop) : 
	Character(name, health, position, texture, character_manager, movements, attacks)
{
	is_enemy_ = true;
	drop_ = drop;
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
		IncrementTurn();
		break;
	case TurnStages::Movement:
		//Move towards the target.
		if (GetMovementActions() > 0 && target_) {
			grid->MoveCharacterTowardsTarget(this, target_);
			SpendMovement();
		}
		if (GetMovementActions() <= 0) {
			IncrementTurn();
		}
		break;
	case TurnStages::Attack:
		if (target_ && grid->CheckIfInRange(GetGridNode(), target_->GetGridNode(), 1)) {
			if (GetAction() > 0) {
				if (target_->GetName() == "Player") {
					Player* player = (Player*)target_;
					player->SetInfoWindow(false);
				}
				else if (target_->SubtractHealth(attack_strength_)) {
					character_manager_->DeleteDeadGoodCharacter(target_->GetName());
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

std::string Enemy::GetDropName()
{
	return drop_;
}

void Enemy::IncrementTurn()
{
	stage_ = TurnStages((int)stage_ + 1 == (int)TurnStages::Count ?
		0 : (int)stage_ + 1);
}

