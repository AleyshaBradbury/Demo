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


	void InitialiseCharacter(Character* character, sf::Vector2i node_position);
	bool MoveCharacter(Character* character, Node* node);
	void MoveCharacter(Character* character, sf::Vector2i node_position);
	void MoveCharacterTowardsTarget(Character* character, GameObject* target);
	Node* GridCollision(sf::Vector2f mouse_position);
	void CreateMap(std::string file_name);

	void SetGameObjectPositionOnGrid(GameObject* game_object, sf::Vector2i position_on_grid);
	void SetGameObjectPositionOnGrid(GameObject* game_object, Node* target_node);

	void RenderGridPieces(sf::RenderWindow* window);
	
	//Static variables.
	//The distance between nodes/size of grid pieces.
	static const float grid_spacing_;

private:
	sf::Texture* LoadTexture(std::string texture_name);

	//Grid piece variables.
	std::vector<GridPiece*> Grid_Pieces_;
	std::vector<sf::Texture*> Main_Textures_;
	std::vector<sf::Texture*> Sub_Textures_;

	//Pathfinding variables.
	Pathfinding pathfinding_;
};