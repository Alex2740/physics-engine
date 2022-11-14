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

	void setOrientationPosition(Quaternion& quaternion, Vector3& position);
};