#pragma once
#include "Scene.h"
#include "Location.h"

class LocationScene : public Scene
{
public:
	LocationScene();
	void OnEnterLocation();
	bool Update(float dt);
	void Render();

private:
	Location* location_ = nullptr;
};

