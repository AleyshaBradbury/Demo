#include "LocationScene.h"

LocationScene::LocationScene()
{
}

void LocationScene::OnEnterLocation()
{
	location_ = SceneManager::GetLocation();
	location_->SetUpLocation();
}

bool LocationScene::Update(float dt)
{
	if (Input::GetMouseLeftDown()) {
		location_->Update(dt);
	}
	else if (Input::GetKeyDown(sf::Keyboard::Escape)) {
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
	EndDraw();
}
