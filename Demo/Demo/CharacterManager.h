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
	void CreateNPCFromFile(std::string file_name, QuestManager* quest_manager);
	//A vector of enemies that are alive.
	std::vector<Enemy*> Enemies_;

	
	void RenderAll();
	void DeleteAll();
	void DeleteDeadCharacter(Character* character);
	void SpawnEnemies();

	void SetLocationManager(LocationManager* location_manager);
	void SetGrid(Grid* grid);
	void AddEnemySpawnPoint(Node* node);

private:
	LocationManager* location_manager_ = nullptr;
	Grid* grid_ = nullptr;
	int num_to_spawn_ = 2;
	std::vector<Node*> Enemy_Spawn_Points_;
};

