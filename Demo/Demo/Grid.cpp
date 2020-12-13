#include "Grid.h"
#include <iostream>
#include <queue>
#include <sstream>
#include <fstream>

Grid::Grid()
{
	LoadTexture("gfx/grassyPlane.png");
	LoadTexture("gfx/sandyPlane.png");
	LoadTexture("gfx/stonePlane.png");
	LoadTexture("gfx/hut.png");
	LoadTexture("gfx/loneMountain.png");

	CreateMap("maps/map1.csv");
}

Grid::~Grid()
{
	delete show_nodes_button_;
	show_nodes_button_ = NULL;
}

void Grid::InitialiseShowNodesButton(sf::Font* font)
{
	sf::Vector2f button_size(105.0f, 35.0f);
	show_nodes_button_ = new Button("Show Nodes", sf::Vector2f(10.0f, 10.0f),
		button_size, font, 20);
}

void Grid::StartTurn(Character* character)
{
	pathfinding_.FindAvailableNodes(character);
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
			sf::Texture* main_texture = Textures_[std::stoi(row[2])];
			sf::Texture* sub_texture = NULL;
			if (row.size() > 3) {
				sub_texture = Textures_[std::stoi(row[3])];
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
	}
}

void Grid::RenderNodes(sf::RenderWindow* window)
{
	pathfinding_.RenderNodes(window);
}

void Grid::RenderShowNodesButton(sf::RenderWindow* window)
{
	//Render the show nodes button.
	if (show_nodes_button_) {
		window->draw(*show_nodes_button_);
		show_nodes_button_->RenderButtonText(window);
	}
}

bool Grid::InvertShowNodes(sf::Vector2f mouse_pos)
{
	if (show_nodes_button_->Collision(mouse_pos)) {
		pathfinding_.InvertShowNodes();
		return true;
	}
	return false;
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

void Grid::LoadTexture(std::string texture_name)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(texture_name);
	Textures_.push_back(texture);
}
