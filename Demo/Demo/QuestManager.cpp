#include "QuestManager.h"
#include "CharacterManager.h"
#include "ResourceManager.h"

QuestManager::QuestManager(CharacterManager* character_manager)
{
    character_manager_ = character_manager;
}

void QuestManager::GenerateQuests(NPC* npc)
{
    if (GetNPCsQuests(npc).size() == 0) {
        std::vector<Quest::QuestDetails> quest_details;
        quest_details.push_back(Quest::QuestDetails());
        quest_details.back().resource_ = DetermineResource();
        if (quest_details.back().resource_ != "") {
            quest_details.back().amount_ = rand() % 5 + 1;
            Quest* quest = new Quest("I need " + quest_details[0].resource_ + "!", quest_details);
            AddQuest(npc, quest);
        }
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

std::string QuestManager::DetermineResource()
{
    std::string resource = "";
    std::vector<Memories::Memory> memories = character_manager_->player_->GetMemories();
    for (int i = memories.size() - 1; i >= 0; i--) {
        if (memories[i].what_happened_[0] == "Task") {
            resource = memories[i].what_happened_[1];
            break;
        }
        else if (memories[i].what_happened_[0] == "Attack") {
            resource = character_manager_->GetEnemyDropByEnemyName(memories[i].what_happened_[1]);
            break;
        }
    }
    return resource;
}

void QuestManager::AddQuest(NPC* npc, Quest* quest)
{
    if (Quests_.find(npc) == Quests_.end()) {
        Quests_.insert(std::pair<NPC*, std::vector<Quest*>>(npc, std::vector<Quest*>()));
    }
    Quests_[npc].push_back(quest);
}
