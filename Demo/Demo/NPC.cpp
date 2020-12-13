#include "NPC.h"
#include <iostream>
#include <math.h>

NPC::NPC(std::string name, float health) : Character(name, health)
{
	std::cout << name << ":\n";
	AddNeed("Food");
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
