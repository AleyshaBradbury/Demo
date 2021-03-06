#include <SFML/Graphics.hpp>
#include <ctime>
#include <stdlib.h> 
#include <time.h>
#include <stdio.h>
#include "Input.h"
#include "Grid.h"
#include "SceneManager.h"
#include "TurnManager.h"
#include "GeneralVariables.h"

#include "MenuScene.h"
#include "MainScene.h"
#include "LocationScene.h"
#include "FailureScene.h"

//
//Declaring Static Members
//

//Input static members.
bool Input::keys[256];
Input::Mouse Input::mouse;

//SceneManager static members.
SceneManager::Scene SceneManager::scene_;
Location* SceneManager::current_location_;

//Grid static members.
const float Grid::grid_spacing_ = 50.0f;
sf::View Grid::grid_view_;

//Turn Manager static members.
TurnManager::Turn TurnManager::turn_ = TurnManager::Turn::Player;
int TurnManager::turn_num_ = 0;
Character* TurnManager::character_turn_ = nullptr;
CharacterManager* TurnManager::character_manager_ = nullptr;
bool TurnManager::was_moveable_ = false;

//General Variables static members.
sf::Vector2u window_size_(800, 800);
sf::RenderWindow GeneralVariables::window_(sf::VideoMode(window_size_.x, window_size_.y), "Demo");
sf::Font GeneralVariables::font_;

int main() {

	srand((int)time(NULL));

	//Initialise Clock Object.
	sf::Clock clock;

	//Initialse SceneManager Object.
	SceneManager::ChangeScene(SceneManager::Scene::Menu);

	//Initialise Input.
	Input::Init();

	
	GeneralVariables::font_.loadFromFile("fonts/consola.ttf");

	//Initialise Scene Objects.
	MenuScene menu_scene_;
	MainScene main_scene_;
	FailureScene failure_scene_;
	LocationScene location_scene_;

	while (GeneralVariables::window_.isOpen())
	{
		sf::Event event;
		while (GeneralVariables::window_.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				GeneralVariables::window_.close();
				break;
			case sf::Event::Resized:
				GeneralVariables::window_.setSize(window_size_);
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
			if (menu_scene_.Update(dt)) {
				main_scene_.Init();
			}
			menu_scene_.Render();
			break;
		case SceneManager::Scene::Main:
			main_scene_.Update(dt);
			main_scene_.Render();
			break;
		case SceneManager::Scene::Location:
			location_scene_.Update(dt);
			location_scene_.Render();
			break;
		case SceneManager::Scene::Failure:
			failure_scene_.Update(dt);
			failure_scene_.Render();
		}
	}
}