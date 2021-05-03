#include "LocationScene.h"

LocationScene::LocationScene(CharacterManager* character_manager)
{
	character_manager_ = character_manager;
	failed_action_text_.setCharacterSize(30);
	failed_action_text_.setFont(GeneralVariables::font_);
	failed_action_text_.setFillColor(sf::Color::White);
	failed_action_text_.setPosition(100.0f, 60.0f);
	failed_action_text_.setString("Unable to perform\naction");
}

void LocationScene::OnEnterLocation()
{
	location_ = SceneManager::GetLocation();
	location_->SetUpLocation();
	failed_action_timer_ = 0.0f;
}

bool LocationScene::Update(float dt)
{
	if (failed_action_timer_ >= 0.0f) {
		failed_action_timer_ -= dt;
	}

	if (Input::GetMouseLeftDown()) {
		Input::SetMouseLeftDown(false);
		if (character_manager_->player_->GetAction() > 0 &&
			location_->Update(dt, character_manager_->player_)) {
			character_manager_->player_->SpendAction();
		}
		else {
			failed_action_timer_ = 1.0f;
		}
	}

	if (Input::GetKeyDown(sf::Keyboard::Escape)) {
		Input::SetKeyUp(sf::Keyboard::Escape);
		SceneManager::ChangeScene(SceneManager::Scene::Main);
		return true;
	}
	return false;
}

void LocationScene::Render()
{
	StartDraw();
	location_->RenderLocation();
	character_manager_->player_->RenderIcons();
	if (failed_action_timer_ >= 0.0f) {
		GeneralVariables::window_.draw(failed_action_text_);
	}
	EndDraw();
}
