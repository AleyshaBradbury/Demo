#pragma once
#include "Quest.h"
#include "NPC.h"
#include <fstream>

using namespace std;

class SaveData
{
public:
	static void SaveNewQuestData(Quest* quest, NPC* npc);
	static void SaveCompletedQuestData(NPC* npc, Quest* quest);
	static void SaveDeletedQuestData(NPC* npc, Quest* quest);
	static void SaveRelationshipChanges(NPC* npc);
	static void SaveQuestData(Quest* quest);

	static ofstream file;
};

