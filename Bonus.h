#pragma once
#include "GameObject.h"
#include <vector>

const uint8_t BONUS_SPRITE_SIZE = 40;


enum class Bonus
{
	HEALTH
};


struct Bonuses : GameObject
{
	std::vector<Bonus> types;
};


#include "GameField.h"

Bounds GetNewBonusBounds();
void SpawnBonus(Bonus type, Bonuses& bonusesData);
void DestroyBonus(size_t index, Bonuses& bonusesData);
void TakeBonus(size_t index, TanksData& tanksData, Bonuses& bonusesData);