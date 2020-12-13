#include "GridPiece.h"
#include "Grid.h"

GridPiece::GridPiece(sf::Texture* main_texture, sf::Texture* added_texture, 
	Node* node)
{
	grid_node_ = node;

	//Set up the main grid piece.
	setTexture(main_texture);
	setSize(sf::Vector2f(Grid::grid_spacing_, Grid::grid_spacing_));
	setOrigin(getSize() / 2.0f);
	setPosition(grid_node_->getPosition());
	if (!main_texture) {
		setFillColor(sf::Color::Cyan);
	}

	//Set up the added grid piece.
	added_.setTexture(added_texture);
	added_.setSize(sf::Vector2f(Grid::grid_spacing_, Grid::grid_spacing_));
	added_.setPosition(grid_node_->getPosition());

	hitbox_.height = Grid::grid_spacing_;
	hitbox_.width = Grid::grid_spacing_;
	hitbox_.top = grid_node_->getPosition().y - getSize().y / 2.0f;
	hitbox_.left = grid_node_->getPosition().x - getSize().x / 2.0f;

}

bool GridPiece::Collision(sf::Vector2f mouse_position)
{
	if (hitbox_.contains(mouse_position)) {
		return true;
	}
	return false;
}

void GridPiece::Render(sf::RenderWindow* window)
{
	if (added_.getTexture()) {
		window->draw(added_);
	}
}
