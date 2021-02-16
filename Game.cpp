#include "Framework.h"
#include <iostream>
#include "GameObject.h"
#include "Tank.h"
#include "GameField.h"
#include "Level.h"
#include "Bullet.h"
#include <chrono>
#include <thread>
#include <random>
#include "Bonus.h"

void DrawGameObjects(const GameObject& goData);
void DrawTanks(const TanksData& tanksData);
void DrawField(const GameField& wallsData);


class Game : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 624;
		height = 600;
		fullscreen = false;
	}

	virtual bool Init() {
		LoadLevel(fieldData);
		backGround = createSprite("Resources\\BG.png");
		Vector2 pos(0, 0);
		AddTank(0, pos, tanksData);
		RespawnPlayersTank(tanksData, fieldData);
		srand(time(0));
		enemiesCount = 0;
		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() 
	{
		drawSprite(backGround, 0, 0);
		DrawGameObjects(fieldData);
		DrawGameObjects(fieldData);
		DrawGameObjects(tanksData);
		DrawGameObjects(bulletsData);
		DrawGameObjects(bonusesData);
		if (!fieldData.baseDefeated)
		{			
			CheckHits(bulletsData, tanksData, fieldData);
			UpdateSprites(tanksData);			
			UpdateWallsState(fieldData, bulletsData, tanksData);
			TakeBonus(0, tanksData, bonusesData);
			if (std::chrono::steady_clock::now() - lastObjectsMoveTime > std::chrono::milliseconds(10))
			{
				MoveTanks(tanksData, fieldData);
				MoveBullets(bulletsData);
				lastObjectsMoveTime = std::chrono::steady_clock::now();
			}
			if (std::chrono::steady_clock::now() - lastControlTime > std::chrono::milliseconds(500))
			{
				ControlEnemies(tanksData, fieldData);
				lastControlTime = std::chrono::steady_clock::now();
			}			
			if (std::chrono::steady_clock::now() - lastShotTime > std::chrono::milliseconds(2000))
			{
				FireByEnemies(tanksData, bulletsData);
				lastShotTime = std::chrono::steady_clock::now();
			}			
			if (tanksData.bounds.size() < 3 && enemiesCount <= 20)
			{
				SpawnEnemy(enemiesCount, tanksData);
			}
			if ((enemiesCount == 6 && bonusCount == 0)||(enemiesCount == 13 && bonusCount == 1)||(enemiesCount == 20 && bonusCount == 2))
			{				
				SpawnBonus(Bonus::HEALTH, bonusesData);
				bonusCount++;
			}
			if ((enemiesCount == 12 && bonusCount == 1) || (enemiesCount == 19 && bonusCount == 2))
			{
				for (size_t i{ 0 }; i < bonusesData.types.size(); ++i)
				{
					if (bonusesData.types[i] == Bonus::HEALTH)
					{
						DestroyBonus(i, bonusesData);
					}
				}
			}
		}
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) 
	{
		if (!fieldData.baseDefeated)
		{
			if (!isReleased)
			{
				if (button == FRMouseButton::LEFT)
				{
					Fire(0, bulletsData, tanksData);
				}
			}
		}
	}

	virtual void onKeyPressed(FRKey k) 
	{
		if ((uint8_t)k == (uint8_t)tanksData.directions[0] || fieldData.baseDefeated)
		{
			return;
		}

		switch (k)
		{
		case FRKey::RIGHT:
			std::cout << "RIGHT" << std::endl;
			tanksData.directions[0] = (uint8_t)Direction::RIGHT;
			break;
		case FRKey::LEFT:
			std::cout << "LEFT" << std::endl;
			tanksData.directions[0] = (uint8_t)Direction::LEFT;
			break;
		case FRKey::DOWN:
			std::cout << "DOWN" << std::endl;
			tanksData.directions[0] = (uint8_t)Direction::DOWN;
			break;
		case FRKey::UP:
			std::cout << "UP" << std::endl;
			tanksData.directions[0] = (uint8_t)Direction::UP;
			break;
		}
	}

	virtual void onKeyReleased(FRKey k) 
	{
		if ((uint8_t)k == (uint8_t)tanksData.directions[0])
		{
			std::cout << "STOP" << std::endl;
			tanksData.directions[0] = (uint8_t)Direction::COUNT;
		}
	}

	virtual const char* GetTitle() override
	{
		return "Tanks";
	}

	TanksData tanksData;
	GameField fieldData;
	Bullets bulletsData;
	Bonuses bonusesData;
	Sprite* backGround;
	int enemiesCount{ 0 };
	int bonusCount{ 0 };
	std::chrono::time_point<std::chrono::steady_clock> lastShotTime;
	std::chrono::time_point<std::chrono::steady_clock> lastControlTime;
	std::chrono::time_point<std::chrono::steady_clock> lastObjectsMoveTime;
};

int main(int argc, char* argv[])
{
	return run(new Game);
}

void DrawGameObjects(const GameObject& goData)
{
	for (size_t i{ 0 }; i < goData.sprites.size(); ++i)
	{
		drawSprite(goData.sprites[i], (int)goData.positions[i].x, (int)goData.positions[i].y);
	}
}

void DrawTanks(const TanksData& tanksData)
{
	for (size_t i{ 0 }; i < tanksData.sprites.size(); ++i)
	{
		drawSprite(tanksData.sprites[i], (int)tanksData.positions[i].x, (int)tanksData.positions[i].y);
	}
}

void DrawField(const GameField& wallsData)
{
	for (size_t i{ 0 }; i < wallsData.sprites.size(); ++i)
	{
		drawSprite(wallsData.sprites[i], (int)wallsData.positions[i].x, (int)wallsData.positions[i].y);
	}
}