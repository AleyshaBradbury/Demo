#include "SceneManager.h"

void SceneManager::ChangeScene(Scene scene_)
{
	scene = scene_;
}

void SceneManager::ChangeScene(int index)
{
	scene = (Scene)index;
}

SceneManager::Scene SceneManager::GetScene()
{
	return scene;
}
