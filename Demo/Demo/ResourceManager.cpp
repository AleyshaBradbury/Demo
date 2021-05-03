#include "ResourceManager.h"

bool ResourceManager::AddResource(std::string resource_name, int resource_amount)
{
	//If the resource already exists in the characters inventory.
	if (resources.find(resource_name) != resources.end()) {
		int new_amount = resources[resource_name] + resource_amount;
		if (new_amount >= 0) {
			resources[resource_name] = new_amount;
			return true;
		}
	}
	//If the resource didnt already exist in the characters inventory.
	else {
		resources.insert(std::pair<std::string, int>(resource_name, 0));
		if (resource_amount >= 0) {
			resources[resource_name] = resource_amount;
			return true;
		}
	}
	return false;
}

bool ResourceManager::CanAddResource(std::string resource_name, int resource_amount)
{
	if (resources.find(resource_name) != resources.end()) {
		int new_amount = resources[resource_name] + resource_amount;
		if (new_amount >= 0) {
			return true;
		}
	}
	//If the resource didnt already exist in the characters inventory.
	else {
		resources.insert(std::pair<std::string, int>(resource_name, 0));
	}
	return false;
}
