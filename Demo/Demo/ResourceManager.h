#pragma once
#include <unordered_map>

class ResourceManager
{
public:
	static bool AddResource(std::string resource_name, int resource_amount);
	static bool CanSubtractResource(std::string resource_name, int resource_amount);
	static std::unordered_map<std::string, unsigned int> resources;
};

