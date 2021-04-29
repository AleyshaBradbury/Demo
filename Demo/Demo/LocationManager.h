#pragma once
#include "TaskLocation.h"
#include "QuestLocation.h"
#include "Task.h"
#include "CharacterManager.h"

class Grid;

class LocationManager
{
public:
	~LocationManager();
	void DeleteAllQuestLocations();
	void CreateQuestLocations(Grid* grid, const CharacterManager* character_manager_,
		QuestManager* quest_manager);
	void CreateTaskLocations(Grid* grid);
	void DeleteQuestLocation(QuestLocation* quest_location);

private:
	std::vector<TaskLocation*> Task_Locations_;
	std::vector<QuestLocation*> Quest_Locations_;
	sf::Texture task_location_texture_;
};

