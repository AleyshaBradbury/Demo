#include "NPC.h"
#include <iostream>
#include <math.h>
#include "Grid.h"

NPC::NPC(std::string name, int health, sf::Vector2f position, 
	sf::Texture* texture, CharacterManager* character_manager,
	int movements, int attacks, QuestManager* quest_manager) :
	Character(name, health, position, texture, character_manager,
		movements, attacks)
{
	quest_manager_ = quest_manager;
}

NPC::~NPC()
{
	for (int i = 0; i < 4; i++) {
		if (grid_node_->GetNeighbour(i)) {
			grid_node_->GetNeighbour(i)->SetLocation(nullptr);
		}
	}
}

void NPC::DoAction(float dt, Grid* grid)
{
	quest_manager_->GenerateQuests(this);
	TurnManager::DetermineCharacterTurn();
	if (rescued_time_ > 0) {
		rescued_time_--;
	}
}

void NPC::IncrementNeeds()
{
	for (auto& need : Needs_) {
		need.second = std::min((int)need.second + 1, 9);
	}
}

void NPC::AddNeed(std::string name)
{
	//Insert a need into the needs map.
	Needs_.insert(std::pair<std::string, int>(name, rand() % 10));
}

std::unordered_map<std::string, uint32_t> NPC::GetAllNeeds()
{
	return Needs_;
}

void NPC::AddCompletedQuest(Quest* quest)
{
	completed_quests_.push_back(quest);
	character_manager_->ChangeRelationshipsAfterQuest(this);
}

std::vector<Quest*> NPC::GetCompletedQuests()
{
	return completed_quests_;
}

void NPC::AddRelationshipWithCharacter(std::string character_name, unsigned int rel)
{
	if (Relationship_.find(character_name) == Relationship_.end()) {
		Relationship_.insert(std::pair<std::string, unsigned int>(character_name, rel));
	}
}

unsigned int NPC::GetRelationshipWithCharacter(std::string character_name)
{
	return Relationship_[character_name];
}

void NPC::ChangeRelationshipWithCharacter(std::string character_name, int change)
{
	if (Relationship_.find(character_name) != Relationship_.end()) {
		Relationship_[character_name] = 
			(uint32_t)fminf(fmaxf(Relationship_[character_name] + change, 0), 9);
	}
}

std::unordered_map<std::string, uint32_t> NPC::GetRelationships()
{
	return Relationship_;
}
