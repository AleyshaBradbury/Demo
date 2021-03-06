#pragma once
#include <vector>
#include "Player.h"
#include "NPC.h"
#include "Enemy.h"

class CharacterManager
{
public:
	//The player character.
	Player* player_ = nullptr;
	//A vector of npcs that are alive.
	std::vector<NPC*> Npcs_;
	//A vector of enemies that are alive.
	std::vector<Enemy*> Enemies_;

	
	void RenderAll();
	void DeleteAll();
	void DeleteDeadCharacter(Character* character);
};

