#pragma once
#include "Character.h"
#include "Button.h"

class Player : public Character
{
public:
	Player(int health, sf::Vector2f position, sf::Texture* texture, 
		CharacterManager* character_manager, int movements, int attacks);
	~Player();
	void DoAction(float dt, Grid* grid);
	void RenderTurnButton();

private:
	void CheckIfSpaceEmptyAndResolve(Node* node, Grid* grid);
	//Changes the turn from the players to the enemies.
	Button* turn_button_ = nullptr;
	Button* DEBUG_skip_to_start_of_players_turn_ = nullptr;

	//The character that has been clicked on.
	Character* selected_character_ = nullptr;
};