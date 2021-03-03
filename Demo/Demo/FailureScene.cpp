#include "FailureScene.h"
#include "Input.h"
#include "SceneManager.h"

FailureScene::FailureScene(sf::RenderWindow* window, sf::Font* font) :
	Scene(window, font)
{
	sf::Vector2f button_size(200.0f, 70.0f);
	to_menu_button_ = new Button("To Menu",
		sf::Vector2f(window->getSize().x / 2.0f - button_size.x / 2.0f,
			window->getSize().y / 4.0f * 3.0f - button_size.y / 2.0f),
		button_size, font, 50, sf::Vector2f(30.0f, 5.0f));
}

bool FailureScene::Update(float dt)
{
	if (Input::GetMouseLeftDown() &&
		to_menu_button_->Collision(window_->mapPixelToCoords(Input::GetMouse()))) {
		Input::SetMouseLeftDown(false);
		SceneManager::ChangeScene(SceneManager::Scene::Menu);
		return true;
	}
	return false;
}

void FailureScene::Render()
{
	StartDraw();
	window_->draw(*to_menu_button_);
	to_menu_button_->RenderButtonText(window_);
	EndDraw();
}
