#include "Location.h"
#include "SceneManager.h"
#include "Grid.h"
#include "Node.h"
#include "GeneralVariables.h"

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

void Location::Render()
{
}

void Location::RenderIndicatorOnMap()
{
	GeneralVariables::window_.draw(indicator_);
}
