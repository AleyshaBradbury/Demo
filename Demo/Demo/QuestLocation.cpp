#include "QuestLocation.h"

QuestLocation::QuestLocation(NPC* npc, Node* node, sf::Texture* texture, 
	QuestManager* quest_manager) :
	Location(node, texture)
{
	npc_ = npc;
	quest_manager_ = quest_manager;
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
		}
	}
}

void QuestLocation::Update(float dt)
{
	for (int i = 0; i < Quest_.size(); i++) {
		if (Quest_[i]->ButtonPressed()) {
			return;
		}
	}
}
