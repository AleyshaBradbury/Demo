#pragma once
#include "Location.h"
#include "Task.h"

class LocationManager
{
public:
	void AddLocation(Location* location);

private:
	std::vector<Location*> locations_;
};

