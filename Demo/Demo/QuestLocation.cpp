#include "QuestLocation.h"
#include "Input.h"
#include "Player.h"

QuestLocation::QuestLocation(NPC* npc, Node* node, sf::Texture* texture, 
	QuestManager* quest_manager) :
	Location(node, texture)
{
	npc_ = npc;
	quest_manager_ = quest_manager;
	no_quest_text_.setString("Sorry, there are\nno quests right\nnow.   D:");
	no_quest_text_.setCharacterSize(30);
	no_quest_text_.setFillColor(sf::Color::White);
	no_quest_text_.setPosition(500.0f, 5.0f);
	no_quest_text_.setFont(GeneralVariables::font_);
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
}

void QuestLocation::SetUpLocation()
{
	Quest_ = quest_manager_->GetNPCsQuests(npc_);
	if (Quest_.size() > 0) {
		float sizeY = Quest_[0]->getSize().y;
		float positionY = 5.0f;
		for (int i = 0; i < Quest_.size(); i++) {
			Quest_[i]->SetUpPositionOnScreen(sf::Vector2f(500.0f, positionY));
			positionY += sizeY + 5.0f;
			sizeY = Quest_[i]->getSize().y;
		}
	}
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

			quest_manager_->DeleteQuest(Quest_[i], npc_);
			npc_->AddCompletedQuest(Quest_[i]);
			SetUpLocation();
			return true;
		}
	}
	return false;
}
