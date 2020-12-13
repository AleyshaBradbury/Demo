#include "GameObject.h"
#include "GeneralFunctions.h"

void GameObject::SetGridNode(Node* grid_position)
{
	grid_node_ = grid_position;
}

Node* GameObject::GetGridNode()
{
	return grid_node_;
}
