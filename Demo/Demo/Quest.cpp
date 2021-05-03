#include "Quest.h"
#include "GeneralVariables.h"
#include "ResourceManager.h"

Quest::Quest(std::string quest_name, std::vector<QuestDetails> Quest_Requirements) :
	ThingsToDoAtLocation()
{
	Quest_Requirements_ = Quest_Requirements;

	setSize(getSize() + sf::Vector2f(0.0f, 22.0f * Quest_Requirements_.size() - 1));

	title_.setString(quest_name);
	std::string details;
	for (auto requirement : Quest_Requirements_) {
		details += std::to_string(requirement.amount_) + " " + requirement.resource_ + "\n";
	}
	setSize(sf::Vector2f(getSize().x,
		getSize().y + Quest_Requirements_.size() * (other_text_size_ + 2)));
	other_text_.setString(details);
}

bool Quest::DoAction()
{
	//Check if all of the task requirements are doable.
	for (auto task : Quest_Requirements_) {
		if (!ResourceManager::CanSubtractResource(task.resource_, -task.amount_)) {
			return false;
		}
	}

	for (auto task : Quest_Requirements_) {
		ResourceManager::AddResource(task.resource_, -task.amount_);
	}
	return true;
}

void Quest::RenderExtra()
{
}

std::vector<Quest::QuestDetails> Quest::GetRequirements()
{
	return Quest_Requirements_;
}
