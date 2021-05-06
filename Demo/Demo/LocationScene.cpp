#include "LocationScene.h"

LocationScene::LocationScene(CharacterManager* character_manager, InfoWindow* info_window)
{
	character_manager_ = character_manager;
	info_window_ = info_window;
	failed_action_text_.setCharacterSize(30);
	failed_action_text_.setFont(GeneralVariables::font_);
	failed_action_text_.setFillColor(sf::Color::White);
	failed_action_text_.setPosition(500.0f, GeneralVariables::window_.getSize().y - 300.0f);
	failed_action_text_.setString("Unable to perform\naction!");
}

void LocationScene::OnEnterLocation()
{
	location_ = SceneManager::GetLocation();
	location_->SetUpLocation();
	failed_action_timer_ = 0.0f;
}

bool LocationScene::Update(float dt)
{
	if (info_window_->isAlive()) {
		info_window_->Collsion();
		return false;
	}
	if (failed_action_timer_ >= 0.0f) {
		failed_action_timer_ -= dt;
	}

	if (Input::GetMouseLeftDown()) {
		Input::SetMouseLeftDown(false);
		if (character_manager_->player_->GetAction() > 0 &&
			location_->Update(dt, character_manager_->player_)) {
			character_manager_->player_->SpendAction();
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
	if (info_window_->isAlive()) {
		info_window_->Render();
	}
	EndDraw();
}
