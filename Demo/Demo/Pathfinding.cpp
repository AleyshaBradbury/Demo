#include "Pathfinding.h"
#include "Grid.h"
#include <iostream>

Node*  Pathfinding::AddNode(sf::Vector2i node_position)
{
	//Create the new node.
	Node* node = new Node(node_position);

	//Make a map of all the positions around the node.
	std::unordered_map<int, sf::Vector2i> Surrounding_positions;
	Surrounding_positions.insert(std::pair<int, sf::Vector2i>
		(0, sf::Vector2i(0, -1) + node_position));
	Surrounding_positions.insert(std::pair<int, sf::Vector2i>
		(1, sf::Vector2i(1, 0) + node_position));
	Surrounding_positions.insert(std::pair<int, sf::Vector2i>
		(2, sf::Vector2i(0, 1) + node_position));
	Surrounding_positions.insert(std::pair<int, sf::Vector2i>
		(3, sf::Vector2i(-1, 0) + node_position));

	//If a node neighbours the new node, make them neighbours.
	for (int i = 0; i < Nodes_.size(); i++) {
		if (Nodes_[i]->GetNumNeighbours() != 4) {
			for (auto& position : Surrounding_positions) {
				if (Nodes_[i]->GetGridPosition() == position.second) {
					node->AddNeighbour(Nodes_[i], position.first);
					int r_index = position.first + 2;
					r_index = r_index > 3 ? r_index - 4 : r_index;
					Nodes_[i]->AddNeighbour(node, r_index);
					Surrounding_positions.erase(position.first);
					break;
				}
			}
			if (node->GetNumNeighbours() == 4) {
				break;
			}
		}
	}
	Nodes_.push_back(node);
	Node** nodes = Nodes_.back()->GetNeighbours();

	return node;
}

void Pathfinding::FindAvailableNodes(GameObject* game_object)
{
	Moveable_Nodes_.push_back(Nodes_[0]);
	CreateMoveableArea();
}

std::vector<Node*> Pathfinding::Pathfind(Node* start_node, sf::Vector2i end)
{

	//
	//A* algorithm.
	//

	//The vector which will hold the final path.
	std::vector<Node*> Path;

	//Find the nodes for the end position.
	Node* end_node = FindNodeByPosition(end);

	if (!start_node || !end_node) {
		return Path;
	}

	//
	//Create the different vectors and maps for the algorithm.
	//

	std::vector<Node*> Open_Set;
	Open_Set.push_back(start_node);

	std::map<Node*, Node*> Previous_Node;

	std::map<Node*, float> gScore;
	gScore.insert(std::pair<Node*, float>(start_node, 0.0f));
	std::map<Node*, float> fScore;
	gScore.insert(std::pair<Node*, float>(start_node, h(start_node->GetGridPosition(), end)));

	while (Open_Set.size() > 0) {
		Node* current = Open_Set[0];
		//Find the node with the lowest fScore and current to it.
		for (int i = 1; i < Open_Set.size(); i++) {
			if (fScore[current] > fScore[Open_Set[i]]) {
				current = Open_Set[i];
			}
		}

		//If current is the end node.
		if (current == end_node) {

			//Reconstruct the path by making a vector of the nodes to visit to reach there.
			Path.push_back(current);
			while (true) {
				if (Previous_Node[current] == start_node) {
					return Path;
				}
				Path.insert(Path.begin(), Previous_Node[current]);
				current = Previous_Node[current];
			}
		}

		//Delete the current node from the open set.
		for (int i = 0; i < Open_Set.size(); i++) {
			if (Open_Set[i] == current) {
				Open_Set.erase(Open_Set.begin() + i);
				break;
			}
		}

		//Get the nodes neighbours and then itterate through them.
		Node** neighbours = current->GetNeighbours();
		for (int i = 0; i < 4; i++) {
			//If the neighbour exists.
			if (neighbours[i]) {
				//Calculate the currentG by adding the gScore for the current node and the
				//distance between current node and neighbour node.
				float currentG = gScore[current] + d(neighbours[i]);
				if (gScore.find(neighbours[i]) == gScore.end()) {
					gScore.insert(std::pair<Node*, float>(neighbours[i], 1000));
				}
				//If currentG is better than previous g for the neighbour.
				if (currentG < gScore[neighbours[i]]) {
					Previous_Node[neighbours[i]] = current;
					//If there is not already an entry for that node then create it and set it.
					gScore[neighbours[i]] = h(neighbours[i]->GetGridPosition(), end);
					//If the fScore for that node already exists then set it to it,
					//otherwise create it and then set it.
					fScore[neighbours[i]] =
						currentG + h(neighbours[i]->GetGridPosition(), end);
					//If the neighbour isnt already in the open set then add it.
					if (std::find(Open_Set.begin(), Open_Set.end(), neighbours[i]) == Open_Set.end()) {
						Open_Set.push_back(neighbours[i]);
					}
				}
			}

		}
	}
	Path.clear();
	return Path;
}

void Pathfinding::RenderMoveableArea(sf::RenderWindow* window)
{
	window->draw(moveable_area_);
}

void Pathfinding::RenderNodes(sf::RenderWindow* window)
{
	if (show_nodes_) {
		for (int i = 0; i < Nodes_.size(); i++) {
			window->draw(*Nodes_[i]);
		}
	}
}

Node* Pathfinding::FindNodeByPosition(sf::Vector2i grid_position)
{
	for (int i = 0; i < Nodes_.size(); i++) {
		if (Nodes_[i]->GetGridPosition() == grid_position) {
			return Nodes_[i];
		}
	}
	return NULL;
}

int Pathfinding::FindNodeNumByPosition(sf::Vector2i grid_position)
{
	for (int i = 0; i < Nodes_.size(); i++) {
		if (Nodes_[i]->GetGridPosition() == grid_position) {
			return i;
		}
	}
	return -1;
}

void Pathfinding::InvertShowNodes()
{
	show_nodes_ = !show_nodes_;
}


float Pathfinding::h(sf::Vector2i start, sf::Vector2i end)
{
	return abs(start.x - end.x) + abs(start.y - end.y);
}

float Pathfinding::d(Node* end)
{
	return end->GetDistance();
}

void Pathfinding::CreateMoveableArea()
{
}
