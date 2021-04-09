#pragma once
#include <string>
#include <vector>
#include "ResourceManager.h"
#include "ThingsToDoAtLocation.h"

class Quest : public ThingsToDoAtLocation
{
public:
	struct QuestDetails {
		bool complete = false;
		std::string type_;
		std::string action_resource_;
		int amount_;
	};
	Quest(std::string quest_name, std::vector<QuestDetails> Quest_Requirements, ResourceManager* resource_manager);
	bool DoAction();

private:
	ResourceManager* resource_manager_ = nullptr;
	std::vector<QuestDetails> Quest_Requirements_;
};

