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
	void StartDraw();
	void EndDraw();
	void RenderUI();
	//Check if the space is empty and resolve actions based on that.
	void CheckIfSpaceEmptyAndResolve(Node* node, Character* character);
	sf::RenderWindow* window_;
	sf::View grid_view_;

	Character* player_;
	std::vector<NPC*> Npcs_;
	std::vector<Enemy*> Enemies_;

	Button* turn_button_; 
	Grid grid_;
};

