#pragma once
#include "Character.h"
#include "NPC.h"
#include "Grid.h"

class Enemy : public Character
{
public:
	Enemy(float health);
	void SetTarget(GameObject* target);
	GameObject* GetTarget();
	void HandleTarget();

private:
	GameObject* target_ = nullptr;
};

