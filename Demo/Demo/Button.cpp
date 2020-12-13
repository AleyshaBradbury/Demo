#include "Button.h"

Button::Button(std::string nameText_, sf::Vector2f position,
	sf::Vector2f size, sf::Font* font, float fontSize, sf::Vector2f textPosition, 
	sf::Color color, sf::Color textColor)
{
	nameText.setString(nameText_);
	nameText.setCharacterSize(fontSize);
	nameText.setFont(*font);
	nameText.setFillColor(textColor);
	nameText.setPosition(position.x + textPosition.x, position.y + textPosition.y);

	hitbox.left = position.x;
	hitbox.top = position.y;
	hitbox.height = size.y;
	hitbox.width = size.x;

	setPosition(position);
	setSize(size);
	setFillColor(color);
}

bool Button::Collision(sf::Vector2f mousePosition)
{
	if (hitbox.contains(mousePosition)) {
		return true;
	}
	return false;
}

void Button::RenderButtonText(sf::RenderWindow* window)
{
	window->draw(nameText);
}

void Button::SetPosition(sf::Vector2f position_)
{
	sf::Vector2f difference = getPosition() - position_;
	setPosition(position_);
	nameText.setPosition(nameText.getPosition().x - difference.x, nameText.getPosition().y - difference.y);
	hitbox.left = position_.x;
	hitbox.top = position_.y;
}

std::string Button::GetButtonName()
{
	return nameText.getString();
}
