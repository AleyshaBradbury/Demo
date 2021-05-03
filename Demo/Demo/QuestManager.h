#pragma once
#include "Quest.h"
#include <unordered_map>
#include "NPC.h"
#include "ResourceManager.h"

class QuestManager
{
public:
	QuestManager(CharacterManager* character_manager);
	void GenerateQuests(NPC* npc);
	std::vector<Quest*> GetNPCsQuests(NPC* npc);

	void DeleteQuest(Quest* quest, NPC* npc);

private:
	void AddQuest(NPC* npc, Quest* quest);
	std::unordered_map<NPC*, std::vector<Quest*>> Quests_;

	CharacterManager* character_manager_;
};

