#include "Bonus.h"
#include "Level.h"
#include <random>
#include <iostream>

const char* HEALTH_BONUS_SPRITE = "Resources\\HealthBonus.png";

Bounds GetNewBonusBounds()
{	
	uint8_t slot = rand() % 16;
	for (uint8_t i{ 0 }; i < LEVEL_Y_SIZE; ++i)
	{
		for (uint8_t j{ 0 }; j < LEVEL_X_SIZE; ++j)
		{
			if (level[i][j] == 7 && slot-- == 0)
			{
				return Bounds(Vector2(j * TILE_SIZE, i * TILE_SIZE), Vector2(j * TILE_SIZE + BONUS_SPRITE_SIZE, i * TILE_SIZE + BONUS_SPRITE_SIZE));
			}
		}		
	}
}

void SpawnBonus(Bonus type, Bonuses& bonusesData)
{
	if (type == Bonus::HEALTH)
	{
		bonusesData.sprites.push_back(createSprite(HEALTH_BONUS_SPRITE));
	}
	else
	{
		return;
	}
	Bounds newBounds = GetNewBonusBounds();
	bonusesData.positions.push_back(newBounds.topLeft);
	bonusesData.bounds.push_back(newBounds);
	bonusesData.types.push_back(type);
}

void DestroyBonus(size_t index, Bonuses& bonusesData)
{
	std::vector<Vector2>::iterator posIter(bonusesData.positions.begin() + index);
	bonusesData.positions.erase(posIter);
	std::vector<Bounds>::iterator bndIter(bonusesData.bounds.begin() + index);
	bonusesData.bounds.erase(bndIter);
	std::vector<Bonus>::iterator tpIter(bonusesData.types.begin() + index);
	bonusesData.types.erase(tpIter);
	destroySprite(bonusesData.sprites[index]);
	std::vector<Sprite*>::iterator sprIter(bonusesData.sprites.begin() + index);
	bonusesData.sprites.erase(sprIter);
}


void TakeBonus(size_t index, TanksData& tanksData, Bonuses& bonusesData)
{
	size_t bonusIndex = GetObstacle(tanksData.bounds[index], bonusesData);
	if (bonusIndex != -1)
	{
		if (bonusesData.types[bonusIndex] == Bonus::HEALTH)
		{
			std::cout << "Health increased" << std::endl;
			tanksData.health[index]++;
			DestroyBonus(bonusIndex, bonusesData);
		}
	}
}