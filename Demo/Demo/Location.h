#pragma once
#include "SFML/Graphics.hpp"

class Node;

class Location
{
public:
	Location(Node* node, sf::Texture* texture);
	void Update(float dt);
	void Render();
	void RenderIndicatorOnMap();

private:
	sf::RectangleShape indicator_;
};

