#pragma once
#include "Character.h"
#include <unordered_map>

class NPC : public Character
{
public:
	NPC(std::string name, int health, sf::Vector2f position, 
		sf::Texture* texture, CharacterManager* character_manager, int movements, int attacks);
	~NPC();
	void DoAction(float dt, Grid* grid);
	void IncrementNeeds();
	
	void AddNeed(std::string name);

private:
	std::unordered_map<std::string, unsigned int> Needs_;
};

