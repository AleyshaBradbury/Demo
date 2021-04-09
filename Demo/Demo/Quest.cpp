#include "Quest.h"
#include "GeneralVariables.h"

Quest::Quest(std::string quest_name, std::vector<QuestDetails> Quest_Requirements, ResourceManager* resource_manager) :
	ThingsToDoAtLocation()
{
	Quest_Requirements_ = Quest_Requirements;
	resource_manager_ = resource_manager;

	setSize(getSize() + sf::Vector2f(0.0f, 22.0f * Quest_Requirements_.size() - 1));

	title_.setString(quest_name);
	std::string details;
	for (auto requirement : Quest_Requirements_) {
		details += std::to_string(requirement.amount_) + " " + requirement.action_resource_ + "\n";
	}
}

bool Quest::DoAction()
{
	//Check if all of the task requirements are doable.
	for (auto task : Quest_Requirements_) {
		if (!task.complete) {
			if (task.type_ == "Resource") {
				if (!resource_manager_->AddResource(task.action_resource_, -task.amount_)) {
					return false;
				}
				else {
					task.complete = true;
				}
			}
		}
	}
	return true;
}
