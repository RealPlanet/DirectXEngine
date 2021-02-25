#pragma once

class Vector4D
{
public:
	float x, y, z, w;
	Vector4D() : x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 }{}
	Vector4D(float _x, float _y, float _z, float _w) : x{ _x }, y{ _y }, z{ _z }, w{ _w }{}
	inline void cross(Vector4D& v1, Vector4D& v2, Vector4D& v3);
};

void Vector4D::cross(Vector4D& v1, Vector4D& v2, Vector4D& v3)
{
	this->x = v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v2.z * v3.y);
	this->y = -(v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z));
	this->z = v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y);
	this->w = -(v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x * v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y));
}