#include "Line.h"

Line::Line(std::vector<sf::Vector2f> points)
{
	line = new sf::Vertex[points.size()];
	for (int i = 0; i < points.size(); i++) {
		line[i].position = points[i];
	}
}

void Line::RenderLine(sf::RenderWindow* window)
{
	window->draw(line, 2, sf::Lines);
}
