#include "Location.h"
#include "SceneManager.h"
#include "Grid.h"

Location::Location(Node* node, sf::Texture* texture)
{
	indicator_.setSize(sf::Vector2f(Grid::grid_spacing_, Grid::grid_spacing_));
	indicator_.setOrigin(indicator_.getSize() / 2.0f);
	indicator_.setPosition(node->getPosition());
	indicator_.setTexture(texture);
}

void Location::Update(float dt)
{
}

void Location::Render(sf::RenderWindow* window)
{
}

void Location::RenderIndicatorOnMap(sf::RenderWindow* window)
{
	window->draw(indicator_);
}
