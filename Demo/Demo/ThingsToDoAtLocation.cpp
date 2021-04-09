#include "ThingsToDoAtLocation.h"
#include "GeneralVariables.h"
#include "Input.h"

ThingsToDoAtLocation::ThingsToDoAtLocation() :
	GameObject(sf::Vector2f(298.0f, 100.0f), sf::Vector2f(0.0f, 0.0f), nullptr)
{
	setFillColor(sf::Color(100, 100, 100, 255));

	title_.setFont(GeneralVariables::font_);
	title_.setCharacterSize(30);

	other_text_.setFont(GeneralVariables::font_);
	other_text_.setCharacterSize(20);

	do_action_button_ = new Button("Do Action", sf::Vector2f(), sf::Vector2f(100.0f, 25.0f),
		20, sf::Vector2f(2, 2.5f));
}

bool ThingsToDoAtLocation::ButtonPressed()
{
	if (do_action_button_->Collision(GeneralVariables::window_.mapPixelToCoords(Input::GetMouse()))) {
		Input::SetMouseLeftDown(false);
		return DoAction();
	}
	return false;
}

void ThingsToDoAtLocation::Render()
{
	GeneralVariables::window_.draw(*this);
	GeneralVariables::window_.draw(title_);
	GeneralVariables::window_.draw(other_text_);
	GeneralVariables::window_.draw(*do_action_button_);
	do_action_button_->RenderButtonText();
}

void ThingsToDoAtLocation::SetUpPositionOnScreen(sf::Vector2f position)
{
	setPosition(position);
	title_.setPosition(position + sf::Vector2f(5.0f, 2.0f));
	other_text_.setPosition(position + sf::Vector2f(5.0f, 40.0f));
	do_action_button_->SetPosition(position + sf::Vector2f(195.0f, getSize().y - 30.0f));
}
