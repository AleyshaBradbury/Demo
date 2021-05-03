#include "Character.h"
#include "CharacterManager.h"
#include "Grid.h"

Character::Character(std::string name, int health, sf::Vector2f position,
	sf::Texture* texture, CharacterManager* character_manager, 
	unsigned int num_movement, unsigned int num_attacks, unsigned int attack_strength) :
	GridObject(sf::Vector2f(Grid::grid_spacing_ / 5.0f * 4.0f,
		Grid::grid_spacing_ / 5.0f * 4.0f) , position, texture)
{
	max_health_ = health;
	ResetHealth();
	name_ = name;
	overlap_ = false;
	character_manager_ = character_manager;
	max_movement_actions_ = num_movement;
	max_actions_ = num_attacks;
	attack_strength_ = attack_strength;

	movement_icon_ = new Icon(sf::Vector2f(5.0f, 5.0f), sf::Vector2f(40.0f, 50.0f));
	movement_icon_->setFillColor(sf::Color::Blue);
	actions_icon_ = new Icon(sf::Vector2f(55.0f, 5.0f), sf::Vector2f(40.0f, 50.0f));
	actions_icon_->setFillColor(sf::Color::Red);

	setOrigin(getSize() / 2.0f);

	ResetActions();
}

Character::~Character()
{
	grid_node_->SetCharacterOnTile(nullptr);
}

void Character::AddMemory(std::vector<std::string> what_happened)
{
	Memories::AddMemory(what_happened, grid_node_);
}

unsigned int Character::GetMovement()
{
	return movement_;
}

unsigned int Character::GetMovementActions()
{
	return num_movement_actions_;
}

unsigned int Character::GetAction()
{
	return num_actions_;
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

bool Character::SpendMovement()
{
	if (num_movement_actions_ > 0) {
		num_movement_actions_--;
		movement_icon_->SetText(std::to_string(num_movement_actions_));
		return true;
	}
	return false;
}

bool Character::SpendAction()
{
	if (num_actions_ > 0) {
		num_actions_--;
		actions_icon_->SetText(std::to_string(num_actions_));
		return true;
	}
	return false;
}

void Character::RenderMoveableArea()
{
	if (show_movement_) {
		for (Node* node : Moveable_Nodes_) {
			node->RenderMoveable();
		}
	}
}

void Character::RenderIcons()
{
	actions_icon_->Render();
	movement_icon_->Render();
}

bool Character::isEnemy()
{
	return is_enemy_;
}

std::string Character::GetName()
{
	return name_;
}

void Character::ResetActions()
{
	num_movement_actions_ = max_movement_actions_;
	num_actions_ = max_actions_;
	actions_icon_->SetText(std::to_string(num_actions_));
	movement_icon_->SetText(std::to_string(num_movement_actions_));
}
