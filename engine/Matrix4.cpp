#include "Matrix4.h"

Matrix4::Matrix4(Matrix3 matrix3, Vector3 vector) {
	data[0] = matrix3.data[0];
	data[1] = matrix3.data[1];
	data[2] = matrix3.data[2];

	data[4] = matrix3.data[3];
	data[5] = matrix3.data[4];
	data[6] = matrix3.data[5];

	data[8] = matrix3.data[6];
	data[9] = matrix3.data[7];
	data[10] = matrix3.data[8];

	data[3] = vector.x;
	data[7] = vector.y;
	data[11] = vector.z;
}

Vector3 Matrix4::operator*(const Vector3& vector)
{
	return Vector3(
		vector.x * data[0] + vector.y * data[1] + vector.z * data[2] + data[3],
		vector.x * data[4] + vector.y * data[5] + vector.z * data[6] + data[7],
		vector.x * data[8] + vector.y * data[9] + vector.z * data[10] + data[11]
	);
}

Matrix4 Matrix4::operator*(const Matrix4& other)
{
	Matrix4 result = Matrix4();

	result.data[0] = data[0] * other.data[0] + data[4] * other.data[1] + data[8] * other.data[2];
	result.data[4] = data[0] * other.data[4] + data[4] * other.data[5] + data[8] * other.data[6];
	result.data[8] = data[0] * other.data[8] + data[4] * other.data[9] + data[8] * other.data[10];

	result.data[1] = data[1] * other.data[0] + data[5] * other.data[1] + data[9] * other.data[2];
	result.data[5] = data[1] * other.data[4] + data[5] * other.data[5] + data[9] * other.data[6];
	result.data[9] = data[1] * other.data[8] + data[5] * other.data[9] + data[9] * other.data[10];

	result.data[2] = data[2] * other.data[0] + data[6] * other.data[1] + data[10] * other.data[2];
	result.data[6] = data[2] * other.data[4] + data[6] * other.data[5] + data[10] * other.data[6];
	result.data[10] = data[2] * other.data[8] + data[6] * other.data[9] + data[10] * other.data[10];

	result.data[3] = data[3] * other.data[0] + data[7] * other.data[1] + data[11] * other.data[2];
	result.data[7] = data[3] * other.data[4] + data[7] * other.data[5] + data[11] * other.data[6];
	result.data[11] = data[3] * other.data[8] + data[7] * other.data[9] + data[11] * other.data[10];

	return result;
}

float Matrix4::getDeterminant()
{
	return - data[8] * data[5] * data[2]
		+ data[4] * data[9] * data[2]
		+ data[8] * data[1] * data[6]
		- data[0] * data[9] * data[6]
		- data[4] * data[1] * data[10]
		+ data[0] * data[5] * data[10];
}

Matrix3 Matrix4::getMatrix3()
{
	Matrix3 ret = Matrix3();
	ret.data[0] = data[0];
	ret.data[1] = data[1];
	ret.data[2] = data[2];

	ret.data[3] = data[4];
	ret.data[4] = data[5];
	ret.data[5] = data[6];

	ret.data[6] = data[8];
	ret.data[7] = data[9];
	ret.data[8] = data[10];

	return ret;
}

Vector3 Matrix4::transform(Vector3& vector)
{
	return (*this) * vector;
}

Vector3 Matrix4::transformInverse(Vector3& vector)
{
	Vector3 tmp = vector;
	tmp.x -= data[3];
	tmp.y -= data[7];
	tmp.z -= data[11];

	return Vector3(
		tmp.x * data[0] + tmp.y * data[4] + tmp.z * data[8],
		tmp.x * data[1] + tmp.y * data[5] + tmp.z * data[9],
		tmp.x * data[2] + tmp.y * data[6] + tmp.z * data[10]
	);
}

void Matrix4::setInverse(Matrix4& matrix)
{
	float determinant = matrix.getDeterminant();

	if (determinant == 0.0f) return;

	float inverseDeterminant = 1.0f / determinant;

	data[0] = (-matrix.data[9] * matrix.data[6] + matrix.data[5] * matrix.data[10]) * inverseDeterminant;
	data[4] = (matrix.data[8] * matrix.data[6] - matrix.data[4] * matrix.data[10]) * inverseDeterminant;
	data[8] = (-matrix.data[8] * matrix.data[5] + matrix.data[4] * matrix.data[9]) * inverseDeterminant;
	data[1] = (matrix.data[9] * matrix.data[2] - matrix.data[1] * matrix.data[10]) * inverseDeterminant;
	data[5] = (-matrix.data[8] * matrix.data[2] + matrix.data[0] * matrix.data[10]) * inverseDeterminant;
	data[9] = (matrix.data[8] * matrix.data[1] - matrix.data[0] * matrix.data[9]) * inverseDeterminant;
	data[2] = (-matrix.data[5] * matrix.data[2] + matrix.data[1] * matrix.data[6]) * inverseDeterminant;
	data[6] = (matrix.data[4] * matrix.data[2] - matrix.data[0] * matrix.data[6]) * inverseDeterminant;
	data[10] = (-matrix.data[4] * matrix.data[1] + matrix.data[0] * matrix.data[5]) * inverseDeterminant;
	data[3] = (matrix.data[9] * matrix.data[6] * matrix.data[3] - matrix.data[5] * matrix.data[10] * matrix.data[3] - matrix.data[9] * matrix.data[2] * matrix.data[7] + matrix.data[1] * matrix.data[10] * matrix.data[7] + matrix.data[5] * matrix.data[2] * matrix.data[11] - matrix.data[1] * matrix.data[6] * matrix.data[11]) * inverseDeterminant;
	data[7] = (-matrix.data[8] * matrix.data[6] * matrix.data[3] + matrix.data[4] * matrix.data[10] * matrix.data[3] + matrix.data[8] * matrix.data[2] * matrix.data[7] - matrix.data[0] * matrix.data[10] * matrix.data[7] - matrix.data[4] * matrix.data[2] * matrix.data[11] + matrix.data[0] * matrix.data[6] * matrix.data[11]) * inverseDeterminant;
	data[11] = (matrix.data[8] * matrix.data[5] * matrix.data[3] - matrix.data[4] * matrix.data[9] * matrix.data[3] - matrix.data[8] * matrix.data[1] * matrix.data[7] + matrix.data[0] * matrix.data[9] * matrix.data[7] + matrix.data[4] * matrix.data[1] * matrix.data[11] - matrix.data[0] * matrix.data[5] * matrix.data[11]) * inverseDeterminant;
}

Matrix4 Matrix4::inverse()
{
	Matrix4 result = Matrix4();

	result.setInverse(*this);

	return result;
}

void Matrix4::invert()
{
	setInverse(*this);
}

Vector3 Matrix4::worldToLocal(Vector3& world, Matrix4& transform)
{
	return transform.transformInverse(world);
}

Vector3 Matrix4::localToWorld(Vector3& local, Matrix4& transform)
{
	return transform.transform(local);
}

void Matrix4::setOrientationPosition(Quaternion& quaternion, Vector3& position)
{
	data[0] = 1 - (2 * quaternion.y * quaternion.y + 2 * quaternion.z * quaternion.z);
	data[1] = 2 * quaternion.x * quaternion.y + 2 * quaternion.z * quaternion.w;
	data[2] = 2 * quaternion.x * quaternion.z - 2 * quaternion.y * quaternion.w;
	data[3] = position.x;
	data[4] = 2 * quaternion.x * quaternion.y - 2 * quaternion.z * quaternion.w;
	data[5] = 1 - (2 * quaternion.x * quaternion.x + 2 * quaternion.z * quaternion.z);
	data[6] = 2 * quaternion.y * quaternion.z + 2 * quaternion.x * quaternion.w;
	data[7] = position.y;
	data[8] = 2 * quaternion.x * quaternion.z + 2 * quaternion.y * quaternion.w;
	data[9] = 2 * quaternion.y * quaternion.z - 2 * quaternion.x * quaternion.w;
	data[10] = 1 - (2 * quaternion.x * quaternion.x + 2 * quaternion.y * quaternion.y);
	data[11] = position.z;
}
