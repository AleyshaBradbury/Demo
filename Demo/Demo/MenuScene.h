#pragma once
#include "Scene.h"
#include "Button.h"

class MenuScene : public Scene
{
public:
	MenuScene(sf::RenderWindow* window, sf::Font* font);
	bool Update(float dt);
	void Render();

private:
	Button* to_main_button_ = nullptr;
};

