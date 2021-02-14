#include <SFML/Graphics.hpp>
#include <ctime>
#include <stdlib.h> 
#include <time.h>
#include <stdio.h>
#include "Input.h"
#include "Grid.h"
#include "SceneManager.h"
#include "TurnManager.h"

#include "MenuScene.h"
#include "MainScene.h"

//
//Declaring Static Members
//

//Input static members.
bool Input::keys[256];
Input::Mouse Input::mouse;

//SceneManager static members.
SceneManager::Scene SceneManager::scene;

//Grid static members.
const float Grid::grid_spacing_ = 50.0f;

//Turn Manager statuc members.
TurnManager::Turn TurnManager::turn_ = TurnManager::Turn::Player;

int main() {
	sf::Vector2u window_size_(800, 800);
	//Create the window.
	sf::RenderWindow window(sf::VideoMode(window_size_.x, window_size_.y), "Demo");

	srand((int)time(NULL));

	//Initialise Clock Object.
	sf::Clock clock;

	//Initialse SceneManager Object.
	SceneManager::ChangeScene(SceneManager::Scene::Menu);

	//Initialise Input.
	Input::Init();

	//Initialise Font Object.
	sf::Font font;
	font.loadFromFile("fonts/consola.ttf");

	//Initialise Scene Objects.
	MenuScene menu_scene_(&window, &font);
	MainScene main_scene_(&window, &font);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setSize(window_size_);
				break;
			case sf::Event::KeyPressed:
				// update input class
				Input::SetKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				Input::SetKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				Input::SetMouseXPosition(event.mouseMove.x);
				Input::SetMouseYPosition(event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					Input::SetMouseLeftDown(true);
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//update input class
					Input::SetMouseRightDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					Input::SetMouseLeftDown(false);
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//update input class
					Input::SetMouseRightDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}
		float dt = clock.restart().asSeconds();

		switch (SceneManager::GetScene()) {
		case SceneManager::Scene::Menu:
			menu_scene_.Update(dt);
			menu_scene_.Render();
			break;
		case SceneManager::Scene::Main:
			main_scene_.Update(dt);
			main_scene_.Render();
			break;
		}
	}
}