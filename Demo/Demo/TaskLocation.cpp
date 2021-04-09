#include "TaskLocation.h"

TaskLocation::TaskLocation(Node* node, sf::Texture* texture) :
	Location(node, texture)
{
}

void TaskLocation::AddAction(Task* task)
{
	Task_.push_back(task);
}

void TaskLocation::RenderLocation()
{
	for (int i = 0; i < Task_.size(); i++) {
		Task_[i]->Render();
		Task_[i]->RenderExtra();
	}
}

void TaskLocation::SetUpLocation()
{
	if (Task_.size() > 0) {
		float sizeY = Task_[0]->getSize().y;
		float positionY = 5.0f;
		for (int i = 0; i < Task_.size(); i++) {
			Task_[i]->SetUpPositionOnScreen(sf::Vector2f(500.0f, positionY));
			positionY += sizeY + 5.0f;
		}
	}
}

void TaskLocation::Update(float dt)
{
	for (int i = 0; i < Task_.size(); i++) {
		if (Task_[i]->ButtonPressed()) {
			return;
		}
	}
}
