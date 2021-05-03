#include "QuestManager.h"
#include "CharacterManager.h"
#include "ResourceManager.h"

QuestManager::QuestManager(CharacterManager* character_manager)
{
    character_manager_ = character_manager;
}

void QuestManager::GenerateQuests(NPC* npc)
{
    if (GetNPCsQuests(npc).size() == 0 && ResourceManager::resources.size() > 0) {
        int random = rand() % ResourceManager::resources.size();
        std::unordered_map<std::string, unsigned int>::iterator it = 
            ResourceManager::resources.begin();
        std::advance(it, random);
        std::vector<Quest::QuestDetails> quest_details;
        quest_details.push_back(Quest::QuestDetails());
        quest_details.back().resource_ = it->first;
        quest_details.back().amount_ = rand() % 5 + 1;
        Quest* quest = new Quest("I need " + it->first + "!", quest_details);
        AddQuest(npc, quest);
    }
}

std::vector<Quest*> QuestManager::GetNPCsQuests(NPC* npc)
{
    if (Quests_.find(npc) == Quests_.end()) {
        Quests_.insert(std::pair<NPC*, std::vector<Quest*>>(npc, std::vector<Quest*>()));
    }
    return Quests_[npc];
}

void QuestManager::DeleteQuest(Quest* quest, NPC* npc)
{
    std::vector<Quest*> npc_quests = Quests_[npc];
    std::vector<Quest*>::iterator quest_position = std::find(npc_quests.begin(), npc_quests.end(), quest);
    if (quest_position != npc_quests.end()) {
        npc_quests.erase(quest_position);
    }
    Quests_[npc] = npc_quests;
}

void QuestManager::AddQuest(NPC* npc, Quest* quest)
{
    if (Quests_.find(npc) == Quests_.end()) {
        Quests_.insert(std::pair<NPC*, std::vector<Quest*>>(npc, std::vector<Quest*>()));
    }
    Quests_[npc].push_back(quest);
}
