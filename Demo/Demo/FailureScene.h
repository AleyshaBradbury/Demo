#pragma once
#include "Scene.h"
#include "Button.h"

class FailureScene : public Scene
{
public:
	FailureScene(sf::RenderWindow* window, sf::Font* font);
	bool Update(float dt);
	void Render();
private:
	Button* to_menu_button_;
};

