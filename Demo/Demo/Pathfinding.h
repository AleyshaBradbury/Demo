#pragma once
#include <unordered_map>
#include "Node.h"
#include "GameObject.h"
#include "Character.h"

class Pathfinding
{
public:
	Pathfinding();
	Node* AddNode(sf::Vector2i node_position);
	void FindAvailableNodes(Character* character);
	std::vector<Node*> Pathfind(Node* start_node, Node* end_node);
	void RenderNodes(sf::RenderWindow* window);
	
	Node* FindNodeByPosition(sf::Vector2i grid_position);
	int FindNodeNumByPosition(sf::Vector2i grid_position);
	void InvertShowNodes();
	
private:
	//Returns the estimated distance between the start and end node.
	float h(sf::Vector2i start, sf::Vector2i end);
	//Returns the distance between the neighbouring nodes.
	float d(Node* end);
	
	bool show_nodes_ = false;
	std::vector<Node*> Nodes_;

	//Moveable nodes variables.
	float max_distance_ = 0;
	std::vector<Node*> Nodes_To_Be_Checked_;
};

