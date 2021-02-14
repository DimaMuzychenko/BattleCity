#pragma once
#include <vector>
#include "GameObject.h"


enum class Tile
{
	BRICK = 1
};


struct GameField : GameObject
{
	std::vector<uint8_t> types;
	bool baseDefeated = false;
};

#include "Bullet.h"
#include "Tank.h"

void AddTile(uint8_t type, const Vector2& position, GameField& fieldData);
void LoadLevel(GameField& fieldData);
void DestroyTile(size_t index, GameField& fieldData);
void HarmBrickTile(size_t index, Direction harmedSide, GameField& fieldData);
void UpdateWallsState(GameField& fieldData, Bullets& bulletsData, TanksData& tanksData);
void ChangeBaseSprite(GameField& fieldData);