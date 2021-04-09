#include "Task.h"
#include "GeneralVariables.h"
#include <string>
#include "ResourceManager.h"

Task::Task(std::string task_name, std::string thing_collected, int thing_per_task) :
	ThingsToDoAtLocation()
{
	task_name_ = task_name;
	task_details_.thing_collected_ = thing_collected;
	task_details_.thing_per_task_ = thing_per_task;
	
	title_.setString(task_name_);

	other_text_.setString("Gain " + std::to_string(thing_per_task) + " " + thing_collected + ".");
}

std::string Task::GetTaskName()
{
	return task_name_;
}

bool Task::DoAction()
{
	ResourceManager::AddResource(task_details_.thing_collected_, task_details_.thing_per_task_);
	return true;
}

void Task::RenderExtra()
{
}
