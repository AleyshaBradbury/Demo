#include "CharacterManager.h"
#include "SceneManager.h"
#include <sstream>
#include <fstream>
#include "Grid.h"


void CharacterManager::DeleteAll()
{
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

void CharacterManager::DeleteDeadCharacter(Character* target)
{
	if (target == player_) {
		SceneManager::ChangeScene(SceneManager::Scene::Failure);
		return;
	}
	for (int i = 0; i < Npcs_.size(); i++) {
		if (target == Npcs_[i]) {
			for (int i = 0; i < 4; i++) {
				if (Npcs_[i]->GetGridNode()->GetNeighbour(i)) {
					location_manager_->DeleteQuestLocation((QuestLocation*)Npcs_[i]->GetGridNode()->GetNeighbour(i)->GetLocation());
					break;
				}
			}
			delete Npcs_[i];
			Npcs_.erase(Npcs_.begin() + i);
			return;
		}
	}

	for (int i = 0; i < Enemies_.size(); i++) {
		if (target == Enemies_[i]) {
			delete Enemies_[i];
			Enemies_.erase(Enemies_.begin() + i);
			return;
		}
	}
}

void CharacterManager::SetLocationManager(LocationManager* location_manager)
{
	location_manager_ = location_manager;
}

void CharacterManager::CreateNPCFromFile(std::string file_name, Grid* grid, QuestManager* quest_manager)
{
	//Read in the npcs data from file and then initialise that character onto the grid.
	std::string name = "";
	int max_health = 0;
	std::string texture_location;
	sf::Vector2i initial_position(0, 0);
	std::vector<std::string> Needs;

	std::fstream file;
	file.open(file_name);
	std::string line, word, temp;

	while (file >> temp) {
		std::vector<std::string> row;

		std::getline(file, line);
		temp += line;

		std::stringstream s(temp);

		while (std::getline(s, word, ',')) {
			row.push_back(word);
		}

		if (row.size() > 0) {
			if (row[0] == "name") {
				name = row[1];
			}
			else if (row[0] == "max health") {
				max_health = std::stoi(row[1]);
			}
			else if (row[0] == "texture location") {

			}
			else if (row[0] == "start position") {
				initial_position = sf::Vector2i(std::stoi(row[1]), std::stoi(row[2]));
			}
			else if (row[0] == "needs") {
				for (int i = 1; i < row.size(); i++) {
					Needs.push_back(row[i]);
				}
			}
		}
	}

	Npcs_.push_back(new NPC(name, max_health, sf::Vector2f(), nullptr, this, 1, 0, quest_manager));
	Npcs_.back()->setFillColor(sf::Color::Blue);
	for (int i = 0; i < Needs.size(); i++) {
		Npcs_.back()->AddNeed(Needs[i]);
 }
	grid->InitialiseCharacter(Npcs_.back(), initial_position);
}

void CharacterManager::RenderAll()
{
	for (int i = 0; i < Npcs_.size(); i++) {
		Npcs_[i]->RenderMoveableArea();
	}

	for (int i = 0; i < Enemies_.size(); i++) {
		Enemies_[i]->RenderMoveableArea();
	}

	if (player_) {
		player_->RenderMoveableArea();
	}

	//Render every npc.
	for (int i = 0; i < Npcs_.size(); i++) {
		if (Npcs_[i]) {
			GeneralVariables::window_.draw(*Npcs_[i]);
			Npcs_[i]->RenderHealthText();
		}
	}

	//Render every enemy.
	for (int i = 0; i < Enemies_.size(); i++) {
		if (Enemies_[i]) {
			GeneralVariables::window_.draw(*Enemies_[i]);
			Enemies_[i]->RenderHealthText();
		}
	}

	//Render the player
	if (player_) {
		GeneralVariables::window_.draw(*player_);
		player_->RenderHealthText();
	}
}
