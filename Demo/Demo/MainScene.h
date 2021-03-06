#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "NPC.h"
#include "Enemy.h"
#include "Player.h"
#include "Button.h"
#include "Grid.h"
#include "TurnManager.h"
#include "CharacterManager.h"

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

	CharacterManager character_manager_;

	//The grid object.
	Grid grid_;
};

