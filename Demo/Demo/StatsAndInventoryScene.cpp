#include "StatsAndInventoryScene.h"
#include "ResourceManager.h"

StatsAndInventoryScene::StatsAndInventoryScene()
{
	text_.setFont(GeneralVariables::font_);
	text_.setCharacterSize(20);
	text_.setFillColor(sf::Color::White);
	text_.setPosition(5.0f, 5.0f);
}

bool StatsAndInventoryScene::Update(float dt)
{
	if (Input::GetKeyDown(sf::Keyboard::Escape)) {
		Input::SetKeyDown(sf::Keyboard::Escape);
		SceneManager::ChangeScene(SceneManager::Scene::Main);
		return true;
	}
	return false;
}

void StatsAndInventoryScene::Render()
{
	StartDraw();
	GeneralVariables::window_.draw(text_);
	EndDraw();
}

void StatsAndInventoryScene::OnEnter()
{
	std::string text_string_;
	for (auto resource : ResourceManager::resources) {
		text_string_ += resource.first + ": " + std::to_string(resource.second) + "\n";
	}
	text_.setString(text_string_);
}
