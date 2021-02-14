#include "MenuScene.h"
#include "SceneManager.h"

MenuScene::MenuScene(sf::RenderWindow* window, sf::Font* font) :
	Scene(window, font)
{
	sf::Vector2f button_size(200.0f, 70.0f);
	to_main_button_ = new Button("Start", 
		sf::Vector2f(window->getSize().x / 2.0f - button_size.x / 2.0f, 
		window->getSize().y / 4.0f * 3.0f - button_size.y / 2.0f), 
		button_size, font, 50, sf::Vector2f(30.0f, 5.0f));
}

void MenuScene::Update(float dt)
{
	if (Input::GetMouseLeftDown() &&
		to_main_button_->Collision(window_->mapPixelToCoords(Input::GetMouse()))) {
		Input::SetMouseLeftDown(false);
		SceneManager::ChangeScene(SceneManager::Scene::Main);
	}
}

void MenuScene::Render()
{
	StartDraw();
	window_->draw(*to_main_button_);
	to_main_button_->RenderButtonText(window_);
	EndDraw();
}
