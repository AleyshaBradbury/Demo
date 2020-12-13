#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GeneralFunctions.h"

using namespace std;

class InfoWindow : public sf::RectangleShape
{
public:
	InfoWindow(sf::RenderWindow* window, sf::Font* font);
	bool Collsion(sf::Vector2f mousePosition);
	void Render(sf::RenderWindow* window);

	bool isAlive();
	void SetAlive(bool a);
	void ShowWindow(string text);
private:
	bool alive = false;
	sf::Text windowText;
	Button* windowButton;

	int maxLineSize = 21;
};

