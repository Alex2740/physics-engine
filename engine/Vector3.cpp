#include "Vector3.h"

void Vector3::setMagnitude()
{
	magnitude_ = sqrtf(Vector3::Dot(*this, *this));
}

Vector3::Vector3()
{
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x_ = _x;
	y_ = _y;
	z_ = _z;

	setMagnitude();
}

void Vector3::setX(float _x)
{
	x_ = _x;

	setMagnitude();
}

void Vector3::setY(float _y)
{
	y_ = _y;

	setMagnitude();
}

void Vector3::setZ(float _z)
{
	z_ = _z;

	setMagnitude();
}

Vector3 Vector3::operator=(const Vector3& other)
{
	this->x_ = other.x;
	this->y_ = other.y;
	this->z_ = other.z;

	setMagnitude();

	return *this;
}

Vector3 Vector3::operator+=(const Vector3& other)
{
	this->x_ += other.x;
	this->y_ += other.y;
	this->z_ += other.z;

	setMagnitude();

	return Vector3(this->x_ + other.x, this->y_ + other.y, this->z_ + other.z);
}

Vector3 Vector3::operator+(const Vector3& other)
{
	Vector3 result = *this;
	result += other;
	return result;
}

Vector3 Vector3::operator-=(const Vector3& other)
{
	x_ -= other.x;
	y_ -= other.y;
	z_ -= other.z;

	setMagnitude();

	return *this;
}

Vector3 Vector3::operator-(const Vector3& other)
{
	Vector3 result = Vector3::Zero();
	result = *this;
	result -= other;
	return result;
}

Vector3 Vector3::operator*(const float& other)
{
	float newX = x * other;
	float newY = y * other;
	float newZ = z * other;
	return Vector3(newX, newY, newZ);
}

Vector3 Vector3::operator/(const float& other)
{
	float newX = x / other;
	float newY = y / other;
	float newZ = z / other;
	return Vector3(newX, newY, newZ);
}

bool Vector3::operator==(const Vector3& other)
{
	return (x == other.x) && (y == other.y) && (z == other.z);
}

bool Vector3::operator!=(const Vector3& other)
{
	return !(*this == other);
}

float Vector3::Dot(const Vector3 a, const Vector3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::Cross(const Vector3 a, const Vector3 b)
{
	float newX = a.y * b.z - a.z * b.y;
	float newY = a.z * b.x - a.x * b.z;
	float newZ = a.x * b.y - a.y * b.x;
	return Vector3(newX, newY, newZ);
}

Vector3 Vector3::Normalized(const Vector3 a)
{
	Vector3 v = a;
	return v / v.magnitude;
}

float Vector3::Distance(const Vector3 a, const Vector3 b)
{
	Vector3 x = a;
	Vector3 y = b;
	return (x - y).magnitude;
}

Vector3 Vector3::Zero()
{
	return Vector3(0, 0, 0);
}

void Vector3::print()
{
	std::cout << "Vector3(" << x << "f, " << y << "f, " << z << "f)" << std::endl;
}
