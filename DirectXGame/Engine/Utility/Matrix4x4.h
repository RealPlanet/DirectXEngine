#pragma once
#include <memory>
#include <Vector3D.h>

class Matrix4x4
{
public:
	void setIdentity()
	{
		memset(matrix, 0, sizeof(float) * 16);
		matrix[0][0] = 1;
		matrix[1][1] = 1;
		matrix[2][2] = 1;
		matrix[3][3] = 1;
	}

	void setTranslation(const Vector3D& translation)
	{
		setIdentity();
		matrix[3][0] = translation.x;
		matrix[3][1] = translation.y;
		matrix[3][2] = translation.z;
	}

	void setScale(const Vector3D& scale)
	{
		setIdentity();
		matrix[0][0] = scale.x;
		matrix[1][1] = scale.y;
		matrix[2][2] = scale.z;
	}

	void setOrthoLH(float width, float height, float near_plane, float far_plane)
	{
		setIdentity();
		matrix[0][0] = 2.0f / width;
		matrix[1][1] = 2.0f / height;
		matrix[2][2] = 1.0f / (far_plane - near_plane);
		matrix[3][2] = -(near_plane / (far_plane - near_plane));
	}

	void operator*=(Matrix4x4 other)
	{
		Matrix4x4 res;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				res.matrix[i][j] = 
					matrix[i][0] * other.matrix[0][j] + matrix[i][1] * other.matrix[1][j] +
					matrix[i][2] * other.matrix[2][j] + matrix[i][3] * other.matrix[3][j];

			}
		}
		memcpy(matrix, res.matrix, sizeof(float) * 16);
	}

private:
	float matrix[4][4] = {};
};