#pragma once

#include "Vector3.h"
#include "Quaternion.h"

class Matrix4
{
public:
	float data[12];

	Vector3 operator*(const Vector3& vector);
	Matrix4 operator*(const Matrix4& other);

	float getDeterminant();

	Vector3 transform(Vector3& vector);
	Vector3 transformInverse(Vector3& vector);
	void setInverse(Matrix4& matrix);
	Matrix4 inverse();
	void invert();

	static Vector3 worldToLocal(Vector3& world, Matrix4& transform);
	static Vector3 localToWorld(Vector3& local, Matrix4& transform);

	void setOrientationPosition(Quaternion& quaternion, Vector3& position);
};