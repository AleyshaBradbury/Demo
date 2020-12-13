#include "InfoWindow.h"

InfoWindow::InfoWindow(sf::RenderWindow* window, sf::Font* font)
{
	//Initialise the info window.
	setSize(sf::Vector2f(300.0f, 200.0f));
	setPosition(window->getSize().x / 2.0f - getSize().x / 2.0f,
		window->getSize().y / 2 - getSize().y / 2.0f);
	setFillColor(sf::Color(200.0f, 200.0f, 200.0f, 255.0f));

	windowButton = new Button("Close",
		sf::Vector2f(window->getSize().x / 2.0f - 50.0f, window->getSize().y / 2.0f + 25.0f),
		sf::Vector2f(100.0f, 50.0f), font, 25, sf::Vector2f(13.0f, 10.0f), sf::Color::White);

	windowText.setCharacterSize(20);
	windowText.setPosition(window->getSize().x / 2 - 120.0f, window->getSize().y / 2 - 50.0f);
	windowText.setFillColor(sf::Color::Black);
	windowText.setFont(*font);
}

bool InfoWindow::Collsion(sf::Vector2f mousePosition)
{
	if (windowButton->Collision(mousePosition)) {
		alive = false;
		return true;
	}
	return false;
}

void InfoWindow::Render(sf::RenderWindow* window)
{
	window->draw(*windowButton);
	window->draw(windowText);
	windowButton->RenderButtonText(window);
}

bool InfoWindow::isAlive()
{
	return alive;
}

void InfoWindow::SetAlive(bool a)
{
	alive = a;
}

void InfoWindow::ShowWindow(string text)
{
	alive = true;
	windowText.setString(GeneralFunctions::FormatLine(text, maxLineSize));
}
