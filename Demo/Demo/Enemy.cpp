#include "Enemy.h"

Enemy::Enemy(float health) : 
	Character("", health)
{
}

void Enemy::SetTarget(GameObject* target)
{
	target_ = target;
}

GameObject* Enemy::GetTarget()
{
	return target_;
}

void Enemy::HandleTarget()
{
}

