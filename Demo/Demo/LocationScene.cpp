#include "LocationScene.h"

LocationScene::LocationScene(CharacterManager* character_manager)
{
	character_manager_ = character_manager;
}

void LocationScene::OnEnterLocation()
{
	location_ = SceneManager::GetLocation();
	location_->SetUpLocation();
}

bool LocationScene::Update(float dt)
{
	if (character_manager_->player_->GetAction() > 0 && location_->Update(dt, 
		character_manager_->player_)) {
		character_manager_->player_->SpendAction();
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
	EndDraw();
}
