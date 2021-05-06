#pragma once
#include "Character.h"
#include <unordered_map>
#include "Quest.h"

class NPC : public Character
{
public:
	NPC(std::string name, int health, sf::Vector2f position, 
		sf::Texture* texture, CharacterManager* character_manager, int movements, 
		int attacks, QuestManager* quest_manager);
	~NPC();
	void DoAction(float dt, Grid* grid);

	void IncrementNeeds();
	void AddNeed(std::string name);
	std::unordered_map<std::string, uint32_t> GetAllNeeds();

	void AddCompletedQuest(Quest* quest);
	std::vector<Quest*> GetCompletedQuests();

	void AddRelationshipWithCharacter(std::string character_name, unsigned int rel);
	unsigned int GetRelationshipWithCharacter(std::string character_name);
	void ChangeRelationshipWithCharacter(std::string character_name, int change);
	std::unordered_map<std::string, uint32_t> GetRelationships();

	uint16_t rescued_time_ = 0;

private:
	std::unordered_map<std::string, uint32_t> Needs_;
	QuestManager* quest_manager_ = nullptr;
	std::vector<Quest*> completed_quests_;
	std::unordered_map<std::string, uint32_t> Relationship_;
};

