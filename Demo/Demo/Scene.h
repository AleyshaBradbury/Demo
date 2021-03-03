#pragma once
#include <SFML/Graphics.hpp>
#include "Input.h"
#include "SceneManager.h"

class Scene
{
public:
	Scene(sf::RenderWindow* window, sf::Font* font);
	virtual bool Update(float dt) = 0;
	virtual void Render() = 0;

protected:
	void StartDraw();
	void EndDraw();

	sf::RenderWindow* window_;
	sf::Font* font_;
};

