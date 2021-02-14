#include "Bullet.h"
#include <string>
#include <iostream>

void AddBullet(size_t owner, const Vector2& position, uint8_t direction, Bullets& bulletsData)
{
	std::cout << "Bullet's position: (" << position.x << ", " << position.y << ")" << std::endl;
	std::string spritePath = "Resources\\Bullet\\" + std::to_string(direction) + ".png";
	Sprite* sprite = createSprite(spritePath.c_str());
	int h, w;
	getSpriteSize(sprite, w, h);
	bulletsData.bounds.push_back(Bounds(position, Vector2(position.x + w, position.y + h)));
	bulletsData.positions.push_back(position);
	bulletsData.sprites.push_back(createSprite(spritePath.c_str()));
	bulletsData.directions.push_back(direction);
	bulletsData.owners.push_back(owner);
	//destroySprite(sprite);
}

void MoveBullets(Bullets& bulletsData)
{	
	for (size_t i{ 0 }; i < bulletsData.directions.size(); ++i)
	{		
		if (bulletsData.directions[i] == (uint8_t)Direction::UP)
		{
			//std::cout << "MoveBullets(UP)" << std::endl;
			bulletsData.positions[i].y -= 1.f;
			bulletsData.bounds[i].topLeft.y -= 1.f;
			bulletsData.bounds[i].bottomRight.y -= 1.f;
		}
		if (bulletsData.directions[i] == (uint8_t)Direction::RIGHT)
		{
			//std::cout << "MoveBullets(RIGHT)" << std::endl;
			bulletsData.positions[i].x += 1.f;
			bulletsData.bounds[i].topLeft.x += 1.f;
			bulletsData.bounds[i].bottomRight.x += 1.f;
		}
		if (bulletsData.directions[i] == (uint8_t)Direction::DOWN)
		{
			//std::cout << "MoveBullets(DOWN)" << std::endl;
			bulletsData.positions[i].y += 1.f;
			bulletsData.bounds[i].topLeft.y += 1.f;
			bulletsData.bounds[i].bottomRight.y += 1.f;
		}
		if (bulletsData.directions[i] == (uint8_t)Direction::LEFT)
		{
			//std::cout << "MoveBullets(LEFT)" << std::endl;
			bulletsData.positions[i].x -= 1.f;
			bulletsData.bounds[i].topLeft.x -= 1.f;
			bulletsData.bounds[i].bottomRight.x -= 1.f;
		}
	}
}

void DestroyBullet(size_t index, Bullets& bulletsData, TanksData& tanksData)
{
	destroySprite(bulletsData.sprites[index]);

	tanksData.shots[bulletsData.owners[index]]--;

	std::vector<uint8_t>::iterator dirIter(bulletsData.directions.begin() + index);
	bulletsData.directions.erase(dirIter);
	std::vector<Vector2>::iterator posIter(bulletsData.positions.begin() + index);
	bulletsData.positions.erase(posIter);
	std::vector<Bounds>::iterator bndIter(bulletsData.bounds.begin() + index);
	bulletsData.bounds.erase(bndIter);	
	std::vector<Sprite*>::iterator sprIter(bulletsData.sprites.begin() + index);
	bulletsData.sprites.erase(sprIter);
}

bool GetBulletByOwner(size_t& bulletIndex, size_t owner, Bullets& bulletsData)
{
	for (size_t i{ 0 }; i < bulletsData.owners.size(); ++i)
	{
		if (bulletsData.owners[i] == owner)
		{
			bulletIndex = i;
			return true;
		}
	}
	return false;
}