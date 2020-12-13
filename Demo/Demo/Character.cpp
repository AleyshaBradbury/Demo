#include "Character.h"

Character::Character(std::string name, float health)
{
	max_health_ = health;
	name_ = name;

	ResetHealth();

	setOrigin(getSize() / 2.0f);
}

void Character::ResetHealth()
{
	health_ = max_health_;
}

bool Character::SubtractHealth(float health)
{
	health_ -= health;
	if (health_ <= 0.0f) {
		delete this;
		return true;
	}
	return false;
}

float Character::GetHealth()
{
	return health_;
}

void Character::AddMemory(std::string what_happened)
{
	Memories::AddMemory(what_happened, grid_node_);
}

int Character::GetMovement()
{
	return movement_;
}
