#pragma once
#include "Scene.h"
#include "GridObject.h"
#include "NPC.h"
#include "Enemy.h"
#include "Player.h"
#include "Button.h"
#include "Grid.h"
#include "TurnManager.h"
#include "CharacterManager.h"
#include "LocationManager.h"
#include "LocationScene.h"

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();
	void Init();
	void Release();
	bool Update(float dt);
	void Render();

private:
	//Render the UI.
	void RenderUI();

	//The turn manager handles what factions turn it is and what phase an enemy is in.
	TurnManager turn_manager_;

	LocationScene* location_scene_ = nullptr;

	CharacterManager character_manager_;

	//The grid object.
	Grid* grid_;

	const sf::Vector2f task_size_ = sf::Vector2f(500.0f, 200.0f);

	LocationManager* location_manager_;
};

