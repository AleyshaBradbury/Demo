#pragma once
#include "Input.h"
#include "Button.h"
#include "Pathfinding.h"
#include <map>
#include "LocationManager.h"

class Enemy;

class Grid
{
public:
	Grid(LocationManager* location_manager);
	~Grid();

	void InitialiseCharacter(Character* character, sf::Vector2i node_position);
	bool MoveCharacter(Character* character, Node* node);
	void MoveCharacter(Character* character, sf::Vector2i node_position);
	void MoveCharacterTowardsTarget(Character* character, GridObject* target);
	Character* MovementAnimation(float dt);
	Node* GridCollision(sf::Vector2f mouse_position);
	bool CheckIfInRange(Node* node1, Node* node2, int max_distance);

	void CreateMap(std::string file_name);
	void AddLocation(sf::Vector2i node_position);
	void AddLocation(Node* node);
	bool CheckIfLocation(Node* current_node);

	void SetGridObjectPositionOnGrid(GridObject* game_object, sf::Vector2i position_on_grid);
	void SetGridObjectPositionOnGrid(GridObject* game_object, Node* target_node);
	void SetCharacterPositionOnGrid(Character* character, sf::Vector2i position_on_grid);
	void SetCharacterPositionOnGrid(Character* character, Node* target_node);

	//Find closest target for the enemy.
	GridObject* FindClosestTarget(GridObject* enemy);

	void RenderGridPieces();
	void RenderLocationIndicators();
	
	//Static variables.
	//The distance between nodes/size of grid pieces.
	static const float grid_spacing_;

	//The view of the grid so that the camera can be focused on the active character.
	static sf::View grid_view_;

private:
	sf::Texture* LoadTexture(std::string texture_name);

	LocationManager* location_manager_ = nullptr;

	//The texture for locations.
	sf::Texture location_texture_;

	//
	//Grid piece variables.
	//

	//Nodes vector.
	std::vector<Node*> Nodes_;
	//A vector of all of the main grid piece textures.
	std::vector<sf::Texture*> Main_Textures_;
	//A vector of all of the sub textures for the grid pieces.
	std::map<std::string, sf::Texture*> Sub_Textures_;

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