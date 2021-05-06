#include "SaveData.h"
#include "TurnManager.h"

void SaveData::SaveNewQuestData(Quest* quest, NPC* npc)
{
	//Save npc data for reference.
	file << TurnManager::turn_num_ << ",New Quest," <<  npc->GetName() << "," << npc->GetHealth();
	unordered_map<string, uint32_t> Needs = npc->GetAllNeeds();
	for (auto& need : Needs) {
		file << need.first << "," << need.second << ",";
	}
	unordered_map<string, uint32_t> Relationships = npc->GetRelationships();
	for (auto& relationship : Relationships) {
		file << relationship.first << "," << relationship.second << ",";
	}
	SaveQuestData(quest);
	file << endl;
}

void SaveData::SaveCompletedQuestData(NPC* npc, Quest* quest)
{
	file << TurnManager::turn_num_ << ",Completed Quest," << npc->GetName() << ",";
	SaveQuestData(quest);
	file << endl;
}

void SaveData::SaveDeletedQuestData(NPC* npc, Quest* quest)
{
	file << TurnManager::turn_num_ << ",Deleted Quest," << npc->GetName() << ",";
	SaveQuestData(quest);
	file << endl;
}

void SaveData::SaveRelationshipChanges(NPC* npc)
{
	file << TurnManager::turn_num_ << ",Relationship Data," << npc->GetName() << ",";
	for (auto& relationship : npc->GetRelationships()) {
		file << relationship.first << "," << relationship.second << ",";
	}
	file << endl;
}

void SaveData::SaveQuestData(Quest* quest)
{
	std::vector<Quest::QuestDetails> Quest_Requirements = quest->GetRequirements();
	for (auto& quest : Quest_Requirements) {
		file << quest.resource_ << "," << quest.amount_ << ",";
	}
}
