#include "GridObject.h"
#include "GeneralFunctions.h"
#include "GeneralVariables.h"

GridObject::GridObject(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, GameObject* parent) :
	GameObject(size, position, texture, parent)
{
	setOrigin(size / 2.0f);
	health_text_.setCharacterSize(30.0f);
	health_text_.setFillColor(sf::Color::White);
	health_text_.setFont(GeneralVariables::font_);
	health_text_.setOutlineColor(sf::Color::Black);
	health_text_.setOutlineThickness(2.0f);

	ResetHealth();
}

void GridObject::SetGridNode(Node* grid_position)
{
	grid_node_ = grid_position;
}

Node* GridObject::GetGridNode()
{
	return grid_node_;
}

bool GridObject::isOverlap()
{
	return overlap_;
}

void GridObject::ResetHealth()
{
	health_ = max_health_;
	SetHealthText();
}

bool GridObject::SubtractHealth(int health)
{
	health_ -= health;
	SetHealthText();
	if (health_ <= 0) {
		return true;
	}
	return false;
}

int GridObject::GetHealth()
{
	return health_;
}

void GridObject::RenderHealthText()
{
	GeneralVariables::window_.draw(health_text_);
}

void GridObject::MoveObject(sf::Vector2f position)
{
	setPosition(position);
	health_text_.setPosition(position - sf::Vector2f(9.0f, 20.0f));
}

void GridObject::SetHealthText()
{
	health_text_.setString(std::to_string(health_));
}
