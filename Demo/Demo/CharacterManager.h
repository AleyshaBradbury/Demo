#pragma once
#include <vector>
#include "Player.h"
#include "NPC.h"
#include "Enemy.h"
#include "LocationManager.h"

class CharacterManager
{
public:
	//The player character.
	Player* player_ = nullptr;
	//A vector of npcs that are alive.
	std::vector<NPC*> Npcs_;
	//Load in NPCs from file.
	void CreateNPCFromFile(std::string file_name, Grid* grid);
	//A vector of enemies that are alive.
	std::vector<Enemy*> Enemies_;

	
	void RenderAll();
	void DeleteAll();
	void DeleteDeadCharacter(Character* character);

	void SetLocationManager(LocationManager* location_manager);

private:
	LocationManager* location_manager_ = nullptr;
};

