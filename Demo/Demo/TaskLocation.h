#pragma once
#include "Location.h"
#include "Task.h"

class TaskLocation : public Location
{
public:
	TaskLocation(Node* node, sf::Texture* texture);
	void AddAction(Task* task);
	void RenderLocation();

	void SetUpLocation();
	void Update(float dt);

private:
	std::vector<Task*> Task_;
};

