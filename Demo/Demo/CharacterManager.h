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
	NPC* FindNPCByName(std::string name);
	//A vector of enemies that are alive.
	std::vector<Enemy*> Enemies_;
	void LoadEnemyTypesFromFile(std::string file_name);
	
	void RenderAll();
	void DeleteAll();
	void DeleteDeadGoodCharacter(std::string character_name);
	void DeleteDeadEnemy(Enemy* enemy);
	void SpawnEnemies();

	void SetLocationManager(LocationManager* location_manager);
	void SetGrid(Grid* grid);
	void AddEnemySpawnPoint(Node* node);

	std::string GetEnemyDropByEnemyName(std::string enemy_name);

	void CreateRelationship(NPC* npc, std::string other_character);
	void ChangeRelationshipsAfterQuest(NPC* npc);


private:
	Enemy* ChooseEnemyType();
	LocationManager* location_manager_ = nullptr;
	Grid* grid_ = nullptr;
	unsigned int num_to_spawn_ = 2;
	std::vector<Node*> Enemy_Spawn_Points_;
	bool spawned_before_ = false;

	struct EnemyType {
		std::string name_;
		std::string drop_;
		unsigned int max_health_;
		unsigned int movement_;
		unsigned int attack_;
		unsigned int attack_strength_;
		std::string texture_location_;
	};
	std::vector<EnemyType> Enemy_Types_;
};

