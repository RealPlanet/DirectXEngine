#include "Matrix4x4.h"
#include "Vector3D.h"
#include "Vector4D.h"

void Matrix4x4::setIdentity()
{
	memset(matrix, 0, sizeof(float) * 16);
	matrix[0][0] = 1;
	matrix[1][1] = 1;
	matrix[2][2] = 1;
	matrix[3][3] = 1;
}

float Matrix4x4::getDeterminant()
{
	Vector4D minor, v1, v2, v3;
	float det;

	v1 = Vector4D(this->matrix[0][0], this->matrix[1][0], this->matrix[2][0], this->matrix[3][0]);
	v2 = Vector4D(this->matrix[0][1], this->matrix[1][1], this->matrix[2][1], this->matrix[3][1]);
	v3 = Vector4D(this->matrix[0][2], this->matrix[1][2], this->matrix[2][2], this->matrix[3][2]);


	minor.cross(v1, v2, v3);
	det = -(this->matrix[0][3] * minor.x + this->matrix[1][3] * minor.y + this->matrix[2][3] * minor.z +
		this->matrix[3][3] * minor.w);
	return det;
}

void Matrix4x4::inverse()
{
	int a, i, j;
	Matrix4x4 out;
	Vector4D v, vec[3];
	float det = 0.0f;

	det = this->getDeterminant();
	if (!det) return;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (j != i)
			{
				a = j;
				if (j > i) a = a - 1;
				vec[a].x = (this->matrix[j][0]);
				vec[a].y = (this->matrix[j][1]);
				vec[a].z = (this->matrix[j][2]);
				vec[a].w = (this->matrix[j][3]);
			}
		}
		v.cross(vec[0], vec[1], vec[2]);

		out.matrix[0][i] = pow(-1.0f, i) * v.x / det;
		out.matrix[1][i] = pow(-1.0f, i) * v.y / det;
		out.matrix[2][i] = pow(-1.0f, i) * v.z / det;
		out.matrix[3][i] = pow(-1.0f, i) * v.w / det;
	}

	this->setMatrix(out);
}

void Matrix4x4::setMatrix(const Matrix4x4& matrix)
{
	memcpy(this->matrix, matrix.matrix, sizeof(float) * 16);
}

void Matrix4x4::setRotationX(float x)
{
	matrix[1][1] = (float)cos(x);
	matrix[1][2] = (float)sin(x);
	matrix[2][1] = (float)-sin(x);
	matrix[2][2] = (float)cos(x);
}

void Matrix4x4::setRotationY(float y)
{
	matrix[0][0] = (float)cos(y);
	matrix[0][2] = (float)-sin(y);
	matrix[2][0] = (float)sin(y);
	matrix[2][2] = (float)cos(y);
}

void Matrix4x4::setRotationZ(float z)
{
	matrix[0][0] = (float)cos(z);
	matrix[0][1] = (float)sin(z);
	matrix[1][0] = (float)-sin(z);
	matrix[1][1] = (float)cos(z);
}

void Matrix4x4::setTranslation(const Vector3D& translation)
{
	matrix[3][0] = translation.x;
	matrix[3][1] = translation.y;
	matrix[3][2] = translation.z;
}

void Matrix4x4::setScale(const Vector3D& scale)
{
	matrix[0][0] = scale.x;
	matrix[1][1] = scale.y;
	matrix[2][2] = scale.z;
}

void Matrix4x4::setPerspectiveFovLH(float fov, float aspect, float zNear, float zFar)
{
	float yScale = 1.0f / tan(fov / 2.0f);
	float xScale = yScale / aspect;

	matrix[0][0] = xScale;
	matrix[1][1] = yScale;
	matrix[2][2] = zFar / (zFar - zNear);
	matrix[2][3] = 1.0f;
	matrix[3][2] = (-zNear * zFar) / (zFar - zNear);
}

void Matrix4x4::setOrthoLH(float width, float height, float near_plane, float far_plane)
{
	setIdentity();
	matrix[0][0] = 2.0f / width;
	matrix[1][1] = 2.0f / height;
	matrix[2][2] = 1.0f / (far_plane - near_plane);
	matrix[3][2] = -(near_plane / (far_plane - near_plane));
}

Vector3D Matrix4x4::getZDirection()
{
	return Vector3D(matrix[2][0], matrix[2][1], matrix[2][2]);
}

Vector3D Matrix4x4::getXDirection()
{
	return Vector3D(matrix[0][0], matrix[0][1], matrix[0][2]);
}

Vector3D Matrix4x4::getTranslation()
{
	return Vector3D(matrix[3][0], matrix[3][1], matrix[3][2]);
}

