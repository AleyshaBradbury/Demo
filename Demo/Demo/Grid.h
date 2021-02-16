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
	bool MovementAnimation(float dt);
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

	//
	//Grid piece variables.
	//

	//Grid piece vector.
	std::vector<GridPiece*> Grid_Pieces_;
	//A vector of all of the main grid piece textures.
	std::vector<sf::Texture*> Main_Textures_;
	//A vector of all of the sub textures for the grid pieces.
	std::vector<sf::Texture*> Sub_Textures_;

	//Pathfinding object.
	Pathfinding pathfinding_;
	//The character which is moving.
	Character* moving_character_ = nullptr;
	//A vector of all the nodes still to be moved to for animation.
	std::vector<Node*> movement_nodes_;
	//The previous node the character visited.
	Node* previous_movement_node_ = nullptr;
	//The maximum time for movement between nodes.
	const float max_movement_timer_ = 0.2f;
	//The time past during movement between nodes.
	float movement_timer_ = 0.0f;
};