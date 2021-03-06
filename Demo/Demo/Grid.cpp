#include "Grid.h"
#include <iostream>
#include <queue>
#include <sstream>
#include <fstream>
#include "GeneralFunctions.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "GeneralVariables.h"

Grid::Grid()
{
	location_texture_.loadFromFile("gfx/exclamationMark.png");

	Main_Textures_.push_back(LoadTexture("gfx/grassyPlane.png"));
	Main_Textures_.push_back(LoadTexture("gfx/sandyPlane.png"));
	Main_Textures_.push_back(LoadTexture("gfx/stonePlane.png"));
	Sub_Textures_.insert(std::pair<string, sf::Texture*>("hut", LoadTexture("gfx/hut.png")));
	Sub_Textures_.insert(std::pair<string, sf::Texture*>("mountain", LoadTexture("gfx/loneMountain.png")));

	CreateMap("maps/test.csv");
}

Grid::~Grid()
{
}

void Grid::InitialiseCharacter(Character* character, sf::Vector2i node_position)
{
	Node* node = pathfinding_.FindNodeByPosition(node_position, Nodes_);
	SetCharacterPositionOnGrid(character, node);
	pathfinding_.FindAvailableNodes(character, Nodes_);
}

bool Grid::MoveCharacter(Character* character, Node* node)
{
	if (character && node &&
		std::find(character->Moveable_Nodes_.begin(), character->Moveable_Nodes_.end(),
		node) != character->Moveable_Nodes_.end()) {
		movement_nodes_ = pathfinding_.Pathfind(character->GetGridNode(), node, Nodes_);
		moving_character_ = character;
		previous_movement_node_ = character->GetGridNode();
		return true;
	}
	return false;
}

void Grid::MoveCharacter(Character* character, sf::Vector2i node_position)
{
	Node* node = pathfinding_.FindNodeByPosition(node_position, Nodes_);
	MoveCharacter(character, node);
}

void Grid::MoveCharacterTowardsTarget(Character* character, GameObject* target)
{
	//Find the path between the two points. max_distance == 1000 because its irellevant.
	std::vector<Node*> Path = pathfinding_.Pathfind(character->GetGridNode(),
		target->GetGridNode(), Nodes_, 1000);
	if (Path.size() > 0) {
		Node* node_position = nullptr;
		do {
			if (target->isOverlap()) {
				node_position = Path[Path.size() - 1];
			}
			else if (Path.size() > 1) {
				node_position = Path[Path.size() - 2];
			}
			Path.pop_back();
		} while (node_position && !MoveCharacter(character, node_position));
	}
}

Character* Grid::MovementAnimation(float dt)
{
	//If there is a character which should be moving.
	if (moving_character_) {
		if (movement_nodes_.size() > 0) {
			movement_timer_ += dt;
			moving_character_->setPosition(GeneralFunctions::LerpVector2(
				previous_movement_node_->getPosition(),
				movement_nodes_.front()->getPosition(),
				movement_timer_ / max_movement_timer_));
			if (movement_timer_ >= max_movement_timer_) {
				movement_timer_ = 0.0f;
				previous_movement_node_ = movement_nodes_.front();
				movement_nodes_.erase(movement_nodes_.begin());
			}
		}
		else {
			//Move the character.
			SetCharacterPositionOnGrid(moving_character_, previous_movement_node_);
			pathfinding_.FindAvailableNodes(moving_character_, Nodes_);
			moving_character_->AddMemory("Moved");
			moving_character_ = nullptr;
			movement_timer_ = 0.0f;
		}
	}
	return moving_character_;
}

Node* Grid::GridCollision(sf::Vector2f mouse_position)
{
	for (int i = 0; i < Nodes_.size(); i++) {
		if (Nodes_[i]->Collision(mouse_position)) {
			return Nodes_[i];
		}
	}
	return NULL;
}

void Grid::CreateMap(std::string file_name)
{
	//
	//Reading the map from file.
	//

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

		if (row.size() > 2) {
			int positionX = std::stoi(row[0]);
			int positionY = std::stoi(row[1]);
			sf::Texture* main_texture = Main_Textures_[std::stoi(row[2])];
			sf::Texture* sub_texture = NULL;
			if (row.size() > 3 && Sub_Textures_.find(row[3]) != Sub_Textures_.end()) {
				sub_texture = Sub_Textures_[row[3]];
			}
			Nodes_.push_back(new Node(sf::Vector2i(positionX, positionY), main_texture,
				sub_texture));;
			pathfinding_.SetupNode(Nodes_.back(), Nodes_);
		}
	}
}

void Grid::AddLocation(sf::Vector2i node_position)
{
	Node* node = pathfinding_.FindNodeByPosition(node_position, Nodes_);
	AddLocation(node);
}

void Grid::AddLocation(Node* node)
{
	if (node) {
		node->SetLocation(new Location(node, &location_texture_));
	}
}

bool Grid::CheckIfLocation(Node* current_node)
{
	Location* location = current_node->GetLocation();
	if (location) {
		SceneManager::ChangeScene(SceneManager::Scene::Location);
		SceneManager::SetLocation(location);
		return true;
	}
	return false;
}

bool Grid::CheckIfInRange(Node* node1, Node* node2, int max_distance)
{
	float distanceX = abs(node1->GetGridPosition().x - node2->GetGridPosition().x);
	float distanceY = abs(node1->GetGridPosition().y - node2->GetGridPosition().y);

	if (distanceX + distanceY <= max_distance) {
		return true;
	}
	return false;
}

GameObject* Grid::FindClosestTarget(Enemy* enemy)
{
	GameObject* closest_object = nullptr;
	float closest_distance_ = 10000.0f;
	//For every node, check if there is a character on that tile.
	for (int i = 0; i < Nodes_.size(); i++) {
		Character* character = Nodes_[i]->GetCharacterOnTile();
		if (character && character != enemy) {
			//Get the distance between the character and the enemy.
			float distance = GeneralFunctions::DistanceBetweenTwoObjects(
				enemy->GetGridNode()->GetGridPosition(), character->GetGridNode()->GetGridPosition());
			//If the character is closer than the current closest set the character to
			//be the current closest.
			if (distance < closest_distance_) {
				closest_distance_ = distance;
				closest_object = character;
			}
		}
	}
	return closest_object;
}

void Grid::RenderGridPieces()
{
	for (int i = 0; i < Nodes_.size(); i++) {
		GeneralVariables::window_.draw(*Nodes_[i]);
		Nodes_[i]->Render();
	}
}

void Grid::RenderLocationIndicators()
{
	for (int i = 0; i < Nodes_.size(); i++) {
		Location* location = Nodes_[i]->GetLocation();
		if (location) {
			location->RenderIndicatorOnMap();
		}
	}
}

void Grid::SetGameObjectPositionOnGrid(GameObject* game_object, sf::Vector2i position_on_grid)
{
	//Find the node for that game_object.
	Node* node = pathfinding_.FindNodeByPosition(position_on_grid, Nodes_);

	SetGameObjectPositionOnGrid(game_object, node);
}

void Grid::SetGameObjectPositionOnGrid(GameObject* game_object, Node* target_node)
{
	if (target_node) {
		game_object->setPosition(
			target_node->GetGridPosition().x * grid_spacing_ + grid_spacing_ / 2.0f,
			target_node->GetGridPosition().y * grid_spacing_ + grid_spacing_ / 2.0f);
		game_object->SetGridNode(target_node);
	}
}

void Grid::SetCharacterPositionOnGrid(Character* character, sf::Vector2i position_on_grid)
{
	//Find the node for that game_object.
	Node* node = pathfinding_.FindNodeByPosition(position_on_grid, Nodes_);
	SetCharacterPositionOnGrid(character, node);
}

void Grid::SetCharacterPositionOnGrid(Character* character, Node* target_node)
{
	if (target_node) {
		character->SetGridNode(target_node);
		target_node->SetCharacterOnTile(character);
	}
}

sf::Texture* Grid::LoadTexture(std::string texture_name)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(texture_name);
	
	return texture;
}
