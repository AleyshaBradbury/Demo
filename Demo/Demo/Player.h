#pragma once
#include "Character.h"
#include "Button.h"

class Player : public Character
{
public:
	Player(float health, sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, 
		CharacterManager* character_manager);
	~Player();
	GridObject* DoAction(float dt, Grid* grid);
	void RenderTurnButton();
private:
	void CheckIfSpaceEmptyAndResolve(Node* node, Grid* grid);
	//Changes the turn from the players to the enemies.
	Button* turn_button_ = nullptr;

	//The character that has been clicked on.
	Character* selected_character_ = nullptr;
};