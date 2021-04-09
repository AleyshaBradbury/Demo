#include "MainScene.h"
#include <iostream>
#include "Memories.h"
#include "TurnManager.h"
#include "GeneralFunctions.h"
#include "TaskLocation.h"

MainScene::MainScene()
{
	location_manager_ = new LocationManager();
	grid_ = new Grid(location_manager_);

	//Set up the view.
	grid_->grid_view_.setSize((sf::Vector2f)GeneralVariables::window_.getSize());
	grid_->grid_view_.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	grid_->grid_view_.setCenter(sf::Vector2f(0.0f, 0.0f));

	TurnManager::character_manager_ = &character_manager_;

	grid_->AddLocation(sf::Vector2i(4, 4));
}

MainScene::~MainScene()
{
	Release();
	delete grid_;
	grid_ = nullptr;
	delete location_manager_;
	location_manager_ = nullptr;
}

void MainScene::Init()
{
	//Set the values for the size of the grid pieces and the size of the characters.
	float grid_spacing = Grid::grid_spacing_;
	float character_size = grid_spacing / 5.0f * 4.0f;

	//Set up player.
	character_manager_.player_ = new Player(20.0f, 
		sf::Vector2f(character_size, character_size), sf::Vector2f(), nullptr,
		&character_manager_);
	character_manager_.player_->setFillColor(sf::Color::Green);
	grid_->InitialiseCharacter(character_manager_.player_, sf::Vector2i(0, 0));
	turn_manager_.character_turn_ = character_manager_.player_;
	turn_manager_.StartTurn(character_manager_.player_);

	//Set up npc.
	character_manager_.Npcs_.push_back(new NPC("Joey", 30.0f,
		sf::Vector2f(character_size, character_size), sf::Vector2f(), nullptr,
		&character_manager_));
	character_manager_.Npcs_.back()->setSize(sf::Vector2f(character_size, character_size));
	character_manager_.Npcs_.back()->setFillColor(sf::Color::Blue);
	character_manager_.Npcs_.back()->setOrigin(character_size / 2.0f, character_size / 2.0f);
	grid_->InitialiseCharacter(character_manager_.Npcs_.back(), sf::Vector2i(0, 1));

	//Set up enemy.
	character_manager_.Enemies_.push_back(new Enemy(40.0f,
		sf::Vector2f(character_size, character_size), sf::Vector2f(), nullptr,
		&character_manager_));
	character_manager_.Enemies_.back()->setSize(sf::Vector2f(character_size, character_size));
	character_manager_.Enemies_.back()->setFillColor(sf::Color::Red);
	character_manager_.Enemies_.back()->setOrigin(character_size / 2.0f, character_size / 2.0f);
	grid_->InitialiseCharacter(character_manager_.Enemies_.back(), sf::Vector2i(3, 3));
}

void MainScene::Release()
{
	character_manager_.DeleteAll();
}

bool MainScene::Update(float dt)
{
	Character* c = grid_->MovementAnimation(dt);
	if (!c) {
		turn_manager_.character_turn_->DoAction(dt, grid_);
	}
	else {
		grid_->grid_view_.setCenter(c->getPosition());
	}
	return false;
}

void MainScene::Render()
{
	StartDraw();

	//Set the view to have the centre on the player.
	GeneralVariables::window_.setView(grid_->grid_view_);

	grid_->RenderGridPieces();

	character_manager_.RenderAll();

	//Render the exclamation mark indicators for all locations on top of the moveable areas.
	grid_->RenderLocationIndicators();

	//Reset View
	GeneralVariables::window_.setView(GeneralVariables::window_.getDefaultView());

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
		character_manager_.player_->RenderTurnButton();
	}
}
