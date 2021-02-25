#pragma once

class Vector3D
{
public:
	float x, y, z;
	Vector3D() : x{0}, y{0}, z{0}{}
	Vector3D(float _x, float _y, float _z) : x{ _x }, y{ _y }, z{ _z }{}
	Vector3D(const Vector3D& vector) : x{ vector.x }, y{ vector.y }, z{ vector.z }{}

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta)
	{
		Vector3D v;
		v.x = start.x * (1 - delta) + end.x * delta;
		v.y = start.y * (1 - delta) + end.y * delta;
		v.z = start.z * (1 - delta) + end.z * delta;

		return v;
	}

	Vector3D operator*(float num)
	{
		return Vector3D(x * num, y * num, z * num);
	}

	Vector3D operator+(Vector3D vec)
	{
		return Vector3D(x + vec.x, y + vec.y, z + vec.z);
	}
};