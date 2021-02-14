#include "MainScene.h"
#include <iostream>
#include "Memories.h"
#include "TurnManager.h"
#include "GeneralFunctions.h"

MainScene::MainScene(sf::RenderWindow* window, sf::Font* font) : 
	Scene(window, font)
{
	//Set up the view.
	grid_view_.setSize((sf::Vector2f)window_->getSize());
	grid_view_.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	grid_view_.setCenter(sf::Vector2f(0.0f, 0.0f));
	
	//Set the values for the size of the grid pieces and the size of the characters.
	float grid_spacing = Grid::grid_spacing_;
	float character_size = grid_spacing / 5.0f * 4.0f;

	//Set up player.
	player_ = new Character("Player", 20.0f);
	player_->setSize(sf::Vector2f(character_size, character_size));
	player_->setFillColor(sf::Color::Green);
	player_->setOrigin(character_size / 2.0f, character_size / 2.0f);
	grid_.InitialiseCharacter(player_, sf::Vector2i(0, 0));

	//Set up npc.
	Npcs_.push_back(new NPC("Joey", 20.0f));
	Npcs_.back()->setSize(sf::Vector2f(character_size, character_size));
	Npcs_.back()->setFillColor(sf::Color::Blue);
	Npcs_.back()->setOrigin(character_size / 2.0f, character_size / 2.0f);
	grid_.InitialiseCharacter(Npcs_.back(), sf::Vector2i(0, 1));

	//Set up enemy.
	Enemies_.push_back(new Enemy(20.0f));
	Enemies_.back()->setSize(sf::Vector2f(character_size, character_size));
	Enemies_.back()->setFillColor(sf::Color::Red);
	Enemies_.back()->setOrigin(character_size / 2.0f, character_size / 2.0f);
	grid_.InitialiseCharacter(Enemies_.back(), sf::Vector2i(3, 3));

	sf::Vector2f button_size(105.0f, 35.0f);
	turn_button_ = new Button("End Turn", 
		sf::Vector2f(window_->getSize().x - button_size.x - 10.0f, 10.0f),
		button_size, font, 20);

	grid_.InitialiseShowNodesButton(font);
}

MainScene::~MainScene()
{
	delete turn_button_;
	turn_button_ = NULL;

	for (int i = 0; i < Enemies_.size(); i++) {
		delete Enemies_.back();
		Enemies_.pop_back();
	}

	for (int i = 0; i < Npcs_.size(); i++) {
		delete Npcs_.back();
		Npcs_.pop_back();
	}

	delete player_;
	player_ = NULL;
}

void MainScene::Update(float dt)
{
	switch (TurnManager::turn_) {
	case TurnManager::Turn::Player:
		PlayerTurn(dt);
		break;
	case TurnManager::Turn::Enemy:
		EnemyTurn(dt);
		break;
	case TurnManager::Turn::NPC:
		NPCTurn(dt);
		break;
	}
}

void MainScene::Render()
{
	StartDraw();

	if (!window_) {
		return;
	}
	//Set the view to have the centre on the player.
	window_->setView(grid_view_);

	//Render the grid.
	grid_.RenderGridPieces(window_);
	
	//Render moveable area for all characters.
	for (int i = 0; i < Npcs_.size(); i++) {
		Npcs_[i]->RenderMoveableArea(window_);
	}

	for (int i = 0; i < Enemies_.size(); i++) {
		Enemies_[i]->RenderMoveableArea(window_);
	}

	player_->RenderMoveableArea(window_);
	

	//Render every npc.
	for (int i = 0; i < Npcs_.size(); i++) {
		if (Npcs_[i]) {
			window_->draw(*Npcs_[i]);
		}
	}
	
	//Render every enemy.
	for (int i = 0; i < Enemies_.size(); i++) {
		if (Enemies_[i]) {
			window_->draw(*Enemies_[i]);
		}
	}

	//Render the player
	if (player_) {
		window_->draw(*player_);
	}

	//Reset View
	window_->setView(window_->getDefaultView());

	RenderUI();
	EndDraw();
}

void MainScene::RenderUI()
{
	//
	//Render the UI elements.
	//

	//Render the end turn button.
	if (turn_manager_.turn_ == TurnManager::Turn::Player) {
		window_->draw(*turn_button_);
		turn_button_->RenderButtonText(window_);
	}
}

void MainScene::PlayerTurn(float dt)
{
	if (Input::GetMouseLeftDown()) {
		Node* node = grid_.GridCollision(window_->mapPixelToCoords(Input::GetMouse(), grid_view_));
		//If the end turn button is pressed. 
		if (turn_button_->Collision(window_->mapPixelToCoords(Input::GetMouse()))) {
			//Forget old memories.
			player_->ForgetMemories();
			//Increment needs for all NPCs.
			for (int i = 0; i < Npcs_.size(); i++) {
				Npcs_[i]->IncrementNeeds();
			}

			//Show the memories the player has in the console.
			//FOR DEBUGGING AND FEASIBILITY ONLY! DELETE LATER!
			std::vector<Memories::Memory> Player_Memories = player_->GetMemories();
			std::cout << "Players Memories\n";
			for (int i = 0; i < Player_Memories.size(); i++) {
				std::cout << "	" << Player_Memories[i].what_happened_ << " at position (" <<
					Player_Memories[i].where_it_happened_->GetGridPosition().x << "," <<
					Player_Memories[i].where_it_happened_->GetGridPosition().y << ") " <<
					Player_Memories[i].turns_ago_ << " turns ago\n";
			}
			turn_manager_.IncrementTurn();
		}
		else if (node) {
			CheckIfSpaceEmptyAndResolve(node, player_);
			grid_view_.setCenter(player_->GetGridNode()->getPosition());
		}
		grid_.InvertShowNodes(window_->mapPixelToCoords(Input::GetMouse()));
		Input::SetMouseLeftDown(false);
	}
}

void MainScene::EnemyTurn(float dt)
{
	switch (turn_manager_.enemy_turn_)
	{
	case TurnManager::EnemyTurn::FindTarget:
		//Find the closest target.
		Enemies_[turn_num_]->SetTarget(FindClosestTarget(Enemies_[turn_num_]));
		turn_manager_.IncrementEnemyTurn();
		break;
	case TurnManager::EnemyTurn::Movement:
		if (Enemies_[turn_num_]->GetTarget()) {
			grid_.MoveCharacterTowardsTarget(Enemies_[turn_num_], Enemies_[turn_num_]->GetTarget());
		}
		turn_manager_.IncrementEnemyTurn();
		break;
	case TurnManager::EnemyTurn::Attack:
		turn_manager_.IncrementEnemyTurn();
		break;
	}
	if (turn_manager_.enemy_turn_ == TurnManager::EnemyTurn::FindTarget) {
		turn_num_++;
	}
	if (turn_num_ == Enemies_.size()) {
		turn_manager_.IncrementTurn();
		turn_num_ = 0;
	}
}

//Find the character or place that is closest to the enemy.
GameObject* MainScene::FindClosestTarget(Enemy* enemy)
{
	GameObject* closest_object = player_;
	float shortest_distance = GeneralFunctions::DistanceBetweenTwoObjects(
		enemy->GetGridNode()->GetGridPosition(), player_->GetGridNode()->GetGridPosition());

	for (int i = 0; i < Npcs_.size(); i++) {
		float distance = GeneralFunctions::DistanceBetweenTwoObjects(
			enemy->GetGridNode()->GetGridPosition(), Npcs_[i]->GetGridNode()->GetGridPosition());
		if (distance < shortest_distance) {
			shortest_distance = distance;
			closest_object = Npcs_[i];
		}
	}
	return closest_object;
}

void MainScene::NPCTurn(float dt)
{
	turn_manager_.IncrementTurn();
}

//When clicking on a space to move, check if that space is empty and resolve from that.
void MainScene::CheckIfSpaceEmptyAndResolve(Node* node, Character* character)
{
	//If the player is in the node selected.
	if (player_->GetGridNode() == node) {
		selected_character_ = player_;
		player_->InvertMoveable();
		return;
	}

	//If an NPC is in the node selected.
	for (int i = 0; i < Npcs_.size(); i++) {
		if (Npcs_[i]->GetGridNode() == node) {
			selected_character_ = Npcs_[i];
			Npcs_[i]->InvertMoveable();
			return;
		}
	}

	//If an enemy is in the node selected.
	for (int i = 0; i < Enemies_.size(); i++) {
		if (Enemies_[i]->GetGridNode() == node) {
			selected_character_ = Enemies_[i];
			Enemies_[i]->InvertMoveable();
			return;
		} 
	}

	//If nobody is in the node selected then move to that node.
	grid_.MoveCharacter(character, node);
}
