#pragma once
#include "Character.h"
#include <unordered_map>

class NPC : public Character
{
public:
	NPC(std::string name, float health, sf::Vector2f size, sf::Vector2f position, 
		sf::Texture* texture, CharacterManager* character_manager);
	GridObject* DoAction(float dt, Grid* grid);
	void IncrementNeeds();

private:
	void AddNeed(std::string name);
	std::unordered_map<std::string, unsigned int> Needs_;
};

