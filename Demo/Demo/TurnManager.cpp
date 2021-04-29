#include "TurnManager.h"
#include "Grid.h"
#include "CharacterManager.h"
#include "QuestManager.h"

void TurnManager::StartTurn(Character* character)
{
	was_moveable_ = character->GetMoveable();
	character->SetMoveable(true);
	Grid::grid_view_.setCenter(character->getPosition());
}

void TurnManager::EndTurn(Character* character)
{
	character->SetMoveable(was_moveable_);
}

void TurnManager::DetermineCharacterTurn()
{
	//End the previous characters turn.
	if (character_turn_) {
		EndTurn(character_turn_);
		character_turn_ = nullptr;
	}
	turn_num_++;
	switch (turn_) {
	case Turn::Player:
		/*If the player just finished their turn, check if there are any NPCs. If there
		is then set the first NPC to have their turn. If there is no NPCs but at least
		one enemy, set the first Enemy to have their turn.*/
		if (character_manager_->Npcs_.size() > 0) {
			turn_ = Turn::NPC;
			character_turn_ = character_manager_->Npcs_[0];
			turn_num_ = 0;
			break;
		}
		else if (character_manager_->Enemies_.size() > 0) {
			turn_ = Turn::Enemy;
			character_turn_ = character_manager_->Enemies_[0];
			turn_num_ = 0;
			break;
		}
		return;
	case Turn::NPC:
		/*If all of the NPCs have had their turn: 
		- if there are any enemies, set the first enemy to have their turn
		- otherwise have the player set to have their turn.
		else have the next npc have their turn.*/
		if (turn_num_ >= character_manager_->Npcs_.size()) {
			if (character_manager_->Enemies_.size() > 0) {
				turn_ = Turn::Enemy;
				character_turn_ = character_manager_->Enemies_[0];
				turn_num_ = 0;
			}
			else {
				turn_ = Turn::Player;
				character_turn_ = character_manager_->player_;
			}
		}
		else {
			character_turn_ = character_manager_->Npcs_[turn_num_];
		}
		break;
	case Turn::Enemy:
		/*If all of the enemies have had their turn then set the player to have their 
		turn, else set the next enemy to have their turn.*/
		if (turn_num_ >= character_manager_->Enemies_.size()) {
			turn_ = Turn::Player;
			character_turn_ = character_manager_->player_;
		}
		else {
			character_turn_ = character_manager_->Enemies_[turn_num_];
		}
	}
	//Start the determined characters turn.
	if (character_turn_) {
		StartTurn(character_turn_);
	}
}

void TurnManager::DEBUGSkipToStartOfPlayerTurn()
{
	EndTurn(character_turn_);
	StartTurn(character_turn_);
}
