#include "Tank.h"
#include "GameObjectsParameters.h"
#include <string>
#include <iostream>
#include "Level.h"

void AddTank(uint8_t tier, const Vector2& position, TanksData& tanksData)
{
	// if no tanks in tanksData, then add player's tank sprite, else enemy's sprite
	std::string spritePath = (tanksData.tiers.size() == 0 ? GOLDEN : SILVER)
		+ std::to_string(tier) + "_" + std::to_string((uint8_t)(tanksData.tiers.size() == 0 ? Direction::UP : Direction::DOWN)) + "_0.png";

	Sprite* sprite = createSprite(spritePath.c_str());

	int w, h;
	getSpriteSize(sprite, w, h);

	tanksData.tiers.push_back(tier);
	tanksData.health.push_back(tanksData.health.size() == 0 ? 3 : HEALTH[tier]);
	tanksData.damages.push_back(1);
	tanksData.movementSpeeds.push_back(MOVEMENT_SPEED[tier]);
	tanksData.bulletSpeeds.push_back(BULLET_SPEED[tier]);
	tanksData.positions.push_back(position);
	tanksData.bounds.push_back(Bounds{ position, Vector2{position.x + w, position.y + h } });
	tanksData.sprites.push_back(sprite);
	tanksData.directions.push_back(tanksData.directions.size() == 0 ? (uint8_t)Direction::COUNT : (uint8_t)Direction::DOWN);
	tanksData.sights.push_back((uint8_t)Direction::UP);
	tanksData.shots.push_back(0);

	//destroySprite(sprite);
}

void UpdateSprites(TanksData& tanksData)
{
	std::string spritePath;

	for (size_t i{ 0 }; i < tanksData.tiers.size(); ++i)
	{
		if (tanksData.directions[i] < 4)
		{
			destroySprite(tanksData.sprites[i]);
			spritePath = (i == 0 ? GOLDEN : SILVER) + std::to_string(tanksData.tiers[i]) + "_" + std::to_string(tanksData.directions[i]) + "_0.png";
			tanksData.sprites[i] = createSprite(spritePath.c_str());
		}
	}
}

void MoveTanks(TanksData& tanksData, GameField& fieldData)
{	
	bool collidesTank = false;
	for (size_t i{ 0 }; i < tanksData.positions.size(); ++i)
	{
		// Check current (i) tank for collision with another tanks (j)

		if (tanksData.directions[i] != (uint8_t)Direction::COUNT)
		{
			tanksData.sights[i] = tanksData.directions[i];
		}

		for (size_t j{ 0 }; j < tanksData.bounds.size(); ++j)
		{
			if (i != j)
			{
				if (CheckPotentialCollision(tanksData.directions[i], (float)tanksData.movementSpeeds[i], tanksData.bounds[i], tanksData.bounds[j]))
				{
					collidesTank = true;
					break;
				}
			}			
		}

		if (!CheckPotentialCollision(tanksData.directions[i], (float)tanksData.movementSpeeds[i], tanksData.bounds[i], fieldData) && !collidesTank)
		{
			tanksData.positions[i] = GetPotentialBounds(tanksData.directions[i], (float)tanksData.movementSpeeds[i], tanksData.bounds[i]).topLeft;
			tanksData.bounds[i] = GetPotentialBounds(tanksData.directions[i], (float)tanksData.movementSpeeds[i], tanksData.bounds[i]);
		}
	}
}

void Fire(size_t indexOfTank, Bullets& bulletsData, TanksData& tanksData)
{
	if (tanksData.shots[indexOfTank] == 1)
	{
		return;
	}

	Vector2 position;
	switch (tanksData.sights[indexOfTank])
	{
	case 0:
		position = Vector2(tanksData.bounds[indexOfTank].bottomRight.x - BULLET_MAX_LENGHT,
			(tanksData.bounds[indexOfTank].bottomRight.y + tanksData.bounds[indexOfTank].topLeft.y) / 2 - BULLET_MAX_WIDTH / 2);
		break;
	case 1:
		position = Vector2(tanksData.bounds[indexOfTank].topLeft.x,
			(tanksData.bounds[indexOfTank].bottomRight.y + tanksData.bounds[indexOfTank].topLeft.y) / 2 - BULLET_MAX_WIDTH / 2);
		break;
	case 2:
		position = Vector2((tanksData.bounds[indexOfTank].topLeft.x + tanksData.bounds[indexOfTank].bottomRight.x) / 2 - BULLET_MAX_WIDTH / 2,
			tanksData.bounds[indexOfTank].bottomRight.y - BULLET_MAX_LENGHT);
		break;
	case 3:
		position = Vector2((tanksData.bounds[indexOfTank].topLeft.x + tanksData.bounds[indexOfTank].bottomRight.x) / 2 - BULLET_MAX_WIDTH / 2,
			tanksData.bounds[indexOfTank].topLeft.y);
		break;
	}
	AddBullet(indexOfTank, position, tanksData.sights[indexOfTank], tanksData.bulletSpeeds[indexOfTank], bulletsData);
	tanksData.shots[indexOfTank] = 1;
}

void DestroyTankAndBullets(size_t index, Bullets& bulletsData, TanksData& tanksData)
{
	std::cout << "Destroy tank" << std::endl;
	destroySprite(tanksData.sprites[index]);

	size_t bulletIndex;
	for (uint8_t i{ 0 }; i < tanksData.shots[index]; ++i)
	{
		if (GetBulletByOwner(bulletIndex, index, bulletsData))
		{
			DestroyBullet(bulletIndex, bulletsData, tanksData);
		}		
	}

	std::vector<Bounds>::iterator bndIter(tanksData.bounds.begin() + index);
	tanksData.bounds.erase(bndIter);
	std::vector<uint8_t>::iterator bsIter(tanksData.bulletSpeeds.begin() + index);
	tanksData.bulletSpeeds.erase(bsIter);
	std::vector<uint8_t>::iterator dmgIter(tanksData.damages.begin() + index);
	tanksData.damages.erase(dmgIter);
	std::vector<uint8_t>::iterator dirIter(tanksData.directions.begin() + index);
	tanksData.directions.erase(dirIter);
	std::vector<uint8_t>::iterator hlthIter(tanksData.health.begin() + index);
	tanksData.health.erase(hlthIter);
	std::vector<uint8_t>::iterator msIter(tanksData.movementSpeeds.begin() + index);
	tanksData.movementSpeeds.erase(msIter);
	std::vector<Vector2>::iterator posIter(tanksData.positions.begin() + index);
	tanksData.positions.erase(posIter);
	std::vector<uint8_t>::iterator shtIter(tanksData.shots.begin() + index);	
	tanksData.shots.erase(shtIter);
	std::vector<uint8_t>::iterator sghtIter(tanksData.sights.begin() + index);
	tanksData.sights.erase(sghtIter);
	std::vector<Sprite*>::iterator sprIter(tanksData.sprites.begin() + index);
	tanksData.sprites.erase(sprIter);
	std::vector<uint8_t>::iterator trIter(tanksData.tiers.begin() + index);
	tanksData.tiers.erase(trIter);	
}


void CheckHits(Bullets& bulletsData, TanksData& tanksData, GameField& fieldData)
{
	for (size_t j{ 0 }; j < bulletsData.bounds.size(); ++j)
	{
		for (size_t i{ 0 }; i < tanksData.bounds.size(); ++i)
		{
			if (CheckCollision(bulletsData.bounds[j], tanksData.bounds[i]))
			{
				if (!(bulletsData.owners[j] == 0 && i == 0))
				{
					if (!(bulletsData.owners[j] != 0 && i != 0))
					{
						DestroyBullet(j, bulletsData, tanksData);
						--tanksData.health[i];
						if (i == 0)
						{
							RespawnPlayersTank(tanksData, fieldData);
						}
						else
						{
							if (tanksData.health[i] == 0)
							{
								DestroyTankAndBullets(i, bulletsData, tanksData);
							}
						}
						//std::cout << "Owner: " << bulletsData.owners[j] << ", aim: " << i << std::endl;												
					}				
				}				
			}
		}
	}
}

void FireByEnemies(TanksData& tanksData, Bullets& bulletsData)
{
	for (size_t i{ 1 }; i < tanksData.bounds.size(); ++i)
	{
		Fire(i, bulletsData, tanksData);
	}
}

void ControlEnemies(TanksData& tanksData, GameField& fieldData)
{
	for (size_t i{ 1 }; i < tanksData.bounds.size(); ++i)
	{
		if (!CheckPotentialCollision((uint8_t)Direction::DOWN, (float)tanksData.movementSpeeds[i], tanksData.bounds[i], fieldData) &&
			!CheckExcludingPotentialCollision(i, (uint8_t)Direction::DOWN, (float)tanksData.movementSpeeds[i], tanksData.bounds[i], tanksData))
		{
			tanksData.directions[i] = (uint8_t)Direction::DOWN;
			tanksData.sights[i] = (uint8_t)Direction::DOWN;
		}
		else
		{
			if (tanksData.directions[i] == (uint8_t)Direction::DOWN)
			{
				tanksData.directions[i] = (uint8_t)Direction::RIGHT;
				tanksData.sights[i] = (uint8_t)Direction::RIGHT;
			}
			else
			{
				if (tanksData.directions[i] == (uint8_t)Direction::RIGHT)
				{
					if (!CheckPotentialCollision((uint8_t)Direction::RIGHT, (float)tanksData.movementSpeeds[i], tanksData.bounds[i], fieldData) &&
						!CheckExcludingPotentialCollision(i, (uint8_t)Direction::RIGHT, (float)tanksData.movementSpeeds[i], tanksData.bounds[i], tanksData))
					{
						continue;
					}
					else
					{
						tanksData.directions[i] = (uint8_t)Direction::LEFT;
						tanksData.sights[i] = (uint8_t)Direction::LEFT;
					}
				}
				else
				{
					if (!CheckPotentialCollision((uint8_t)Direction::LEFT, (float)tanksData.movementSpeeds[i], tanksData.bounds[i], fieldData) &&
						!CheckExcludingPotentialCollision(i, (uint8_t)Direction::LEFT, (float)tanksData.movementSpeeds[i], tanksData.bounds[i], tanksData))
					{
						continue;
					}
					else
					{
						tanksData.directions[i] = (uint8_t)Direction::RIGHT;
						tanksData.sights[i] = (uint8_t)Direction::RIGHT;
					}
				}
			}
		}
	}
}

void RespawnPlayersTank(TanksData& tanksData, GameField& fieldData)
{
	if (tanksData.health[0] == 0)
	{
		fieldData.baseDefeated = true;
		return;
	}

	Vector2 spawnPos;
	for (uint8_t i{ 1 }; i < LEVEL_X_SIZE-1; ++i)
	{
		if (level[LEVEL_Y_SIZE-3][i] == 8)
		{
			spawnPos = Vector2(i * TILE_SIZE + 1, (LEVEL_Y_SIZE - 3) * TILE_SIZE + 1);
			if (!CheckExcludingCollision(0, Bounds(spawnPos, Vector2(spawnPos.x + 40, spawnPos.y + 40)), tanksData))
			{
				std::cout << "Respawn" << std::endl;
				tanksData.bounds[0].topLeft = spawnPos;
				tanksData.bounds[0].bottomRight = Vector2(spawnPos.x + 40, spawnPos.y + 40);
				tanksData.positions[0] = spawnPos;
				tanksData.directions[0] = (uint8_t)Direction::COUNT;
				tanksData.sights[0] = (uint8_t)Direction::UP;
				return;
			}
		}
	}
	fieldData.baseDefeated = true;
}


void SpawnEnemy(int& enemiesCount, TanksData& tanksData)
{
	Vector2 spawnPos;
	for (uint8_t i{ 0 }; i < LEVEL_X_SIZE; ++i)
	{
		if (level[1][i] == 9)
		{
			spawnPos = Vector2(i * TILE_SIZE, TILE_SIZE);
			if (!CheckCollision(Bounds(spawnPos, Vector2(spawnPos.x + 40, spawnPos.y + 40)), tanksData))
			{
				std::cout << "Enemy spawned" << std::endl;
				AddTank(0, spawnPos, tanksData);
				++enemiesCount;
				return;
			}
		}
	}
}