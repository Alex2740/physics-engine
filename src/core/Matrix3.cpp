#include "Matrix3.h"

Matrix3::Matrix3()
{
	for (size_t i = 0; i < 9; i++)
	{
		data[i] = 0;
	}
}

Matrix3 Matrix3::eye()
{
	Matrix3 m = Matrix3();
	m.data[0] = 1;
	m.data[4] = 1;
	m.data[8] = 1;

	return m;
}

Vector3 Matrix3::operator*(const Vector3& vector)
{
	return Vector3(
		vector.x * data[0] + vector.y * data[1] + vector.z * data[2],
		vector.x * data[3] + vector.y * data[4] + vector.z * data[5],
		vector.x * data[6] + vector.y * data[7] + vector.z * data[8]
	);
}

Matrix3 Matrix3::operator*(const Matrix3& other)
{
	Matrix3 result = Matrix3();

	result.data[0] = data[0] * other.data[0] + data[1] * other.data[3] + data[2] * other.data[6];
	result.data[1] = data[0] * other.data[1] + data[1] * other.data[4] + data[2] * other.data[7];
	result.data[2] = data[0] * other.data[2] + data[1] * other.data[5] + data[2] * other.data[8];

	result.data[3] = data[3] * other.data[0] + data[4] * other.data[3] + data[5] * other.data[6];
	result.data[4] = data[3] * other.data[1] + data[4] * other.data[4] + data[5] * other.data[7];
	result.data[5] = data[3] * other.data[2] + data[4] * other.data[5] + data[5] * other.data[8];

	result.data[6] = data[6] * other.data[0] + data[7] * other.data[3] + data[8] * other.data[6];
	result.data[7] = data[6] * other.data[1] + data[7] * other.data[4] + data[8] * other.data[7];
	result.data[8] = data[6] * other.data[2] + data[7] * other.data[5] + data[8] * other.data[8];

	return result;
}

void Matrix3::operator*=(const Matrix3& other)
{
	float t1, t2, t3;

	t1 = data[0] * other.data[0] + data[1] * other.data[3] + data[2] * other.data[6];
	t2 = data[0] * other.data[1] + data[1] * other.data[4] + data[2] * other.data[7];
	t3 = data[0] * other.data[2] + data[1] * other.data[5] + data[2] * other.data[8];
	data[0] = t1;
	data[1] = t2;
	data[2] = t3;

	t1 = data[3] * other.data[0] + data[4] * other.data[3] + data[5] * other.data[6];
	t2 = data[3] * other.data[1] + data[4] * other.data[4] + data[5] * other.data[7];
	t3 = data[3] * other.data[2] + data[4] * other.data[5] + data[5] * other.data[8];
	data[3] = t1;
	data[4] = t2;
	data[5] = t3;

	t1 = data[6] * other.data[0] + data[7] * other.data[3] + data[8] * other.data[6];
	t2 = data[6] * other.data[1] + data[7] * other.data[4] + data[8] * other.data[7];
	t3 = data[6] * other.data[2] + data[7] * other.data[5] + data[8] * other.data[8];
	data[6] = t1;
	data[7] = t2;
	data[8] = t3;
}

Vector3 Matrix3::transform(Vector3& vector)
{
	return (*this) * vector;
}

void Matrix3::setInverse(Matrix3& matrix)
{

	float determinant = -matrix.data[2] * matrix.data[4] * matrix.data[6] + matrix.data[1] * matrix.data[5] * matrix.data[6] + matrix.data[2] * matrix.data[3] * matrix.data[7] - matrix.data[0] * matrix.data[5] * matrix.data[7] -matrix.data[1] * matrix.data[3] * matrix.data[8] + matrix.data[0] * matrix.data[4] * matrix.data[8];

	if (determinant == 0.0f) return;

	float inverseDeterminant = 1.0f / determinant;

	data[0] = (matrix.data[4] * matrix.data[8] - matrix.data[5] * matrix.data[7]) * inverseDeterminant;
	data[1] = -(matrix.data[1] * matrix.data[8] - matrix.data[2] * matrix.data[7]) * inverseDeterminant;
	data[2] = (matrix.data[1] * matrix.data[5] - matrix.data[2] * matrix.data[4]) * inverseDeterminant;
	data[3] = -(matrix.data[3] * matrix.data[8] - matrix.data[5] * matrix.data[6]) * inverseDeterminant;
	data[4] = (matrix.data[0] * matrix.data[8] - matrix.data[2] * matrix.data[6]) * inverseDeterminant;
	data[5] = -(matrix.data[0] * matrix.data[5] - matrix.data[2] * matrix.data[3]) * inverseDeterminant;
	data[6] = (matrix.data[3] * matrix.data[7] - matrix.data[4] * matrix.data[6]) * inverseDeterminant;
	data[7] = -(matrix.data[0] * matrix.data[7] - matrix.data[1] * matrix.data[6]) * inverseDeterminant;
	data[8] = (matrix.data[0] * matrix.data[4] - matrix.data[1] * matrix.data[3]) * inverseDeterminant;
}

Matrix3 Matrix3::inverse()
{
	Matrix3 result = Matrix3();

	result.setInverse(*this);

	return result;
}

void Matrix3::invert()
{
	setInverse(*this);
}

void Matrix3::setTranspose(Matrix3& matrix)
{
	data[0] = matrix.data[0];
	data[1] = matrix.data[3];
	data[2] = matrix.data[6];
	data[3] = matrix.data[1];
	data[4] = matrix.data[4];
	data[5] = matrix.data[7];
	data[6] = matrix.data[2];
	data[7] = matrix.data[5];
	data[8] = matrix.data[8];
}

Matrix3 Matrix3::transpose()
{
	Matrix3 result = Matrix3();

	result.setTranspose(*this);

	return result;
}

void Matrix3::setOrientation(Quaternion& quaternion)
{
	data[0] = 1 - (2 * quaternion.y * quaternion.y + 2 * quaternion.z * quaternion.z);
	data[1] = 2 * quaternion.x * quaternion.y + 2 * quaternion.z * quaternion.w;
	data[2] = 2 * quaternion.x * quaternion.z - 2 * quaternion.y * quaternion.w;
	data[3] = 2 * quaternion.x * quaternion.y - 2 * quaternion.z * quaternion.w;
	data[4] = 1 - (2 * quaternion.x * quaternion.x + 2 * quaternion.z * quaternion.z);
	data[5] = 2 * quaternion.y * quaternion.z + 2 * quaternion.x * quaternion.w;
	data[6] = 2 * quaternion.x * quaternion.z + 2 * quaternion.y * quaternion.w;
	data[7] = 2 * quaternion.y * quaternion.z - 2 * quaternion.x * quaternion.w;
	data[8] = 1 - (2 * quaternion.x * quaternion.x + 2 * quaternion.y * quaternion.y);
}
