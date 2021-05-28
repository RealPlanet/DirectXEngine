#pragma once

struct vertex
{
	Vector3 position;
	Vector2 texcoord;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world = {};
	Matrix4x4 m_view = {};
	Matrix4x4 m_projection = {};

	Vector4 m_light_direction;
	Vector4 m_camera_position;

	Vector4 m_light_position = Vector4(0, 1, 0, 0);
	float m_light_radius = 500.0f;

	float m_time = 0;
};
