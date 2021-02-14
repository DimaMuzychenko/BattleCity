#include "Framework.h"
#include <iostream>
#include "GameObject.h"
#include "Tank.h"
#include "GameField.h"
#include "Level.h"
#include "Bullet.h"

void DrawGameObjects(const GameObject& goData);
void DrawTanks(const TanksData& tanksData);
void DrawField(const GameField& wallsData);
void SpawnEnemy(int& enemiesCount, TanksData& tanksData);


class Game : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 600;
		height = 600;
		fullscreen = false;
	}

	virtual bool Init() {
		LoadLevel(fieldData);
		backGround = createSprite("Resources\\BG.png");
		Vector2 pos(400, 300);
		AddTank(0, pos, tanksData);
		SpawnEnemy(enemiesCount, tanksData);
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
		if (!fieldData.baseDefeated)
		{
			if (enemiesCount - tanksData.bounds.size() - 1 < 4 && enemiesCount <= 20)
			{
				SpawnEnemy(enemiesCount, tanksData);
			}
			CheckHits(bulletsData, tanksData);
			UpdateSprites(tanksData);
			MoveTanks(tanksData, fieldData);
			MoveBullets(bulletsData);
			UpdateWallsState(fieldData, bulletsData, tanksData);
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
	Sprite* backGround;
	int enemiesCount{ 0 };
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
				AddTank(0, spawnPos, tanksData);
				enemiesCount++;
			}
		}
	}	
}