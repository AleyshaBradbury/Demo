#include "SceneManager.h"

void SceneManager::ChangeScene(Scene scene)
{
	scene_ = scene;
}

void SceneManager::ChangeScene(int index)
{
	scene_ = (Scene)index;
}

SceneManager::Scene SceneManager::GetScene()
{
	return scene_;
}

void SceneManager::SetLocation(Location* location)
{
	current_location_ = location;
}

Location* SceneManager::GetLocation()
{
	return current_location_;
}
