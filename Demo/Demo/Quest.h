#pragma once
#include <string>
#include <vector>
#include "ThingsToDoAtLocation.h"

class Quest : public ThingsToDoAtLocation
{
public:
	struct QuestDetails {
		std::string resource_;
		int amount_;
	};
	Quest(std::string quest_name, std::vector<QuestDetails> Quest_Requirements);
	bool DoAction();
	void RenderExtra();

	std::vector<QuestDetails> GetRequirements();

private:
	std::vector<QuestDetails> Quest_Requirements_;
};

