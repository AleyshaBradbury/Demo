#pragma once
#include "SFML/Graphics.hpp"
#include "Node.h"

class Location
{
public:
	Location(Node* node, sf::Texture* texture);
	void Update(float dt);
	void Render(sf::RenderWindow* window);
	void RenderIndicatorOnMap(sf::RenderWindow* window);

private:
	sf::RectangleShape indicator_;
};

