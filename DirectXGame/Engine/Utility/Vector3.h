#pragma once

class Vector3
{
public:
	float x, y, z;
	Vector3() : x{0}, y{0}, z{0}{}
	Vector3(float _x, float _y, float _z) : x{ _x }, y{ _y }, z{ _z }{}
	Vector3(const Vector3& vector) : x{ vector.x }, y{ vector.y }, z{ vector.z }{}

	static Vector3 lerp(const Vector3& start, const Vector3& end, float delta)
	{
		Vector3 v;
		v.x = start.x * (1 - delta) + end.x * delta;
		v.y = start.y * (1 - delta) + end.y * delta;
		v.z = start.z * (1 - delta) + end.z * delta;

		return v;
	}

	Vector3 operator*(float num)
	{
		return Vector3(x * num, y * num, z * num);
	}

	Vector3 operator+(Vector3 vec)
	{
		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}
};