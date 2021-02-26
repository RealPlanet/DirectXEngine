#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix4x4.h"

struct vertex
{
	Vector3D position;
	Vector2D texcoord;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world = {};
	Matrix4x4 m_view = {};
	Matrix4x4 m_projection = {};

	unsigned int m_time = 0;
};