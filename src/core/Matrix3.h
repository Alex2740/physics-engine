#pragma once

#include "Vector3.h"
#include "Quaternion.h"

class Matrix3
{
public:
	float data[9];

	Matrix3();

	Vector3 operator*(const Vector3 &vector);
	Matrix3 operator*(const Matrix3 &other);
	void operator*=(const Matrix3 &other);

	Vector3 transform(Vector3 &vector);

	void setInverse(Matrix3 &matrix);
	Matrix3 inverse();
	void invert();

	void setTranspose(Matrix3 &matrix);
	Matrix3 transpose();

	void setOrientation(Quaternion &quaternion);
};
