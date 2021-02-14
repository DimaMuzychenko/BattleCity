#include "Tank.h"
#include "GameObjectsParameters.h"
#include <string>
#include <iostream>

void AddTank(uint8_t tier, const Vector2& position, TanksData& tanksData)
{
	// if no tanks in tanksData, then add player's tank sprite, else enemy's sprite
	std::string spritePath = (tanksData.tiers.size() == 0 ? GOLDEN : SILVER)
		+ std::to_string(tier) + "_" + std::to_string((uint8_t)Direction::UP) + "_0.png";

	Sprite* sprite = createSprite(spritePath.c_str());

	int w, h;
	getSpriteSize(sprite, w, h);

	tanksData.tiers.push_back(tier);
	tanksData.health.push_back(HEALTH[tier]);
	tanksData.damages.push_back(1);
	tanksData.movementSpeeds.push_back(MOVEMENT_SPEED[tier]);
	tanksData.bulletSpeeds.push_back(BULLET_SPEED[tier]);
	tanksData.positions.push_back(position);
	tanksData.bounds.push_back(Bounds{ position, Vector2{position.x + w, position.y + h } });
	tanksData.sprites.push_back(sprite);
	tanksData.directions.push_back((uint8_t)Direction::COUNT);
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
			spritePath = (i == 0 ? GOLDEN : SILVER) + std::to_string(tanksData.tiers[i]) + "_" + std::to_string(tanksData.directions[i]) + "_0.png";
			tanksData.sprites[i] = createSprite(spritePath.c_str());
		}
	}
}

void MoveTanks(TanksData& tanksData, GameField& fieldData)
{
	Bounds temp; // Precalculated bounds to be checked for collision

	for (size_t i{ 0 }; i < tanksData.positions.size(); ++i)
	{
		if (tanksData.directions[i] == (uint8_t)Direction::COUNT)
		{
			continue;
		}

		tanksData.sights[i] = tanksData.directions[i];

		temp = tanksData.bounds[i];

		if (tanksData.directions[i] == (uint8_t)Direction::UP)
		{
			temp.topLeft.y = tanksData.bounds[i].topLeft.y - 1.f;
			temp.bottomRight.y = tanksData.bounds[i].bottomRight.y - 1.f;
		}
		if (tanksData.directions[i] == (uint8_t)Direction::RIGHT)
		{
			temp.topLeft.x = tanksData.bounds[i].topLeft.x + 1.f;
			temp.bottomRight.x = tanksData.bounds[i].bottomRight.x + 1.f;
		}
		if (tanksData.directions[i] == (uint8_t)Direction::DOWN)
		{
			temp.topLeft.y = tanksData.bounds[i].topLeft.y + 1.f;
			temp.bottomRight.y = tanksData.bounds[i].bottomRight.y + 1.f;
		}
		if (tanksData.directions[i] == (uint8_t)Direction::LEFT)
		{
			temp.topLeft.x = tanksData.bounds[i].topLeft.x - 1.f;
			temp.bottomRight.x = tanksData.bounds[i].bottomRight.x - 1.f;
		}

		if (!CheckCollision(temp, fieldData))
		{
			tanksData.positions[i] = temp.topLeft;
			tanksData.bounds[i] = temp;
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
		position = Vector2(tanksData.bounds[indexOfTank].bottomRight.x,
			(tanksData.bounds[indexOfTank].bottomRight.y + tanksData.bounds[indexOfTank].topLeft.y) / 2 - BULLET_MAX_WIDTH / 2);
		break;
	case 1:
		position = Vector2(tanksData.bounds[indexOfTank].topLeft.x - BULLET_MAX_LENGHT,
			(tanksData.bounds[indexOfTank].bottomRight.y + tanksData.bounds[indexOfTank].topLeft.y) / 2 - BULLET_MAX_WIDTH / 2);
		break;
	case 2:
		position = Vector2((tanksData.bounds[indexOfTank].topLeft.x + tanksData.bounds[indexOfTank].bottomRight.x) / 2 - BULLET_MAX_WIDTH / 2,
			tanksData.bounds[indexOfTank].bottomRight.y);
		break;
	case 3:
		position = Vector2((tanksData.bounds[indexOfTank].topLeft.x + tanksData.bounds[indexOfTank].bottomRight.x) / 2 - BULLET_MAX_WIDTH / 2,
			tanksData.bounds[indexOfTank].topLeft.y - BULLET_MAX_LENGHT);
		break;
	}
	AddBullet(indexOfTank, position, tanksData.sights[indexOfTank], bulletsData);
	tanksData.shots[indexOfTank] = 1;
}