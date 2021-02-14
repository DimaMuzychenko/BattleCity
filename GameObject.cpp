#define _USE_MATH_DEFINES
#include "GameObject.h"
#include <cmath>
#include <iostream>


Direction RelationalPosition(size_t first, size_t second, const GameObject& firstData, const GameObject& secondData)
{
	if (firstData.bounds[first].topLeft.y <= secondData.bounds[second].bottomRight.y && firstData.bounds[first].topLeft.y > secondData.bounds[second].bottomRight.y - 0.5f)
	{
		return Direction::UP;
	}
	else if (firstData.bounds[first].topLeft.x <= secondData.bounds[second].bottomRight.x && firstData.bounds[first].topLeft.x > secondData.bounds[second].bottomRight.x - 0.5f)
	{
		return Direction::LEFT;
	}
	else if (firstData.bounds[first].bottomRight.y >= secondData.bounds[second].topLeft.y && firstData.bounds[first].bottomRight.y < secondData.bounds[second].topLeft.y + 0.5f)
	{
		return Direction::DOWN;
	}
	else if (firstData.bounds[first].bottomRight.x >= secondData.bounds[second].topLeft.x && firstData.bounds[first].bottomRight.x < secondData.bounds[second].topLeft.x + 0.5f)
	{
		return Direction::RIGHT;
	}
	return Direction::COUNT;
}

Direction RelationalPosition(const Bounds& first, const Bounds& second)
{
	if (first.topLeft.y <= second.bottomRight.y && first.topLeft.y > second.bottomRight.y - 0.5f)
	{
		return Direction::UP;
	}
	else if (first.topLeft.x <= second.bottomRight.x && first.topLeft.x > second.bottomRight.x - 0.5f)
	{
		return Direction::LEFT;
	}
	else if (first.bottomRight.y >= second.topLeft.y && first.bottomRight.y < second.topLeft.y + 0.5f)
	{
		return Direction::DOWN;
	}
	else if (first.bottomRight.x >= second.topLeft.x && first.bottomRight.x < second.topLeft.x + 0.5f)
	{
		return Direction::RIGHT;
	}
	return Direction::COUNT;
}


bool CheckCollision(size_t index, const GameObject& obiectsData, const GameObject& obstaclesData)
{
	for (size_t i{ 0 }; i < obstaclesData.bounds.size(); ++i)
	{
		if (obiectsData.bounds[index].topLeft.y <= obstaclesData.bounds[i].bottomRight.y)
		{
			if (obiectsData.bounds[index].bottomRight.y >= obstaclesData.bounds[i].topLeft.y)
			{
				if (obiectsData.bounds[index].topLeft.x <= obstaclesData.bounds[i].bottomRight.x)
				{
					if (obiectsData.bounds[index].bottomRight.x >= obstaclesData.bounds[i].topLeft.x)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool CheckCollision(const Bounds& object, const GameObject& obstaclesData)
{
	for (size_t i{ 0 }; i < obstaclesData.bounds.size(); ++i)
	{
		if (object.topLeft.y <= obstaclesData.bounds[i].bottomRight.y)
		{
			if (object.bottomRight.y >= obstaclesData.bounds[i].topLeft.y)
			{
				if (object.topLeft.x <= obstaclesData.bounds[i].bottomRight.x)
				{
					if (object.bottomRight.x >= obstaclesData.bounds[i].topLeft.x)
					{
						/*std::cout << "Collision detected!" << std::endl;
						std::cout << "Tank's bounds: (" << object.topLeft.x << ", " << object.topLeft.y << ") (" << object.bottomRight.x << ", " << object.bottomRight.y << ")" << std::endl;
						std::cout << "Obstacle's bounds: (" << obstaclesData.bounds[i].topLeft.x << ", " << obstaclesData.bounds[i].topLeft.y << ") (" << obstaclesData.bounds[i].bottomRight.x << ", " << obstaclesData.bounds[i].bottomRight.y << ")" << std::endl;*/
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool CheckCollision(const Bounds& object, const Bounds& obstacle)
{
	if (object.topLeft.y <= obstacle.bottomRight.y)
	{
		if (object.bottomRight.y >= obstacle.topLeft.y)
		{
			if (object.topLeft.x <= obstacle.bottomRight.x)
			{
				if (object.bottomRight.x >= obstacle.topLeft.x)
				{
					std::cout << "Collision detected!" << std::endl;
					std::cout << "Tank's bounds: (" << object.topLeft.x << ", " << object.topLeft.y << ") (" << object.bottomRight.x << ", " << object.bottomRight.y << ")" << std::endl;
					std::cout << "Obstacle's bounds: (" << obstacle.topLeft.x << ", " << obstacle.topLeft.y << ") (" << obstacle.bottomRight.x << ", " << obstacle.bottomRight.y << ")" << std::endl;
					return true;
				}
			}
		}
	}
	return false;
}

