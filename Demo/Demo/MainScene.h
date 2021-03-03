#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "NPC.h"
#include "Enemy.h"
#include "Button.h"
#include "Grid.h"
#include "TurnManager.h"

class MainScene : public Scene
{
public:
	MainScene(sf::RenderWindow* window, sf::Font* font);
	~MainScene();
	void Init();
	void Release();
	bool Update(float dt);
	void Render();

private:
	//Render the UI.
	void RenderUI();
	
	void PlayerTurn(float dt);
	void EnemyTurn(float dt);
	GameObject* FindClosestTarget(Enemy* enemy);
	void NPCTurn(float dt);

	void DeleteDeadObject(GameObject* target);

	//Check if the space is empty and resolve actions based on that.
	void CheckIfSpaceEmptyAndResolve(Node* node, Character* character);

	//The turn manager handles what factions turn it is and what phase an enemy is in.
	TurnManager turn_manager_;
	//The view of the grid so that the camera can be focused on the active character.
	sf::View grid_view_;

	//
	//Character Variables
	//

	//The character that has been clicked on.
	Character* selected_character_ = nullptr;
	//The player character.
	Character* player_ = nullptr;
	//The enemy or npc integer.
	int turn_num_ = 0;
	//A vector of npcs that are alive.
	std::vector<NPC*> Npcs_;
	//A vector of enemies that are alive.
	std::vector<Enemy*> Enemies_;

	//Changes the turn from the players to the enemies.
	Button* turn_button_ = nullptr; 
	//The grid object.
	Grid grid_;
};

