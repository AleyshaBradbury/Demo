#include "Character.h"

Character::Character(std::string name, float health)
{
	max_health_ = health;
	name_ = name;
	overlap_ = false;

	setOrigin(getSize() / 2.0f);
}

void Character::AddMemory(std::string what_happened)
{
	Memories::AddMemory(what_happened, grid_node_);
}

int Character::GetMovement()
{
	return movement_;
}

bool Character::GetMoveable()
{
	return show_movement_;
}

void Character::SetMoveable(bool moveable)
{
	show_movement_ = moveable;
}

void Character::InvertMoveable()
{
	show_movement_ = !show_movement_;
}

void Character::RenderMoveableArea(sf::RenderWindow* window)
{
	if (show_movement_) {
		for (Node* node : Moveable_Nodes_) {
			node->RenderMoveable(window);
		}
	}
}
