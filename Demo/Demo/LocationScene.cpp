#include "LocationScene.h"

LocationScene::LocationScene(sf::RenderWindow* window, sf::Font* font) :
	Scene(window, font)
{
}

bool LocationScene::Update(float dt)
{
	return false;
}

void LocationScene::Render()
{
	StartDraw();
	EndDraw();
}
