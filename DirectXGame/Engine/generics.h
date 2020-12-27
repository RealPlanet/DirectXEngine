struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color_1;
};

__declspec(align(16))
struct constant
{
	unsigned int m_time;
};