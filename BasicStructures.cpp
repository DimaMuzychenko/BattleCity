#include "BasicStructures.h"

//namespace st
//{

	/*Vector2::Vector2()
	{
		this->x = 0;
		this->y = 0;
	}*/

	Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2 operator + (const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x + right.x, left.y + right.y);
	}

	Vector2 operator - (const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x - right.x, left.y - right.y);
	}

	bool operator == (const Vector2& left, const Vector2& right)
	{
		return left.x == right.x && left.y == right.y;
	}

	bool operator != (const Vector2& left, const Vector2& right)
	{
		return left.x != right.x || left.y != right.y;
	}

	Vector2& operator += (const Vector2& left, const Vector2& right)
	{
		Vector2* res = new Vector2(left.x + right.x, left.y + right.y);
		return *res;
	}

	Vector2& operator -= (const Vector2& left, const Vector2& right)
	{
		Vector2* res = new Vector2(left.x - right.x, left.y - right.y);
		return *res;
	}

	float Distance(const Vector2& a, const Vector2& b)
	{
		return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
	}

	/*Bounds::Bounds()
	{
		this->topLeft = topLeft;
		this->bottomRight = bottomRight;
	}*/

	Bounds::Bounds(const Vector2& topLeft, const Vector2& bottomRight)
	{
		this->topLeft = topLeft;
		this->bottomRight = bottomRight;
	}
//}