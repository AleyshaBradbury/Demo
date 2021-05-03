#pragma once
#include "Scene.h"
#include "Location.h"
#include "CharacterManager.h"

class LocationScene : public Scene
{
public:
	LocationScene(CharacterManager* character_manager_);
	void OnEnterLocation();
	bool Update(float dt);
	void Render();

private:
	Location* location_ = nullptr;
	CharacterManager* character_manager_;
};

