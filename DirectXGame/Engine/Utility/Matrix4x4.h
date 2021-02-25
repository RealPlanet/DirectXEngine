#pragma once
#include <memory>

class Vector3D;
class Vector4D;
class Matrix4x4
{
public:
	void setIdentity();
	void setTranslation(const Vector3D& translation);
	void setScale(const Vector3D& scale);
	void setPerspectiveFovLH(float fov, float aspect, float zNear, float zFar);
	void setOrthoLH(float width, float height, float near_plane, float far_plane);
	void setRotationX(float x);
	void setRotationY(float y);
	void setRotationZ(float z);
	float getDeterminant();
	void setMatrix(const Matrix4x4& matrix);
	Vector3D getZDirection();
	Vector3D getXDirection();
	Vector3D getTranslation();
	void inverse();

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