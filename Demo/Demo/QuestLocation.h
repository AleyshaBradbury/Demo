#pragma once
#include "Location.h"
#include "Quest.h"
#include "NPC.h"
#include "QuestManager.h"

class QuestLocation : public Location
{
public:
	QuestLocation(NPC* npc, Node* node, sf::Texture* texture, QuestManager* quest_manager);
	~QuestLocation();
	void RenderLocation();

	void SetUpLocation();
	bool Update(float dt, Player* player);

private:
	QuestManager* quest_manager_;

	std::vector<Quest*> Quest_;
	NPC* npc_;
	sf::Text no_quest_text_;
};

