#pragma once
#include "GameObject.h"
#include <vector>


const uint8_t BULLET_MAX_LENGHT = 12;
const uint8_t BULLET_MAX_WIDTH = 9;

struct Bullets : GameObject
{
	std::vector<uint8_t> directions;
	std::vector<size_t> owners;
};

#include "Tank.h"

void AddBullet(size_t owner, const Vector2& position, uint8_t direction, Bullets& bulletsData);
void MoveBullets(Bullets& bulletsData);
void DestroyBullet(size_t index, Bullets& bulletsData);