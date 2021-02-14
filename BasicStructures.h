#pragma once
#include <cmath>

//namespace st
//{
	struct Vector2
	{
		float x = 0;
		float y = 0;

		Vector2() {};
		Vector2(float x, float y);
	};

	struct Bounds
	{
		Vector2 topLeft;
		Vector2 bottomRight;

		Bounds() {}
		Bounds(const Vector2& topLeft, const Vector2& bottomRight);
	};

	float Distance(const Vector2& a, const Vector2& b);
//}