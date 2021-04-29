#include "MainScene.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include "TurnManager.h"
#include "GeneralFunctions.h"
#include "TaskLocation.h"

namespace fs = std::filesystem;

MainScene::MainScene()
{
	location_manager_ = new LocationManager();
	grid_ = new Grid(location_manager_);
	location_manager_->CreateTaskLocations(grid_);

	//Set up the view.
	grid_->grid_view_.setSize((sf::Vector2f)GeneralVariables::window_.getSize());
	grid_->grid_view_.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	grid_->grid_view_.setCenter(sf::Vector2f(0.0f, 0.0f));

	TurnManager::character_manager_ = &character_manager_;
}

MainScene::~MainScene()
{
	Release();
	delete grid_;
	grid_ = nullptr;
}

void MainScene::Init()
{
	//Set the values for the size of the grid pieces and the size of the characters.
	float grid_spacing = Grid::grid_spacing_;

	//Set up player.
	character_manager_.player_ = new Player(20.0f, sf::Vector2f(), nullptr,
		&character_manager_, 1, 1);
	character_manager_.player_->setFillColor(sf::Color::Green);
	grid_->InitialiseCharacter(character_manager_.player_, sf::Vector2i(0, 0));
	turn_manager_.character_turn_ = character_manager_.player_;
	turn_manager_.StartTurn(character_manager_.player_);

	for (auto& p : fs::directory_iterator("NPCs")) {
		character_manager_.CreateNPCFromFile(p.path().string(), grid_);
	}

	//Set up enemy.
	character_manager_.Enemies_.push_back(new Enemy(40.0f, sf::Vector2f(), nullptr,
		&character_manager_, 1, 1));
	character_manager_.Enemies_.back()->setFillColor(sf::Color::Red);
	grid_->InitialiseCharacter(character_manager_.Enemies_.back(), sf::Vector2i(3, 3));

	//Set up the quest manager and pass in managers into classes as needed.
	quest_manager_ = new QuestManager(&character_manager_);
	location_manager_->CreateQuestLocations(grid_, &character_manager_, quest_manager_);
	turn_manager_.turn_ = TurnManager::Turn::Player;
	character_manager_.SetLocationManager(location_manager_);
}

void MainScene::Release()
{
	location_manager_->DeleteAllQuestLocations();
	delete quest_manager_;
	quest_manager_ = nullptr;
	character_manager_.DeleteAll();
}

bool MainScene::Update(float dt)
{
	Character* c = grid_->MovementAnimation(dt);
	if (turn_manager_.character_turn_) {
		if (!c) {
			turn_manager_.character_turn_->DoAction(dt, grid_);
		}
		grid_->grid_view_.setCenter(turn_manager_.character_turn_->getPosition());
	}
	return false;
}

void MainScene::Render()
{
	StartDraw();

	if (grid_) {
		//Set the view to have the centre on the player.
		GeneralVariables::window_.setView(grid_->grid_view_);

		//Render the grid.
		grid_->RenderGridPieces();
	}

	//Render all of the characters.
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

	if (turn_manager_.character_turn_) {
		turn_manager_.character_turn_->RenderIcons();
	}

	//Render the end turn button.
	if (turn_manager_.turn_ == TurnManager::Turn::Player) {
		character_manager_.player_->RenderTurnButton();
	}
}
