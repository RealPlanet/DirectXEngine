#pragma once

class Vector2
{
public:
	float x, y;
	Vector2() :x(0), y(0)
	{
	}
	Vector2(float x, float y) :x(x), y(y)
	{
	}
	Vector2(const Vector2& vector) :x(vector.x), y(vector.y)
	{
	}

	Vector2 operator *(float num)
	{
		return Vector2(x * num, y * num);
	}

	Vector2 operator +(Vector2 vec)
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	~Vector2()
	{
	}
};