#pragma once
#include "ThingsToDoAtLocation.h"

class Task : public ThingsToDoAtLocation
{
public:
	struct TaskDetails {
		//What item the task will give or what action the task will complete.
		std::string thing_collected_;
		//How much of an item the task will give or how many times the action is completed.
		int thing_per_task_ = 1;
	};
public:
	Task(std::string task_name, std::string thing_collected, int thing_per_task);
	std::string GetTaskName();
	bool DoAction();
	void RenderExtra();

private:
	//The name of the task. This is used for quest generation purposes.
	std::string task_name_;
	TaskDetails task_details_;
	
};

