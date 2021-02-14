#include "Scene.h"

Scene::Scene(sf::RenderWindow* window, sf::Font* font)
{
	window_ = window;
	font_ = font;
}

void Scene::StartDraw()
{
	//Clear the window to black.
	window_->clear(sf::Color::Black);
}

void Scene::EndDraw()
{
	//Display the frame in the window.
	window_->display();
}
