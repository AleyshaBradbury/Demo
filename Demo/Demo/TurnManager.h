#pragma once

class CharacterManager;
class Character;
class QuestManager;

class TurnManager
{
public:
	enum class Turn {
		Player,
		NPC,
		Enemy,
		Count
	};

public:
	static void StartTurn(Character* character);
	static void EndTurn(Character* character);
	static void DetermineCharacterTurn();
	static void DEBUGSkipToStartOfPlayerTurn();

	//Which factions turn is the game on?
	static Turn turn_;
	//The enemy or npc integer.
	static int character_turn_num_;
	static bool was_moveable_;

	static int turn_num_;

	static Character* character_turn_;
	static CharacterManager* character_manager_;
};

