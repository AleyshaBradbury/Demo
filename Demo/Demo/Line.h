#pragma once
#include <SFML/Graphics.hpp>

class Line
{
public:
	Line(std::vector<sf::Vector2f> points);
	void RenderLine(sf::RenderWindow* window);
private:
	sf::Vertex* line;
};

