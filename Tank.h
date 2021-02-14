#pragma once
#include <vector>
#include "GameObject.h"
#include "Framework.h"
#include "BasicStructures.h"



struct TanksData : GameObject
{
	std::vector<uint8_t> tiers;
	std::vector<uint8_t> health;
	std::vector<uint8_t> damages;
	std::vector<uint8_t> movementSpeeds;
	std::vector<uint8_t> bulletSpeeds;
	std::vector<uint8_t> directions;
	std::vector<uint8_t> sights;
	std::vector<uint8_t> shots;
};

#include "GameField.h"
#include "Bullet.h"

void AddTank(uint8_t tier, const Vector2& position, TanksData& tanksData);
void MoveTanks(TanksData& tanksData, GameField& fieldData);
void UpdateSprites(TanksData& tanksData);
void Fire(size_t indexOfTank, Bullets& bulletsData, TanksData& tanksData);
void CheckHits(Bullets& bulletsData, TanksData& tanksData);
void DestroyTankAndBullets(size_t index, Bullets& bulletsData, TanksData& tanksData);

