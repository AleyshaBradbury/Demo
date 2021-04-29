#include "LocationManager.h"
#include "Grid.h"
#include "NPC.h"

LocationManager::~LocationManager()
{
	DeleteAllQuestLocations();

	while (Task_Locations_.size() > 0) {
		delete Task_Locations_.back();
		Task_Locations_.back() = nullptr;
		Task_Locations_.pop_back();
	}
}

void LocationManager::DeleteAllQuestLocations()
{
	while (Quest_Locations_.size() > 0) {

		delete Quest_Locations_.back();
		Quest_Locations_.back() = nullptr;
		Quest_Locations_.pop_back();
	}
}

void LocationManager::CreateQuestLocations(Grid* grid, const CharacterManager* character_manager_, 
	QuestManager* quest_manager)
{
	for (auto npc : character_manager_->Npcs_) {
		Quest_Locations_.push_back(new QuestLocation(npc, npc->GetGridNode(), nullptr, quest_manager));
		for (int i = 0; i < 4; i++) {
			Node* neighbour = npc->GetGridNode()->GetNeighbour(i);
			if (neighbour) {
				neighbour->SetLocation(Quest_Locations_.back());
			}
		}
	}
}

void LocationManager::CreateTaskLocations(Grid* grid)
{
	task_location_texture_.loadFromFile("gfx/exclamationMark.png");
	Task_Locations_.push_back(new TaskLocation(
		grid->GetNodeAtPositionOrClosest(sf::Vector2i(3, 3)),
		&task_location_texture_));
	Task_Locations_.back()->AddAction(new Task("Collect Wood", "wood", 1));
	Task_Locations_.push_back(new TaskLocation(
		grid->GetNodeAtPositionOrClosest(sf::Vector2i(-3, 3)),
		&task_location_texture_));
	Task_Locations_.back()->AddAction(new Task("Collect Food", "food", 1));
	Task_Locations_.push_back(new TaskLocation(
		grid->GetNodeAtPositionOrClosest(sf::Vector2i(-3, -3)),
		&task_location_texture_));
	Task_Locations_.back()->AddAction(new Task("Mine Ore", "ore", 1));
	Task_Locations_.push_back(new TaskLocation(
		grid->GetNodeAtPositionOrClosest(sf::Vector2i(3, -3)),
		&task_location_texture_));
	Task_Locations_.back()->AddAction(new Task("Collect Stone", "stone", 1));
}

void LocationManager::DeleteQuestLocation(QuestLocation* quest_location)
{
	for (int i = 0; i < Quest_Locations_.size(); i++) {
		if (Quest_Locations_[i] == quest_location) {
			delete Quest_Locations_[i];
			Quest_Locations_[i] = nullptr;
			Quest_Locations_.erase(Quest_Locations_.begin() + i);
			return;
		}
	}
}
