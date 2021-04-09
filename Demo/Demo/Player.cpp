#include "Player.h"
#include "Input.h"
#include "CharacterManager.h"
#include "Grid.h"
#include "SceneManager.h"

Player::Player(float health, sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, 
	CharacterManager* character_manager) :
	Character("player", health, size, position, texture, character_manager)
{
	sf::Vector2f button_size(105.0f, 35.0f);
	turn_button_ = new Button("End Turn",
		sf::Vector2f(GeneralVariables::window_.getSize().x - button_size.x - 10.0f, 10.0f),
		button_size, 20);
}

Player::~Player()
{
	delete turn_button_;
	turn_button_ = NULL;
}

GridObject* Player::DoAction(float dt, Grid* grid)
{
	if (Input::GetMouseLeftDown()) {
		Node* node = grid->GridCollision(GeneralVariables::window_.mapPixelToCoords(Input::GetMouse(), grid->grid_view_));
		//If the end turn button is pressed. 
		if (turn_button_->Collision(GeneralVariables::window_.mapPixelToCoords(Input::GetMouse()))) {
			//Forget old memories.
			ForgetMemories();
			//Increment needs for all NPCs.
			for (int i = 0; i < character_manager_->Npcs_.size(); i++) {
				character_manager_->Npcs_[i]->IncrementNeeds();
			}

			TurnManager::DetermineCharacterTurn();
		}
		else if (node) {
			CheckIfSpaceEmptyAndResolve(node, grid);
		}
		Input::SetMouseLeftDown(false);
	}

	//If the spacebar is pressed and the player is on a location, enter that location.
	if (Input::GetKeyDown(sf::Keyboard::Space) && grid->CheckIfLocation(GetGridNode())) {
		Input::SetKeyUp(sf::Keyboard::Space);
		return nullptr;
	}
	else if (Input::GetKeyDown(sf::Keyboard::E)) {
		Input::SetKeyUp(sf::Keyboard::E);
		SceneManager::ChangeScene(SceneManager::Scene::StatsAndInventory);
		return nullptr;
	}
	return nullptr;
}

void Player::RenderTurnButton()
{
	GeneralVariables::window_.draw(*turn_button_);
	turn_button_->RenderButtonText();
}

void Player::CheckIfSpaceEmptyAndResolve(Node* node, Grid* grid)
{
	//If the player is in the node selected.
	if (GetGridNode() == node) {
		selected_character_ = character_manager_->player_;
		character_manager_->player_->InvertMoveable();
		return;
	}

	//If an NPC is in the node selected.
	for (int i = 0; i < character_manager_->Npcs_.size(); i++) {
		if (character_manager_->Npcs_[i]->GetGridNode() == node) {
			selected_character_ = character_manager_->Npcs_[i];
			character_manager_->Npcs_[i]->InvertMoveable();
			return;
		}
	}

	//If an enemy is in the node selected.
	for (int i = 0; i < character_manager_->Enemies_.size(); i++) {
		if (character_manager_->Enemies_[i]->GetGridNode() == node) {
			selected_character_ = character_manager_->Enemies_[i];
			character_manager_->Enemies_[i]->InvertMoveable();
			return;
		}
	}

	//If nobody is in the node selected then move to that node.
	grid->MoveCharacter(this, node);
}
