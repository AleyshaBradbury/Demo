#include "NPC.h"
#include <iostream>
#include <math.h>
#include "Grid.h"

NPC::NPC(std::string name, int health, sf::Vector2f position, 
	sf::Texture* texture, CharacterManager* character_manager,
	int movements, int attacks) :
	Character(name, health, position, texture, character_manager,
		movements, attacks)
{
	std::cout << name << ":\n";
}

NPC::~NPC()
{
	for (int i = 0; i < 4; i++) {
		if (grid_node_->GetNeighbour(i)) {
			grid_node_->GetNeighbour(i)->SetLocation(nullptr);
		}
	}
}

void NPC::DoAction(float dt, Grid* grid)
{
	TurnManager::DetermineCharacterTurn();
}

void NPC::IncrementNeeds()
{
	std::cout << name_ << ":\n";
	for (auto& need : Needs_) {
		need.second = std::min((int)need.second + 1, 9);
		std::cout << "	" << need.first << ": " << need.second << std::endl;
		if (need.second > 7) {
			std::cout << "NEED CRITICAL!" << std::endl;
		}
	}
}

void NPC::AddNeed(std::string name)
{
	//Insert a need into the needs map.
	Needs_.insert(std::pair<std::string, int>(name, rand() % 10));
	std::cout << "	" << name << ": " << Needs_[name] << std::endl;
}
