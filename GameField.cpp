#include "GameField.h"
#include "Level.h"
#include <iostream>
#include <string>


void AddTile(uint8_t type, const Vector2& position, GameField& fieldData)
{
	Sprite* sprite = createSprite("Resources\\Tiles\\1.png");
	if (type == 0)
	{
		return;
	}
	if (type == 1)
	{
		sprite = createSprite("Resources\\Tiles\\1.png");
	}
	if (type == 5)
	{
		sprite = createSprite("Resources\\Tiles\\5.png");
	}
	if (type == 9)
	{
		return;
	}
	if (type == 10)
	{
		sprite = createSprite("Resources\\Tiles\\Base.png");
		fieldData.bounds.push_back(Bounds(position, Vector2(position.x + TILE_SIZE * 2, position.y + TILE_SIZE * 2)));
	}
	if (type != 10)
	{
		fieldData.bounds.push_back(Bounds(position, Vector2(position.x + TILE_SIZE, position.y + TILE_SIZE)));
	}
	fieldData.types.push_back(type);
	fieldData.sprites.push_back(sprite);
	fieldData.positions.push_back(position);	
}

void LoadLevel(GameField& fieldData)
{
	int w, h;
	getScreenSize(w, h);
	Vector2 position;

	for (uint8_t i{ 0 }; i < LEVEL_Y_SIZE; ++i)
	{
		for (uint8_t j{ 0 }; j < LEVEL_X_SIZE; ++j)
		{
			position = Vector2((float)w / LEVEL_X_SIZE * j, (float)h / LEVEL_Y_SIZE * i);
			AddTile(level[i][j], position, fieldData);
		}
	}
}

void DestroyTile(size_t index, GameField& fieldData)
{
	std::vector<uint8_t>::iterator typeIter(fieldData.types.begin() + index);
	fieldData.types.erase(typeIter);
	std::vector<Vector2>::iterator posIter(fieldData.positions.begin() + index);
	fieldData.positions.erase(posIter);
	std::vector<Bounds>::iterator bndIter(fieldData.bounds.begin() + index);
	fieldData.bounds.erase(bndIter);
	std::vector<Sprite*>::iterator sprIter(fieldData.sprites.begin() + index);
	fieldData.sprites.erase(sprIter);
}

void HarmBrickTile(size_t index, Direction harmedSide, GameField& fieldData)
{
	std::string spritePath = "Resources\\Tiles\\1_" + std::to_string((uint8_t)harmedSide) + ".png";
	Sprite* sprite = createSprite(spritePath.c_str());
	fieldData.types.push_back(2);
	fieldData.sprites.push_back(sprite);
	Bounds newBounds = fieldData.bounds[index];
	switch (harmedSide)
	{
	case Direction::UP:
		newBounds.topLeft.y += TILE_SIZE / 2;
		break;
	case Direction::RIGHT:
		newBounds.bottomRight.x -= TILE_SIZE / 2;
		break;
	case Direction::DOWN:
		newBounds.bottomRight.y -= TILE_SIZE / 2;
		break;
	case Direction::LEFT:
		newBounds.topLeft.x += TILE_SIZE / 2;
		break;
	}
	fieldData.positions.push_back(newBounds.topLeft);
	fieldData.bounds.push_back(newBounds);
	DestroyTile(index, fieldData);
}

void UpdateWallsState(GameField& fieldData, Bullets& bulletsData, TanksData& tanksData)
{
	bool collisionOccured = false;

	for (size_t j{ 0 }; j < bulletsData.bounds.size(); ++j)
	{
		for (size_t i{ 0 }; i < fieldData.bounds.size(); ++i)
		{
			if (CheckCollision(bulletsData.bounds[j], fieldData.bounds[i]))
			{				
				std::cout << "Bullet collision occured" << std::endl;
				collisionOccured = true;
				if (fieldData.types[i] == 1)
				{
					HarmBrickTile(i, RelationalPosition(fieldData.bounds[i], bulletsData.bounds[j]), fieldData);
					i = 0;
				}
				if (fieldData.types[i] == 2)
				{
					DestroyTile(i, fieldData);
					i = 0;
				}
				if (fieldData.types[i] == 10)
				{
					fieldData.baseDefeated = true;
					ChangeBaseSprite(fieldData);
				}
			}			
		}
		if (collisionOccured)
		{
			DestroyBullet(j, bulletsData, tanksData);
		}
	}
}

void ChangeBaseSprite(GameField& fieldData)
{
	for (size_t i{ 0 }; i < fieldData.bounds.size(); ++i)
	{
		if (fieldData.types[i] == 10)
		{
			fieldData.sprites[i] = createSprite("Resources\\Tiles\\DefeatedBase.png");
		}
	}
}