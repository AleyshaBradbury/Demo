#include "Grid.h"
#include <iostream>
#include <queue>
#include <sstream>
#include <fstream>
#include "GeneralFunctions.h"

Grid::Grid()
{
	Main_Textures_.push_back(LoadTexture("gfx/grassyPlane.png"));
	Main_Textures_.push_back(LoadTexture("gfx/sandyPlane.png"));
	Main_Textures_.push_back(LoadTexture("gfx/stonePlane.png"));
	Sub_Textures_.push_back(LoadTexture("gfx/hut.png"));
	Sub_Textures_.push_back(LoadTexture("gfx/loneMountain.png"));

	CreateMap("maps/test.csv");
}

Grid::~Grid()
{
}

void Grid::InitialiseCharacter(Character* character, sf::Vector2i node_position)
{
	Node* node = pathfinding_.FindNodeByPosition(node_position);
	SetGameObjectPositionOnGrid(character, node);
	pathfinding_.FindAvailableNodes(character);
}

bool Grid::MoveCharacter(Character* character, Node* node)
{
	if (character && node &&
		std::find(character->Moveable_Nodes_.begin(), character->Moveable_Nodes_.end(),
		node) != character->Moveable_Nodes_.end()) {
		movement_nodes_ = pathfinding_.Pathfind(character->GetGridNode(), node);
		moving_character_ = character;
		previous_movement_node_ = character->GetGridNode();
		return true;
	}
	return false;
}

void Grid::MoveCharacter(Character* character, sf::Vector2i node_position)
{
	Node* node = pathfinding_.FindNodeByPosition(node_position);
	MoveCharacter(character, node);
}

void Grid::MoveCharacterTowardsTarget(Character* character, GameObject* target)
{
	//Find the path between the two points. max_distance == 1000 because its irellevant.
	std::vector<Node*> Path = pathfinding_.Pathfind(character->GetGridNode(),
		target->GetGridNode(), 1000);
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

bool Grid::MovementAnimation(float dt)
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
			SetGameObjectPositionOnGrid(moving_character_, previous_movement_node_);
			pathfinding_.FindAvailableNodes(moving_character_);
			moving_character_->AddMemory("Moved");
			moving_character_ = nullptr;
			movement_timer_ = 0.0f;
			return false;
		}
	}
	return true;
}

Node* Grid::GridCollision(sf::Vector2f mouse_position)
{
	for (int i = 0; i < Grid_Pieces_.size(); i++) {
		if (Grid_Pieces_[i]->Collision(mouse_position)) {
			return Grid_Pieces_[i]->GetGridNode();
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
			if (row.size() > 3) {
				sub_texture = Sub_Textures_[std::stoi(row[3])];
			}
			Node* node = pathfinding_.AddNode(sf::Vector2i(positionX, positionY));
			Grid_Pieces_.push_back(new GridPiece(main_texture, sub_texture, node));
		}
	}
}

void Grid::RenderGridPieces(sf::RenderWindow* window)
{
	for (int i = 0; i < Grid_Pieces_.size(); i++) {
		window->draw(*Grid_Pieces_[i]);
		Grid_Pieces_[i]->Render(window);
	}
}

void Grid::SetGameObjectPositionOnGrid(GameObject* game_object, sf::Vector2i position_on_grid)
{
	//Find the node for that game_object.
	Node* node = pathfinding_.FindNodeByPosition(position_on_grid);

	//If the node doesnt exist just place the game object on the (0,0) node.
	if (!node) {
		node = pathfinding_.FindNodeByPosition(sf::Vector2i(0, 0));
	}

	game_object->setPosition(node->getPosition());
	game_object->SetGridNode(node);
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

sf::Texture* Grid::LoadTexture(std::string texture_name)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(texture_name);
	
	return texture;
}
