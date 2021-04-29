#include "QuestManager.h"
#include "CharacterManager.h"

QuestManager::QuestManager(CharacterManager* character_manager)
{
    character_manager_ = character_manager;

    GenerateQuests();
}

void QuestManager::GenerateQuests()
{
    Quest* quest = new Quest("Quest", std::vector<Quest::QuestDetails>());
    AddQuest(character_manager_->Npcs_[0], quest);
}

std::vector<Quest*> QuestManager::GetNPCsQuests(NPC* npc)
{
    if (Quests_.find(npc) == Quests_.end()) {
        Quests_.insert(std::pair<NPC*, std::vector<Quest*>>(npc, std::vector<Quest*>()));
    }
    return Quests_[npc];
}

void QuestManager::AddQuest(NPC* npc, Quest* quest)
{
    if (Quests_.find(npc) == Quests_.end()) {
        Quests_.insert(std::pair<NPC*, std::vector<Quest*>>(npc, std::vector<Quest*>()));
    }
    Quests_[npc].push_back(quest);
}
