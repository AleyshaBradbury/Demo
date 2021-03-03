#pragma once
#include "GameObject.h"
#include "Location.h"

class GridPiece : public  GameObject
{
public:
	GridPiece(sf::Texture* main_texture, sf::Texture* added_texture, Node* node);
	bool Collision(sf::Vector2f mouse_position);
	bool SetLocation(Location* location);
	Location* GetLocation();
	bool EnterLocation();
	void Render(sf::RenderWindow* window);

private:
	GameObject added_;
	//The hitbox for clicking on the piece;
	sf::FloatRect hitbox_;

	Location* location_ = nullptr;
};

