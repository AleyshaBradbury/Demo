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

	void AddCompletedQuest(Quest* quest);
	std::vector<Quest*> GetCompletedQuests();

private:
	std::unordered_map<std::string, unsigned int> Needs_;
	QuestManager* quest_manager_ = nullptr;
	std::vector<Quest*> completed_quests_;
};

