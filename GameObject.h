#pragma once
#include <vector>
#include "BasicStructures.h"
#include "Framework.h"

enum class Direction
{
	RIGHT,
	LEFT,
	DOWN,
	UP,
	COUNT
};

struct GameObject
{
	std::vector<Vector2> positions;
	std::vector<Bounds> bounds;
	std::vector<Sprite*> sprites;
};

Direction RelationalPosition(size_t first, size_t second, const GameObject& firstData, const GameObject& secondData);

Direction RelationalPosition(const Bounds& first, const Bounds& second);

/// <summary>
/// Check for collision of game objects.
/// </summary>
/// <param name="index">Index of object to check collition.</param>
/// <param name="objectsData">Data of objects that need be checked.</param>
/// <param name="obstaclesData">Data of objects that can be obstacles.</param>
bool CheckCollision(size_t index, const GameObject& objectsData, const GameObject& obstaclesData);

/// <summary>
/// Check for collision of game objects.
/// </summary>
/// <param name="object">Bounds of object to be checked for collision.</param>
/// <param name="obstaclesData">Data of objects that can be obstacles.</param>
bool CheckCollision(const Bounds& object, const GameObject& obstaclesData);


bool CheckExcludingCollision(size_t index, const Bounds& object, const GameObject& obstaclesData);

/// <summary>
/// Check for collision of game objects.
/// </summary>
/// <param name="object">Bounds of object to be checked for collision.</param>
/// <param name="obstacle">Bounds of objects that can be obstacles.</param>
bool CheckCollision(const Bounds& object, const Bounds& obstacle);

/// <summary>
/// Check for collision of game objects in specified direction with specified step. Returns whether collision will occure. In case of collision will not occure object's bounds will changed into potential bounds.
/// </summary>
/// <param name="direction">Direction of object movement.</param>
/// <param name="step">Speed of object movement per iteration.</param>
/// <param name="object">Bounds of object to be checked for collision.</param>
/// <param name="obstacle">Bounds of objects that can be obstacles.</param>
bool CheckPotentialCollision(uint8_t direction, float step, Bounds& object, const GameObject& obstacles);


bool CheckExcludingPotentialCollision(size_t index, uint8_t direction, float step, const Bounds& object, const GameObject& obstacles);


bool CheckPotentialCollision(uint8_t direction, float step, const Bounds& object, const Bounds& obstacle);

size_t GetObstacle(const Bounds& object, const GameObject& obstaclesData);

Bounds GetPotentialBounds(uint8_t direction, float step, const Bounds& object);