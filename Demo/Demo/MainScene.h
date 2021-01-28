#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "NPC.h"
#include "Enemy.h"
#include "Button.h"
#include "Grid.h"

class MainScene
{
public:
	MainScene(sf::RenderWindow* window, sf::Font* font);
	~MainScene();
	void Update(float dt);
	void Render();

private:
	enum class Turn {
		Player,
		Enemy
	};
	//Render functions
	void StartDraw();
	void EndDraw();
	void RenderUI();
	
	void PlayerTurn(float dt);

	//Check if the space is empty and resolve actions based on that.
	void CheckIfSpaceEmptyAndResolve(Node* node, Character* character);

	//Main Variables
	sf::RenderWindow* window_ = nullptr;
	sf::View grid_view_;
	Turn turn = Turn::Player;

	//Character Variables
	Character* selected_character_ = nullptr;
	Character* player_ = nullptr;
	std::vector<NPC*> Npcs_;
	std::vector<Enemy*> Enemies_;

	Button* turn_button_ = nullptr; 
	Grid grid_;
};

