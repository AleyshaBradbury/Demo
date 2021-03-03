#pragma once
#include "Scene.h"

class LocationScene : public Scene
{
public:
	LocationScene(sf::RenderWindow* window, sf::Font* font);
	bool Update(float dt);
	void Render();

private:

};

