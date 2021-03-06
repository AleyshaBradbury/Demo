#include "Character.h"
#include "CharacterManager.h"

Character::Character(std::string name, float health, CharacterManager* character_manager)
{
	max_health_ = health;
	name_ = name;
	overlap_ = false;
	character_manager_ = character_manager;

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

void Character::RenderMoveableArea()
{
	if (show_movement_) {
		for (Node* node : Moveable_Nodes_) {
			node->RenderMoveable();
		}
	}
}
