#pragma once
#include "Character.h"
#include <unordered_map>

class NPC : public Character
{
public:
	NPC(std::string name, float health);
	void IncrementNeeds();

private:
	void AddNeed(std::string name);
	std::unordered_map<std::string, unsigned int> Needs_;
};

