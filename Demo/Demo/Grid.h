#pragma once
#include "Input.h"
#include "Button.h"
#include "Pathfinding.h"
#include "GridPiece.h"
#include "Character.h"

class Grid
{
public:
	Grid();
	~Grid();
	void InitialiseShowNodesButton(sf::Font* font);

	void StartTurn(Character* game_object);
	Node* GridCollision(sf::Vector2f mouse_position);
	void CreateMap(std::string file_name);

	void SetGameObjectPositionOnGrid(GameObject* game_object, sf::Vector2i position_on_grid);
	void SetGameObjectPositionOnGrid(GameObject* game_object, Node* target_node);

	void RenderGridPieces(sf::RenderWindow* window);
	void RenderNodes(sf::RenderWindow* window);
	void RenderShowNodesButton(sf::RenderWindow* window);

	bool InvertShowNodes(sf::Vector2f mouse_pos);
	
	//Static variables.
	//The distance between nodes/size of grid pieces.
	static const float grid_spacing_;

private:
	void LoadTexture(std::string texture_name);

	//Grid piece variables.
	std::vector<GridPiece*> Grid_Pieces_;
	std::vector<sf::Texture*> Textures_;

	//Pathfinding variables.
	Pathfinding pathfinding_;
	Button* show_nodes_button_;
};