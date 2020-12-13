#pragma once
#include <unordered_map>
#include "Node.h"
#include "GameObject.h"

class Pathfinding
{
public:
	Node* AddNode(sf::Vector2i node_position);
	void FindAvailableNodes(GameObject* game_object);
	std::vector<Node*> Pathfind(Node* start_node, sf::Vector2i end);
	void RenderMoveableArea(sf::RenderWindow* window);
	void RenderNodes(sf::RenderWindow* window);
	
	Node* FindNodeByPosition(sf::Vector2i grid_position);
	int FindNodeNumByPosition(sf::Vector2i grid_position);

	void InvertShowNodes();
	
private:
	//Returns the estimated distance between the start and end node.
	float h(sf::Vector2i start, sf::Vector2i end);
	//Returns the distance between the neighbouring nodes.
	float d(Node* end);
	void CreateMoveableArea();
	
	bool show_nodes_ = false;
	std::vector<Node*> Nodes_;

	bool show_moveable_area_ = true;
	std::vector<Node*> Moveable_Nodes_;
	sf::ConvexShape moveable_area_;
};

