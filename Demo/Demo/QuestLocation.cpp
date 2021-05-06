#include "QuestLocation.h"
#include "Input.h"
#include "Player.h"

QuestLocation::QuestLocation(NPC* npc, Node* node, sf::Texture* texture, 
	QuestManager* quest_manager) :
	Location(node, texture)
{
	npc_ = npc;
	quest_manager_ = quest_manager;

	//Initialise text objects.
	no_quest_text_.setString("Sorry, I have\nno quests right\nnow.   D:");
	no_quest_text_.setCharacterSize(30);
	no_quest_text_.setFillColor(sf::Color::White);
	no_quest_text_.setPosition(left_size_start_, 5.0f);
	no_quest_text_.setFont(GeneralVariables::font_);

	npc_name_text_.setString(npc_->GetName());
	npc_name_text_.setCharacterSize(30);
	npc_name_text_.setFillColor(sf::Color::White);
	npc_name_text_.setPosition(160.0f, 10.0f);
	npc_name_text_.setFont(GeneralVariables::font_);

	npc_relationships_text_.setCharacterSize(30);
	npc_relationships_text_.setFillColor(sf::Color::White);
	npc_relationships_text_.setPosition(10.0f, 100.0f);
	npc_relationships_text_.setFont(GeneralVariables::font_);

	npc_needs_text_.setCharacterSize(30);
	npc_needs_text_.setFillColor(sf::Color::White);
	npc_needs_text_.setFont(GeneralVariables::font_);
}

QuestLocation::~QuestLocation()
{
	if (npc_) {
		npc_->GetGridNode()->SetLocation(nullptr);
	}
}

void QuestLocation::RenderLocation()
{
	for (int i = 0; i < Quest_.size(); i++) {
		Quest_[i]->Render();
		Quest_[i]->RenderExtra();
	}

	if (Quest_.size() <= 0) {
		GeneralVariables::window_.draw(no_quest_text_);
	}

	GeneralVariables::window_.draw(npc_name_text_);
	GeneralVariables::window_.draw(npc_relationships_text_);
	GeneralVariables::window_.draw(npc_needs_text_);
}

void QuestLocation::SetUpLocation()
{
	Quest_ = quest_manager_->GetNPCsQuests(npc_);
	float positionY = 5.0f;
	if (Quest_.size() > 0) {
		float sizeY = Quest_[0]->getSize().y;
		for (int i = 0; i < Quest_.size(); i++) {
			Quest_[i]->SetUpPositionOnScreen(sf::Vector2f(left_size_start_, positionY));
			Quest_[i]->SetButtonPosition(sf::Vector2f(left_size_start_, positionY));
			positionY += sizeY + 5.0f;
			sizeY = Quest_[i]->getSize().y;
		}
		positionY += 5.0f;
	}

	npc_relationships_text_.setString(GetRelationshipsText());
	npc_needs_text_.setString(GetNeedsText());
	npc_needs_text_.setPosition(10.0f, 100.0f +
		(npc_->GetRelationships().size() + 1) * 30 + 20.0f);
}

bool QuestLocation::Update(float dt, Player* player)
{
	for (int i = 0; i < Quest_.size(); i++) {
		if (Quest_[i]->ButtonPressed()) {
			Input::SetMouseLeftDown(false);
			//Add a memory of completing the quest to the player.
			std::vector<std::string> memory;
			memory.push_back("Quest");
			memory.push_back(npc_->GetName());
			std::vector<Quest::QuestDetails> details_ = Quest_[i]->GetRequirements();
			for (int i = 0; i < details_.size(); i++) {
				memory.push_back(details_[i].resource_);
			}
			player->AddMemory(memory);
			//Show reward screen.
			player->SetInfoWindow(true);

			//Remove the quest from pool of quests.
			npc_->AddCompletedQuest(Quest_[i]);
			quest_manager_->DeleteQuest(Quest_[i], npc_);
			SetUpLocation();
			return true;
		}
		else if (Quest_[i]->DeleteButtonPressed()) {
			quest_manager_->DeleteQuest(Quest_[i], npc_);
			npc_->ChangeRelationshipWithCharacter("Player", -1);
			SetUpLocation();
		}
	}
	return false;
}

std::string QuestLocation::GetRelationshipsText()
{
	//For every relationship the npc has, add that relationship and value to the string.
	std::string relationships = "Relationships:\n";
	std::unordered_map<std::string, unsigned int> Npc_Relationships = npc_->GetRelationships();
	for (auto& relationship : Npc_Relationships) {
		relationships += "	" + relationship.first + ": " +
			std::to_string(relationship.second) + "\n";
	}
	return relationships;
}

std::string QuestLocation::GetNeedsText()
{
	//For every need the npc has, add that need and value to the string.
	std::string needs = "Needs:\n";
	std::unordered_map<std::string, unsigned int> Npc_Needs = npc_->GetAllNeeds();
	for (auto& need : Npc_Needs) {
		needs += "	" + need.first + ": " +
			std::to_string(need.second) + "\n";
	}
	return needs;
}
