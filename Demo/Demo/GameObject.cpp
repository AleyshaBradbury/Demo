#include "GameObject.h"
#include "GeneralFunctions.h"

void GameObject::SetGridNode(Node* grid_position)
{
	grid_node_ = grid_position;
}

Node* GameObject::GetGridNode()
{
	return grid_node_;
}

bool GameObject::isOverlap()
{
	return overlap_;
}

void GameObject::ResetHealth()
{
	health_ = max_health_;
}

bool GameObject::SubtractHealth(float health)
{
	health_ -= health;
	if (health_ <= 0.0f) {
		return true;
	}
	return false;
}

float GameObject::GetHealth()
{
	return health_;
}
